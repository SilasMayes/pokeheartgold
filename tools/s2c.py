#!/usr/bin/env python3
"""Convert the asm data files to C.

    python3 tools/s2c.py [options] asm/foo_data.s [...]

Each data file becomes src/data/<name>.c, or src/data/<name>_1.c ... _N.c (see below).
Every label becomes one C object with the same name and linkage (.public -> global,
otherwise static). Pointers stay pointers, so the same C also builds for 64-bit ports.

How a label is written:
  * a typed definition when a header already declares it (extern const Foo gBar[];):
    the header is included and the initializer is generated from the type's layout
  * otherwise a mechanical one: .byte/.short/.word runs become u8/u16/u32 arrays,
    .word tables of symbols become pointer arrays (function pointers when the targets
    are functions), records mixing pointers and numbers become arrays of an anonymous
    struct whose fields follow the directives, strings stay strings, .space in .bss
    becomes an uninitialised array
  * gaps (.balign, padding after a typed object) become __attribute__((aligned(n))) on
    the next object or a zero pad object

Ground truth comes from the GNU assembler: the original file is preprocessed and
assembled with arm-none-eabi-as, and every generated object is checked against it
(bytes, relocations, symbol offsets) after compiling the C with arm-none-eabi-gcc
(--verify). Types for typed definitions come from the DWARF of a probe compile
(needs pyelftools).

The DS build compiles the C with MWCC, which does not keep definition order: it sorts a
file's data by size (see "MWCC's data layout" below). With --mwcc, s2c splits each asm
file into the fewest C files whose sort can reproduce its layout, orders the definitions
so that it does, and checks the result with the real compiler against the original
assembled by MWAS, exactly (bytes, relocations, symbols, section sizes and alignment).
Without --mwcc the output is one file in asm order: right for GNU tools, not for MWCC.

Requirements: python3, arm-none-eabi-as/-gcc/-readelf, pyelftools (typed mode); for --mwcc,
metroskrew's native mwccarm and mwasmarm (bin directory as the argument).
"""

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from collections import OrderedDict, defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

GAME_DEFINES = {
    'HEARTGOLD': ['-DHEARTGOLD', '-DGAME_REMASTER=0', '-DENGLISH', '-DPM_KEEP_ASSERTS',
                  '-DSDK_ARM9', '-DSDK_CODE_ARM', '-DSDK_FINALROM'],
    'SOULSILVER': ['-DSOULSILVER', '-DGAME_REMASTER=0', '-DENGLISH', '-DPM_KEEP_ASSERTS',
                   '-DSDK_ARM9', '-DSDK_CODE_ARM', '-DSDK_FINALROM'],
}

ASM_INCLUDE_DIRS = ['.', 'include', 'asm/include', 'files', 'lib/include', 'lib/NitroDWC/asm/include',
                    'lib/MSL_C/asm/include', 'lib/NitroSDK/asm/include', 'lib/syscall/asm/include', 'asm',
                    'files/msgdata', 'lib/asm/include']

# Flags that let arm-none-eabi-gcc read the game headers (the same set CMakeLists.txt gives
# CLion), plus the layout switches that match MWCC: int-sized enums, no common symbols,
# no reordering, explicit zero initialisers stay in .data.
GCC_FLAGS = ['-c', '-std=gnu99', '-mcpu=arm946e-s', '-marm', '-mthumb-interwork', '-fno-short-enums',
             '-nostdinc', '-fms-extensions', '-fno-common', '-fno-toplevel-reorder',
             '-fno-zero-initialized-in-bss', '-fkeep-static-consts', '-fno-strict-aliasing',
             '-Wno-builtin-declaration-mismatch', '-Wno-implicit-int', '-Wno-multichar',
             '-D__CLION_IDE__', '-DSDK_CW', '-DSDK_TS', '-D_NITRO', '-D__arm',
             '-DPLATFORM_INTRINSIC_FUNCTION_BIT_CLZ32=__builtin_clz', '-Dwchar_t=__WCHAR_TYPE__',
             '-Isrc', '-Iinclude', '-Ifiles', '-Igenerated', '-Ilib/include', '-Ilib/include/cw', '-Ilib/include/nitro',
             '-Ilib/include/nnsys', '-Ilib/include/nitro/os', '-Iinclude/library',
             '-Ilib/NitroSDK/include', '-Ilib/NitroSDK/include-mw']

DATA_SECTIONS = ('.rodata', '.data', '.bss', '.version')


class S2CError(Exception):
    pass


def run(cmd, **kw):
    res = subprocess.run(cmd, capture_output=True, text=True, **kw)
    if res.returncode != 0:
        raise S2CError('command failed: %s\n%s%s' % (' '.join(map(str, cmd)), res.stdout, res.stderr))
    return res.stdout


def tool(name):
    prefix = os.environ.get('CROSS', 'arm-none-eabi-')
    return prefix + name


# --------------------------------------------------------------------------------------
# Lexing helpers
# --------------------------------------------------------------------------------------

def split_comment(line):
    """Split a source line into (code, comment). Comments: ';', '//', '@' outside strings."""
    in_str = False
    esc = False
    i = 0
    while i < len(line):
        c = line[i]
        if in_str:
            if esc:
                esc = False
            elif c == '\\':
                esc = True
            elif c == '"':
                in_str = False
        else:
            if c == '"':
                in_str = True
            elif c == ';' or c == '@':
                return line[:i], line[i + 1:].strip()
            elif c == '/' and line[i + 1:i + 2] == '/':
                return line[:i], line[i + 2:].strip()
        i += 1
    return line, ''


def split_operands(text):
    """Split on top-level commas (outside parentheses and strings)."""
    out = []
    depth = 0
    in_str = False
    esc = False
    cur = ''
    for c in text:
        if in_str:
            cur += c
            if esc:
                esc = False
            elif c == '\\':
                esc = True
            elif c == '"':
                in_str = False
            continue
        if c == '"':
            in_str = True
        elif c == '(':
            depth += 1
        elif c == ')':
            depth -= 1
        elif c == ',' and depth == 0:
            out.append(cur.strip())
            cur = ''
            continue
        cur += c
    if cur.strip():
        out.append(cur.strip())
    return out


def parse_string_literal(text):
    """Parse an assembler string literal, return bytes."""
    text = text.strip()
    if not (text.startswith('"') and text.endswith('"')):
        raise S2CError('bad string literal: %s' % text)
    body = text[1:-1]
    out = bytearray()
    i = 0
    while i < len(body):
        c = body[i]
        if c == '\\':
            i += 1
            e = body[i]
            simple = {'n': 10, 't': 9, 'r': 13, '0': 0, '\\': 92, '"': 34, "'": 39, 'b': 8, 'f': 12}
            if e == 'x':
                j = i + 1
                while j < len(body) and body[j] in '0123456789abcdefABCDEF':
                    j += 1
                out.append(int(body[i + 1:j], 16) & 0xFF)
                i = j
                continue
            if e in '01234567' and e != '0' or (e == '0' and i + 1 < len(body) and body[i + 1] in '01234567'):
                j = i
                while j < len(body) and j < i + 3 and body[j] in '01234567':
                    j += 1
                out.append(int(body[i:j], 8) & 0xFF)
                i = j
                continue
            if e not in simple:
                raise S2CError('unknown escape \\%s' % e)
            out.append(simple[e])
            i += 1
            continue
        out.extend(c.encode('latin-1'))
        i += 1
    return bytes(out)


SAFE_NUM = re.compile(r'^[\s0-9a-fA-FxX()+\-*/%<>|&^~]*$')


def eval_const(text):
    """Evaluate a purely numeric assembler expression (no symbols)."""
    t = text.strip()
    if not SAFE_NUM.match(t) or re.search(r'[a-wyzA-WYZ]', re.sub(r'0[xX][0-9a-fA-F]+', '', t)):
        raise S2CError('not a numeric expression: %s' % text)
    t = re.sub(r'\b0+(\d)', r'\1', t)
    return int(eval(t, {'__builtins__': {}}, {}))


IDENT = re.compile(r'[A-Za-z_$?][\w$?]*')


# --------------------------------------------------------------------------------------
# Source model
# --------------------------------------------------------------------------------------

class Item:
    """One emitted thing in a section, at a byte offset."""

    def __init__(self, kind, line, **kw):
        self.kind = kind          # 'label', 'data', 'string', 'space', 'align'
        self.line = line          # 1-based source line
        self.offset = None
        self.size = 0
        self.__dict__.update(kw)

    def __repr__(self):
        return '<%s @%s %s>' % (self.kind, self.offset, getattr(self, 'name', getattr(self, 'exprs', '')))


class Section:
    def __init__(self, name):
        self.name = name
        self.items = []
        self.size = 0


class AsmFile:
    """Parsed asm data file: sections with items, symbol visibility, includes, comments."""

    WIDTH = {'byte': 1, 'short': 2, 'hword': 2, '2byte': 2, 'word': 4, 'long': 4, '4byte': 4, 'int': 4}

    def __init__(self, path):
        self.path = Path(path)
        self.name = self.path.stem
        self.text = self.path.read_text()
        self.cpp_includes = []       # '#include "x.h"' lines of the file itself
        self.asm_includes = []       # .include "x.inc"
        self.public = set()
        self.extern = set()
        self.sections = OrderedDict()
        self.macros = {}
        self.top_comments = []
        self.parse()

    # .....................................................................
    def section(self, name):
        if name not in self.sections:
            self.sections[name] = Section(name)
        return self.sections[name]

    def parse(self):
        cur = None
        lines = self.text.splitlines()
        i = 0
        pending_comments = []
        while i < len(lines):
            raw = lines[i]
            lineno = i + 1
            i += 1
            stripped = raw.strip()
            if stripped.startswith('#'):
                m = re.match(r'#\s*include\s+(["<].*[">])', stripped)
                if m:
                    self.cpp_includes.append(m.group(1))
                elif stripped.startswith('#pragma once'):
                    pass
                else:
                    raise S2CError('%s:%d: unsupported preprocessor line: %s' % (self.path, lineno, stripped))
                continue
            code, comment = split_comment(raw)
            code = code.strip()
            if comment and not code:
                pending_comments.append(comment)
                continue
            if not code:
                if pending_comments and cur is None:
                    self.top_comments.extend(pending_comments)
                    pending_comments = []
                continue
            # macro definitions
            m = re.match(r'\.macro\s+(\w+)\s*(.*)', code)
            if m:
                params = [p.strip() for p in m.group(2).replace(',', ' ').split()]
                body = []
                while not re.match(r'\s*\.endm\b', lines[i]):
                    body.append(lines[i])
                    i += 1
                i += 1
                self.macros[m.group(1)] = (params, body)
                if pending_comments:
                    pending_comments = []
                continue
            stmts = self.expand(code, lineno)
            for stmt in stmts:
                cur = self.statement(stmt, lineno, cur, comment, pending_comments)
                comment = ''
                pending_comments = []
        if pending_comments and cur is not None:
            cur.items.append(Item('comment', len(lines), text=pending_comments))
        self.layout()

    def read_inc(self, inc):
        """Collect .public/.extern names from an included .inc (mwasm makes them global)."""
        if inc in ('asm/macros.inc', 'global.inc'):
            return
        for d in ASM_INCLUDE_DIRS:
            p = ROOT / d / inc
            if p.is_file():
                break
        else:
            raise S2CError('%s: cannot find .include %s' % (self.path, inc))
        for line in p.read_text().splitlines():
            code, _ = split_comment(line)
            m = re.match(r'\s*\.(public|global|extern)\s+(.*)$', code)
            if m:
                for n in split_operands(m.group(2)):
                    (self.public if m.group(1) != 'extern' else self.extern).add(n)
            elif code.strip() and not code.strip().startswith('#'):
                raise S2CError('%s: unexpected line in %s: %s' % (self.path, inc, line))

    def expand(self, code, lineno):
        m = re.match(r'([A-Za-z_]\w*)\b\s*(.*)$', code)
        if m and m.group(1) in self.macros and not code.rstrip().endswith(':'):
            params, body = self.macros[m.group(1)]
            args = split_operands(m.group(2)) if m.group(2).strip() else []
            if len(args) != len(params):
                raise S2CError('%s:%d: macro %s expects %d args' % (self.path, lineno, m.group(1), len(params)))
            out = []
            for b in body:
                bcode, _ = split_comment(b)
                for p, a in zip(params, args):
                    bcode = re.sub(r'\\' + re.escape(p) + r'\b', a, bcode)
                if bcode.strip():
                    out.append(bcode.strip())
            return out
        return [code]

    def statement(self, code, lineno, cur, comment, pending):
        # label (possibly followed by a statement)
        m = re.match(r'^([A-Za-z_.$?][\w.$?]*)\s*:\s*(.*)$', code)
        if m and not code.startswith('.'):
            if cur is None:
                raise S2CError('%s:%d: label outside a section' % (self.path, lineno))
            cur.items.append(Item('label', lineno, name=m.group(1), comment=comment, pre_comments=list(pending)))
            if m.group(2).strip():
                return self.statement(m.group(2).strip(), lineno, cur, '', [])
            return cur
        m = re.match(r'^\.(\w+)\b\s*(.*)$', code)
        if not m:
            raise S2CError('%s:%d: cannot parse: %s' % (self.path, lineno, code))
        d, rest = m.group(1), m.group(2).strip()
        if d in ('public', 'global', 'globl'):
            for n in split_operands(rest):
                self.public.add(n)
            return cur
        if d == 'extern':
            for n in split_operands(rest):
                self.extern.add(n)
            return cur
        if d == 'include':
            inc = rest.strip('"')
            self.asm_includes.append(inc)
            self.read_inc(inc)
            return cur
        if d in ('rodata', 'data', 'bss', 'text'):
            return self.section('.' + d)
        if d == 'section':
            name = split_operands(rest)[0]
            return self.section(name)
        if d in ('size', 'type'):
            return cur
        if cur is None:
            raise S2CError('%s:%d: data outside a section' % (self.path, lineno))
        if pending:
            cur.items.append(Item('comment', lineno, text=list(pending)))
        if d in self.WIDTH:
            exprs = split_operands(rest)
            cur.items.append(Item('data', lineno, width=self.WIDTH[d], exprs=exprs, comment=comment))
        elif d in ('ascii', 'asciz', 'string'):
            for s in split_operands(rest):
                b = parse_string_literal(s)
                if d != 'ascii':
                    b += b'\0'
                cur.items.append(Item('string', lineno, data=b, text=s, zero=(d != 'ascii'), comment=comment))
        elif d in ('space', 'skip', 'zero'):
            ops = split_operands(rest)
            fill = eval_const(ops[1]) if len(ops) > 1 else 0
            cur.items.append(Item('space', lineno, count=eval_const(ops[0]), fill=fill, comment=comment))
        elif d in ('balign', 'align', 'p2align'):
            ops = split_operands(rest)
            n = eval_const(ops[0])
            if d == 'p2align':
                n = 1 << n
            fill = eval_const(ops[1]) if len(ops) > 1 and ops[1] else 0
            cur.items.append(Item('align', lineno, align=n, fill=fill, comment=comment))
        else:
            raise S2CError('%s:%d: unsupported directive .%s' % (self.path, lineno, d))
        return cur

    def layout(self):
        for sec in self.sections.values():
            off = 0
            for it in sec.items:
                it.offset = off
                if it.kind == 'data':
                    it.size = it.width * len(it.exprs)
                elif it.kind == 'string':
                    it.size = len(it.data)
                elif it.kind == 'space':
                    it.size = it.count
                elif it.kind == 'align':
                    it.size = (-off) % it.align
                off += it.size
            sec.size = off


# --------------------------------------------------------------------------------------
# ELF reading (relocatable ARM objects)
# --------------------------------------------------------------------------------------

class Elf:
    def __init__(self, path):
        import struct
        self.struct = struct
        data = Path(path).read_bytes()
        self.data = data
        if data[:4] != b'\x7fELF' or data[4] != 1:
            raise S2CError('%s: not ELF32' % path)
        (e_shoff,) = struct.unpack_from('<I', data, 0x20)
        e_shentsize, e_shnum, e_shstrndx = struct.unpack_from('<HHH', data, 0x2E)
        shdrs = []
        for i in range(e_shnum):
            shdrs.append(struct.unpack_from('<IIIIIIIIII', data, e_shoff + i * e_shentsize))
        strtab_off = shdrs[e_shstrndx][4]
        self.sections = []
        for i, sh in enumerate(shdrs):
            name = self.cstr(strtab_off + sh[0])
            self.sections.append({'index': i, 'name': name, 'type': sh[1], 'flags': sh[2], 'offset': sh[4],
                                  'size': sh[5], 'link': sh[6], 'info': sh[7], 'align': sh[8],
                                  'entsize': sh[9]})
        self.by_name = {s['name']: s for s in self.sections}
        self.symbols = []
        for s in self.sections:
            if s['type'] == 2:  # SYMTAB
                strsec = self.sections[s['link']]
                for j in range(s['size'] // 16):
                    st_name, st_value, st_size, st_info, st_other, st_shndx = struct.unpack_from(
                        '<IIIBBH', data, s['offset'] + j * 16)
                    self.symbols.append({'name': self.cstr(strsec['offset'] + st_name), 'value': st_value,
                                         'size': st_size, 'bind': st_info >> 4, 'type': st_info & 15,
                                         'shndx': st_shndx})
        self.relocs = defaultdict(dict)   # section name -> offset -> (type, symname)
        self.addends = defaultdict(dict)  # RELA only: section name -> offset -> addend
        self.rel_by_index = defaultdict(dict)   # section index -> offset -> (type, symbol, addend or None)
        for s in self.sections:
            if s['type'] in (9, 4):  # REL, RELA
                target = self.sections[s['info']]['name']
                ent = 8 if s['type'] == 9 else 12
                for j in range(s['size'] // ent):
                    r_off, r_info = struct.unpack_from('<II', data, s['offset'] + j * ent)
                    sym = self.symbols[r_info >> 8]
                    name = sym['name']
                    if sym['type'] == 3:  # section symbol
                        name = self.sections[sym['shndx']]['name']
                    self.relocs[target][r_off] = (r_info & 0xFF, name)
                    addend = None
                    if ent == 12:
                        (addend,) = struct.unpack_from('<i', data, s['offset'] + j * ent + 8)
                        self.addends[target][r_off] = addend
                    self.rel_by_index[s['info']][r_off] = (r_info & 0xFF, sym, addend)
        self._merged = {}

    def merged(self, secname):
        """All sections called secname laid out the way the linker places them (in file order,
        each at its alignment), as one view: bytes, canonical relocations, symbol offsets."""
        if secname not in self._merged:
            self._merged[secname] = link_view([self], secname)
        return self._merged[secname]

    def cstr(self, off):
        end = self.data.index(b'\0', off)
        return self.data[off:end].decode('latin-1')

    def section_bytes(self, name):
        s = self.by_name.get(name)
        if s is None:
            return b''
        if s['type'] == 8:  # NOBITS
            return bytes(s['size'])
        return self.data[s['offset']:s['offset'] + s['size']]

    def defined_symbols(self, secname):
        s = self.by_name.get(secname)
        if s is None:
            return []
        return [y for y in self.symbols if y['shndx'] == s['index'] and y['type'] in (0, 1, 2) and y['name']
                and not y['name'].startswith('$')]


LINK_ALIGNALL = 4      # the SDK's LCF templates say ALIGNALL(4): every section starts 4-aligned


def link_view(elfs, secname):
    """Lay out the sections called secname of several objects as the linker does (objects in
    order, sections in file order, each at its alignment but at least LINK_ALIGNALL).
    Relocations are made canonical: targets defined in any of the objects become
    ('sect:<name>', final offset)."""
    place = {}            # (object #, section index) -> (section name, offset)
    ends = defaultdict(int)
    aligns = defaultdict(lambda: 1)
    first_align = {}
    for k, e in enumerate(elfs):
        for s in e.sections:
            if s['type'] not in (1, 8) or not s['name'] or not (s['flags'] & 2):
                continue
            a = max(s['align'], LINK_ALIGNALL)
            off = ends[s['name']]
            off += (-off) % a
            place[k, s['index']] = (s['name'], off)
            ends[s['name']] = off + s['size']
            aligns[s['name']] = max(aligns[s['name']], a)
            first_align.setdefault(s['name'], a)
    defined = {}
    for k, e in enumerate(elfs):
        for y in e.symbols:
            if (k, y['shndx']) in place and y['name'] and y['type'] in (0, 1, 2) and y['bind'] == 1:
                n, b = place[k, y['shndx']]
                defined[y['name']] = (n, b + y['value'])
    data = bytearray(ends[secname])
    relocs, syms = {}, {}
    present = False
    for k, e in enumerate(elfs):
        for s in e.sections:
            if (k, s['index']) not in place or s['name'] != secname:
                continue
            present = True
            _, b = place[k, s['index']]
            if s['type'] != 8:
                data[b:b + s['size']] = e.data[s['offset']:s['offset'] + s['size']]
            for r_off, (rtype, sym, addend) in e.rel_by_index.get(s['index'], {}).items():
                o = b + r_off
                if addend is None:
                    addend = int.from_bytes(data[o:o + 4], 'little')
                addend &= 0xFFFFFFFF
                if (k, sym['shndx']) in place:
                    n, tb = place[k, sym['shndx']]
                    val = sym['value'] if sym['type'] != 3 else 0
                    relocs[o] = (rtype, 'sect:' + n, (tb + val + addend) & 0xFFFFFFFF)
                elif sym['name'] in defined:
                    n, tb = defined[sym['name']]
                    relocs[o] = (rtype, 'sect:' + n, (tb + addend) & 0xFFFFFFFF)
                else:
                    relocs[o] = (rtype, sym['name'], addend)
            for y in e.symbols:
                if y['shndx'] == s['index'] and y['type'] in (0, 1, 2) and y['name'] \
                        and not y['name'].startswith('$') and not y['name'].startswith('.'):
                    syms[y['name']] = {'value': b + y['value'], 'bind': y['bind'], 'size': y['size']}
    return {'data': bytes(data), 'relocs': relocs, 'syms': syms, 'align': aligns[secname] if present else 1,
            'first_align': first_align.get(secname, 1), 'size': len(data), 'present': present}


# --------------------------------------------------------------------------------------
# GNU assembly of the original file (ground truth)
# --------------------------------------------------------------------------------------

def gnu_source(asm):
    """Rewrite an MWAS data file into something cpp + arm-none-eabi-as accept."""
    out = ['#include <nitro/fs/overlay.h>']
    for raw in asm.text.splitlines():
        s = raw.strip()
        if s.startswith('#'):
            out.append(s if s.startswith('#include') else '')
            continue
        code, _ = split_comment(raw)
        c = code.strip()
        if not c:
            out.append('')
            continue
        if re.match(r'\.include\b', c):
            out.append('')
            continue
        c = re.sub(r'^\.public\b', '.global', c)
        c = re.sub(r'^\.rodata\b', '.section .rodata', c)
        m = re.match(r'^\.section\s+([.\w]+)\s*,\s*(\d+)\s*$', c)
        if m:
            c = '.section %s,"aw"\n\t.balign %s' % (m.group(1), m.group(2))
        c = re.sub(r'^\.(size|type)\b.*$', '', c)
        out.append('\t' + c if not re.match(r'^[A-Za-z_.$?][\w.$?]*\s*:', c) else c)
    return '\n'.join(out) + '\n'


def assemble_original(asm, workdir, game='HEARTGOLD'):
    src = Path(workdir) / (asm.name + '.gnu.S')
    pre = Path(workdir) / (asm.name + '.gnu.s')
    obj = Path(workdir) / (asm.name + '.gnu.o')
    src.write_text(gnu_source(asm))
    incs = []
    for d in ASM_INCLUDE_DIRS:
        incs += ['-I', str(ROOT / d)]
    out = run(['cpp', '-P', '-x', 'assembler-with-cpp', '-undef', '-DPM_ASM', '-DSDK_ASM']
              + GAME_DEFINES[game] + incs + [str(src)])
    pre.write_text(out)
    run([tool('as'), '-mcpu=arm946e-s', '-o', str(obj), str(pre)])
    return Elf(obj)


# --------------------------------------------------------------------------------------
# Repository symbol index: is a name a function?
# --------------------------------------------------------------------------------------

class SymbolIndex:
    FUNC_ASM = re.compile(r'^\s*(?:arm|thumb|non_word_aligned_thumb|local_arm|local_thumb)_func_start\s+(\w+)', re.M)
    FUNC_TYPE = re.compile(r'^\s*\.type\s+(\w+)\s*,\s*[@%]function', re.M)
    # a function prototype or definition starting in column 0
    FUNC_C = re.compile(r'^(?!\s)(?!typedef\b)(?!return\b)(?:[\w*]+[\s*]+)+?\**\s*(\w+)\s*\([^;{)]*(?:\)|,)', re.M)

    def __init__(self, root):
        self.funcs = set()
        self.root = root
        cache = root / 'build' / 's2c_symbols.json'
        files = []
        for pattern in ('src/**/*.c', 'src/**/*.h', 'include/**/*.h', 'lib/**/*.c', 'lib/**/*.h', 'lib/**/*.cpp',
                        'src/**/*.cpp', 'asm/**/*.s', 'lib/**/*.s', 'asm/**/*.inc'):
            files += root.glob(pattern)
        for f in files:
            try:
                txt = f.read_text(errors='replace')
            except OSError:
                continue
            if f.suffix in ('.s', '.inc'):
                self.funcs.update(self.FUNC_ASM.findall(txt))
                self.funcs.update(self.FUNC_TYPE.findall(txt))
            else:
                for m in self.FUNC_C.finditer(txt):
                    line = txt[m.start():txt.find('\n', m.start())]
                    if '(*' in line.split(m.group(1))[0]:
                        continue
                    self.funcs.add(m.group(1))

    def is_func(self, name):
        return name in self.funcs

    def scan_mentions(self, names):
        """Record which repository files mention each of the given names."""
        self.mentions = defaultdict(set)
        names = set(names)
        ident = re.compile(r'[A-Za-z_$][\w$]*')
        for pattern in ('src/**/*', 'include/**/*', 'lib/**/*', 'asm/*.s', 'sub/**/*', 'files/**/*.s',
                        'files/**/*.h', '*.lsf', 'tools/**/*.py'):
            for f in self.root.glob(pattern):
                if not f.is_file() or f.suffix not in ('.c', '.h', '.s', '.cpp', '.inc', '.lsf', '.py', '.json'):
                    continue
                try:
                    txt = f.read_text(errors='replace')
                except OSError:
                    continue
                if txt.startswith('// Converted from asm/'):
                    continue        # an earlier run's output
                rel = str(f.relative_to(self.root))
                for tok in set(ident.findall(txt)) & names:
                    self.mentions[tok].add(rel)

    def referenced_outside(self, name, own_file):
        return any(f != own_file and not f.startswith('asm/include/') and f != 'tools/s2c.py'
                   for f in self.mentions.get(name, ()))


# --------------------------------------------------------------------------------------
# Objects: one per label (aliases share one), with the items that make up its bytes
# --------------------------------------------------------------------------------------

class Obj:
    def __init__(self, section, start, names, public, line):
        self.section = section
        self.start = start
        self.end = None
        self.names = list(names)
        self.public_names = set()
        self.items = []
        self.align_before = 1       # explicit .balign preceding the object
        self.comments = []
        self.line = line
        self.first_in_section = False

    @property
    def name(self):
        return self.names[0]

    @property
    def size(self):
        return self.end - self.start

    def __repr__(self):
        return '<Obj %s %s %#x+%#x>' % (self.names, self.section, self.start, self.size)


def partition(asm, sec):
    objs = []
    cur = None
    trailing = []          # align items after the content of cur
    pending_comments = []
    lead_align = 1

    def close(end):
        if cur is not None:
            cur.end = end

    for it in sec.items:
        if it.kind == 'comment':
            pending_comments.extend(it.text)
            continue
        if it.kind == 'label':
            if cur is not None and not cur.items and it.offset == cur.start:
                cur.names.append(it.name)
                if it.comment:
                    cur.comments.append(it.comment)
                cur.comments[0:0] = pending_comments + it.pre_comments
                pending_comments = []
                continue
            if cur is not None:
                cur.end = it.offset
            ab = 1
            for a in trailing:
                if a.fill != 0 and a.size:
                    raise S2CError('%s: non-zero alignment fill before %s' % (asm.path, it.name))
                ab = max(ab, a.align)
            trailing = []
            cur = Obj(sec.name, it.offset, [it.name], False, it.line)
            cur.align_before = max(ab, lead_align)
            lead_align = 1
            cur.comments = pending_comments + it.pre_comments + ([it.comment] if it.comment else [])
            pending_comments = []
            objs.append(cur)
            continue
        if cur is None:
            if it.kind == 'align' and not it.size:
                lead_align = max(lead_align, it.align)
                continue
            # bytes nobody labelled: give them a file-local name
            cur = Obj(sec.name, it.offset, ['s%sUnlabeled_%X' % (sec.name[1:].capitalize(), it.offset)], False, it.line)
            cur.align_before = lead_align
            cur.comments = pending_comments + ['not labelled in the asm']
            pending_comments = []
            objs.append(cur)
        if it.kind == 'align':
            if not cur.items:
                if it.size:
                    cur.items.append(it)
                else:
                    cur.align_before = max(cur.align_before, it.align)
            else:
                trailing.append(it)
            continue
        # content
        if trailing:
            cur.items.extend(trailing)
            trailing = []
        if pending_comments:
            cur.comments.extend(pending_comments)
            pending_comments = []
        cur.items.append(it)
    if cur is not None:
        cur.end = sec.size
        if trailing:
            # padding at the very end of the section: keep it inside the last object
            cur.items.extend(trailing)
    if objs:
        objs[0].first_in_section = True
    for o in objs:
        o.public_names = set(n for n in o.names if n in asm.public)
    return objs


# --------------------------------------------------------------------------------------
# C rendering helpers
# --------------------------------------------------------------------------------------

UTYPE = {1: 'u8', 2: 'u16', 4: 'u32'}
STYPE = {1: 's8', 2: 's16', 4: 's32'}
INT_LIT = re.compile(r'^\s*(-)?\s*(0[xX][0-9a-fA-F]+|[0-9]+)\s*$')
C_EXPR_OK = re.compile(r"^[\w\s()+\-*/%<>|&^~']*$")


def c_string(data):
    """Render bytes as a C string literal (octal escapes, never ambiguous)."""
    out = '"'
    for b in data:
        c = chr(b)
        if c == '"':
            out += '\\"'
        elif c == '\\':
            out += '\\\\'
        elif 0x20 <= b < 0x7F:
            out += c
        elif b == 10:
            out += '\\n'
        else:
            out += '\\%03o' % b
    return out + '"'


def sjis_text(data):
    """Shift-JIS reading of a string with non-ASCII bytes, for a comment; None if not text."""
    body = data.rstrip(b'\0')
    if not any(b >= 0x80 for b in body):
        return None
    try:
        text = body.decode('shift_jis')
    except UnicodeDecodeError:
        return None
    if any(ord(c) < 0x20 for c in text):
        return None
    return text


def is_c_identifier(name):
    return re.match(r'^[A-Za-z_]\w*$', name) is not None


class Cell:
    """One element of an object's contents."""
    __slots__ = ('off', 'w', 'kind', 'text', 'value', 'reloc', 'data', 'item')

    def __init__(self, off, w, kind, text=None, value=0, reloc=None, data=None, item=None):
        self.off, self.w, self.kind, self.text, self.value, self.reloc, self.data, self.item = \
            off, w, kind, text, value, reloc, data, item

    def __repr__(self):
        return '<Cell %#x w%d %s %r %s>' % (self.off, self.w, self.kind, self.text, self.reloc)


def make_cells(obj, raw, relocs):
    """Cells for an object: 'num' (with optional reloc), 'str', 'zero' (space/pad)."""
    cells = []
    for it in obj.items:
        if it.kind == 'data':
            for i, e in enumerate(it.exprs):
                off = it.offset + i * it.width
                val = int.from_bytes(raw[off:off + it.width], 'little')
                rel = relocs.get(off)
                if rel is not None and it.width != 4:
                    raise S2CError('relocation in a %d-byte cell at %#x' % (it.width, off))
                cells.append(Cell(off, it.width, 'num', text=e, value=val, reloc=rel, item=it))
        elif it.kind == 'string':
            cells.append(Cell(it.offset, it.size, 'str', data=raw[it.offset:it.offset + it.size], item=it))
        elif it.kind in ('space', 'align'):
            if it.size:
                data = raw[it.offset:it.offset + it.size]
                cells.append(Cell(it.offset, it.size, 'zero', data=data, item=it))
    return cells


class Target:
    """What a relocation points at."""

    def __init__(self, name, addend, kind):
        self.name, self.addend, self.kind = name, addend, kind   # kind: local / extern / overlay

    def __repr__(self):
        return '<Target %s%+d %s>' % (self.name, self.addend, self.kind)


class Field:
    """A field of a generated struct (or the element of a generated array)."""

    def __init__(self, off, ctype, count, kind, w):
        self.off, self.ctype, self.count, self.kind, self.w = off, ctype, count, kind, w
        self.signed = False

    @property
    def size(self):
        return self.w * (self.count or 1)

    def decl(self, name):
        if self.kind == 'fptr':
            return 'void (*%s)(void)' % name
        if self.kind == 'dptr':
            return 'const void *%s' % name
        return '%s %s%s' % (self.ctype, name, '[%d]' % self.count if self.count else '')


class Rep:
    """How one object is written in C."""

    def __init__(self, kind):
        self.kind = kind           # 'array', 'struct', 'structarray', 'string', 'bss', 'typed'
        self.elem = None           # Field for arrays
        self.fields = []           # for struct kinds
        self.count = None
        self.init = None           # initializer text
        self.align = 1             # natural alignment of the C type
        self.elem_size = 1         # for address arithmetic
        self.ctype_text = None     # typed mode: type spelling
        self.typed = None


class Generator:
    def __init__(self, asm, elf, symidx, header_idents, typed_info=None, force_casts=None, untyped=None,
                 hint_types=None, includes=None, declare=None, decl_names=None, force_renames=None, rows=None,
                 merges=None):
        self.asm = asm
        self.rows = rows or set()       # char arrays written as one row of a 2-D array (see ROW_NOTE)
        self.elf = elf
        self.symidx = symidx
        self.header_idents = header_idents
        self.typed_info = typed_info or {}      # name -> (include, decl text, CType)
        self.force_casts = force_casts or {}
        self.untyped = untyped or set()
        self.pointee_hints = {}
        self.hint_types = hint_types or {}      # local name -> CType inferred through a pointer
        self.includes = includes or []
        self.cast_specs = []
        self.sjis_seen = []
        self.renamed = []          # names whose header declarations get renamed away (const fixes)
        self.mismatch = OrderedDict()   # untyped names a header declares: name -> why
        self.decl_names = decl_names or {}      # name -> declaration text (header declarations)
        for n in force_renames or ():
            self.mismatch[n] = 'a header declares it differently'

        self.declare = declare or set()         # names a header seemed to declare but does not
        self.objs = OrderedDict()           # section -> [Obj]
        self.by_name = {}
        for sname, sec in asm.sections.items():
            if sname == '.text':
                if sec.size:
                    raise S2CError('%s: .text contains data' % asm.path)
                continue
            if sname not in DATA_SECTIONS:
                raise S2CError('%s: unsupported section %s' % (asm.path, sname))
            objs = partition(asm, sec)
            self.objs[sname] = objs
            for o in objs:
                for n in o.names:
                    self.by_name[n] = o
        # labels MWCC cannot place as objects of their own (see plan_tus): each is folded into
        # the object before it, and the code has to reach it through that object
        self.interior = []      # (label, owner, offset)
        for objs in self.objs.values():
            i = 1
            while i < len(objs):
                o = objs[i]
                if o.name not in (merges or ()):
                    i += 1
                    continue
                p = objs[i - 1]
                for n in o.names:
                    self.interior.append((n, p.name, o.start - p.start))
                    self.by_name[n] = p
                for n, owner, off in [x for x in self.interior if x[1] == o.name]:
                    self.interior.remove((n, owner, off))
                    self.interior.append((n, p.name, off + o.start - p.start))
                p.end = o.end
                p.items.extend(o.items)
                del objs[i]
        for objs in self.objs.values():
            for o in objs:
                inner = [(n, off) for n, owner, off in self.interior if owner == o.name]
                if inner:
                    o.comments.append('Also holds the asm labels %s. MWCC sorts a file\'s objects by size and the '
                                      'linker starts every section 4-aligned, so no arrangement of separate objects '
                                      'puts them where the asm has them; the code has to reach them through %s.'
                                      % (', '.join('%s (+%#x)' % x for x in inner), o.name))
        self.aliases = []       # (owner, alias): extra names that other code still uses
        self.dropped_aliases = []
        self.notes = []
        own = str(asm.path.relative_to(ROOT)) if asm.path.is_absolute() else str(asm.path)
        self.own_path = own
        for objs in self.objs.values():
            for o in objs:
                if len(o.names) == 1:
                    continue
                used = [n for n in o.names if symidx.referenced_outside(n, own)]
                pub = [n for n in o.names if n in asm.public]
                owner = (used or pub or o.names)[0]
                rest = [n for n in o.names if n != owner]
                o.names = [owner] + rest
                for n in rest:
                    if n in used:
                        # C cannot give one object two names
                        self.aliases.append((owner, n))
                        self.notes.append('%s is also labelled %s, which %s mention; only %s is defined'
                                          % (owner, n, ', '.join(sorted(symidx.mentions[n])), owner))
                    else:
                        self.dropped_aliases.append((owner, n))
                        o.comments.append('also labelled %s in the asm (unused)' % n)
        self.extern_funcs = set()
        self.extern_data = set()
        self.overlays = []
        self.reps = {}

    # ..................................................................
    def raw(self, sname):
        return self.elf.section_bytes(sname)

    def resolve(self, sname, off, value):
        """Resolve the relocation at sname:off (value = in-place addend)."""
        rel = self.elf.relocs.get(sname, {}).get(off)
        if rel is None:
            return None
        rtype, name = rel
        if rtype != 2:
            raise S2CError('unsupported relocation type %d at %s:%#x' % (rtype, sname, off))
        if name in DATA_SECTIONS:
            addr = value
            for o in self.objs.get(name, []):
                if o.start <= addr < o.end or (o.start == addr):
                    return Target(o.name, addr - o.start, 'local')
            raise S2CError('relocation into %s+%#x matches no label' % (name, addr))
        if name.startswith('SDK_OVERLAY_') and name.endswith('_ID'):
            if value:
                raise S2CError('overlay id with addend')
            return Target(name[len('SDK_OVERLAY_'):-len('_ID')], 0, 'overlay')
        if name in self.by_name:
            o = self.by_name[name]
            addend = value + (self.elf_sym_value(name) - o.start)
            return Target(o.name, addend, 'local')
        sval = value - (1 << 32) if value & 0x80000000 else value
        return Target(name, sval, 'extern')

    def elf_sym_value(self, name):
        for y in self.elf.symbols:
            if y['name'] == name and y['shndx'] != 0:
                return y['value']
        raise S2CError('symbol %s not defined' % name)

    # ..................................................................
    def is_func(self, t):
        if t.kind != 'extern':
            return False
        return self.symidx.is_func(t.name)

    def addr_expr(self, t, want, typed=False):
        """C expression for the address of a target; want = 'fptr' / 'dptr' / 'u32'."""
        if t.kind == 'overlay':
            self.need_overlay(t.name)
            return 'FS_OVERLAY_ID(%s)' % t.name
        if t.kind == 'extern':
            if want == 'fptr':
                if t.addend:
                    raise S2CError('function pointer %s with addend' % t.name)
                if t.name in self.header_idents and t.name not in self.declare:
                    return t.name if typed else '(void (*)(void))%s' % t.name
                self.extern_funcs.add(t.name)
                return t.name
            if t.name in self.header_idents and t.name not in self.declare:
                # declared by a header with a type we do not know: take its address
                if t.addend:
                    return '(const u8 *)&%s %s %d' % (t.name, '+' if t.addend > 0 else '-', abs(t.addend))
                return '&%s' % t.name
            if self.symidx.is_func(t.name):
                # a function stored in a data pointer
                self.extern_funcs.add(t.name)
                if t.addend:
                    return '(const u8 *)(const void *)%s %s %d' % (t.name, '+' if t.addend > 0 else '-', abs(t.addend))
                return '(const void *)%s' % t.name
            self.extern_data.add(t.name)
            if t.addend:
                return '%s %s %d' % (t.name, '+' if t.addend > 0 else '-', abs(t.addend))
            return t.name
        # local: resolved after every object has a representation
        return '@@%s@%d@@' % (t.name, t.addend)

    def sub_placeholder(self, m):
        name, addend = m.group(1), int(m.group(2))
        expr = self.local_addr(name, addend)
        if m.group(3) is None:
            return expr
        ptr = self.cast_specs[int(m.group(3))]
        if self.pointer_compatible(ptr, name, addend):
            return expr
        return '(%s)%s' % (spell(unconst(ptr)), expr if not expr.startswith('(') else '(%s)' % expr)

    def elem_spelling(self, rep):
        if rep.kind == 'typed':
            t = rep.typed['type']
            e = t.target if rep.typed['array'] else t
            if e.const:
                e2 = CType(e.kind)
                e2.__dict__.update(e.__dict__)
                e2.const = False
                e = e2
            try:
                return spell(e)
            except TypedFail:
                return None
        if rep.kind in ('array', 'bss') and rep.elem is not None and rep.elem.kind == 'num':
            return rep.elem.ctype
        if rep.kind == 'string':
            return 'char'
        return None

    def pointer_compatible(self, ptr, name, addend):
        rep = self.reps[name]
        es = self.elem_spelling(rep)
        if es is None or addend % max(rep.elem_size, 1):
            return False
        p = ptr.target
        if p is None:
            return False
        pconst = is_const_object(p)
        p2 = CType(p.kind)
        p2.__dict__.update(p.__dict__)
        p2.const = False
        try:
            ps = spell(p2)
        except TypedFail:
            return False
        if ps == 'void':
            return pconst or self.by_name[name].section != '.rodata'
        if ps != es:
            return False
        obj_const = self.by_name[name].section == '.rodata'
        return pconst or not obj_const

    def local_addr(self, name, addend):
        rep = self.reps[name]
        t = Target(name, addend, 'local')
        if rep.kind in ('array', 'string', 'bss', 'structarray') or (rep.kind == 'typed' and rep.typed['array']):
            es = rep.elem_size
            base = t.name + ('[0]' if getattr(rep, 'row', False) else '')
            if t.addend == 0:
                return base
            if t.addend % es == 0:
                return '&%s[%d]' % (base, t.addend // es)
            return '(const u8 *)%s + %d' % (base, t.addend)
        if t.addend == 0:
            return '&%s' % t.name
        return '(const u8 *)&%s + %d' % (t.name, t.addend)

    def need_overlay(self, name):
        if name not in self.overlays:
            self.overlays.append(name)

    # ..................................................................
    # Mechanical representation
    # ..................................................................
    def cells_of(self, obj):
        raw = self.raw(obj.section)
        cells = make_cells(obj, raw, self.elf.relocs.get(obj.section, {}))
        for c in cells:
            if c.reloc is not None:
                c.reloc = self.resolve(obj.section, c.off, c.value)
        return cells

    def slot_status(self, obj, cells):
        """Per 4-byte slot: 'P' pointer reloc, 'O' overlay id, 'Z' zero, 'N' other."""
        raw = self.raw(obj.section)
        n = obj.size // 4
        st = []
        rel_at = {c.off: c for c in cells if c.reloc is not None}
        for i in range(n):
            off = obj.start + 4 * i
            c = rel_at.get(off)
            if c is not None:
                st.append('O' if c.reloc.kind == 'overlay' else 'P')
            elif raw[off:off + 4] == b'\0\0\0\0':
                st.append('Z')
            else:
                st.append('N')
        return st

    def represent(self, obj):
        info = None
        if obj.name not in self.untyped:
            if obj.name in self.typed_info:
                info = self.typed_info[obj.name]
            elif obj.name in self.hint_types:
                info = (None, None, self.hint_types[obj.name])
        if info is not None:
            try:
                return self.represent_typed(obj, info)
            except TypedFail as e:
                self.notes.append('%s: kept untyped (%s)' % (obj.name, e))
                self.untyped.add(obj.name)
                if info[1] is not None:
                    self.mismatch[obj.name] = str(e)
        rep = self.represent_mechanical(obj)
        if obj.name in self.decl_names:
            self.mismatch.setdefault(obj.name, 's2c could not read that type (its header needs generated files)'
                                     if obj.name not in self.typed_info else 'that type does not describe the data')
        return rep

    def represent_typed(self, obj, info):
        include, decl, t = info
        const = obj.section == '.rodata'
        const_fix = None
        if is_const_object(t) != const:
            if decl is None:
                raise TypedFail('the inferred type has the wrong constness')
            const_fix = 'add' if const else 'remove'
            decl = toggle_const(decl, obj.name, const_fix)
        if contains_wide(t) and (obj.section != '.bss' or t.kind == 'array' and t.count is None or t.size != obj.size):
            raise TypedFail('it has 64-bit members, whose layout MWCC and GCC may not agree on')
        al = type_align(t)
        if obj.start % al:
            raise TypedFail('that type needs %d-byte alignment and the data sits at offset %#x' % (al, obj.start))
        raw = self.raw(obj.section)
        is_array = t.kind == 'array'
        count = None
        if is_array:
            es = t.target.size
            if es == 0:
                raise TypedFail('its elements have no size')
            count = t.count if t.count is not None else obj.size // es
            if count == 0:
                raise TypedFail('one element of that type is larger than the data under this label')
            size = count * es
        else:
            if getattr(t, 'incomplete', False) or t.kind in ('func', 'void'):
                raise TypedFail('that type is incomplete')
            size = t.size
        if size > obj.size:
            raise TypedFail('that type is %#x bytes and the label covers only %#x (later labels overlap it)' % (size, obj.size))
        rels = self.elf.relocs.get(obj.section, {})
        if any(raw[obj.start + size:obj.end]) or any(obj.start + size <= r < obj.end for r in rels):
            raise TypedFail('the label holds %d more bytes of data after it' % (obj.end - obj.start - size))
        rep = Rep('typed')
        rep.align = al
        rep.elem_size = t.target.size if is_array else size
        rep.typed = {'array': is_array, 'type': t, 'count': count, 'size': size, 'from_hint': decl is None,
                     'include': include, 'const_fix': const_fix}
        if const_fix:
            self.renamed.append(obj.name)
            obj.comments.append('C declares this %sconst, but it lives in %s' % ('non-' if const_fix == 'add' else '',
                                                                                 obj.section))
        if is_array and decl is not None:
            # spell out the length: uninitialised arrays need it, and an initialiser that stops
            # early (a string) would make the array shorter than the data
            decl = re.sub(r'(%s\s*)\[\s*\]' % re.escape(obj.name), r'\g<1>[%d]' % count, decl)
        if decl is not None:
            rep.decl_text = decl
        else:
            elem = t.target if is_array else t
            base = elem
            # spell without top-level const; the section decides
            if base.const:
                b2 = CType(base.kind)
                b2.__dict__.update(base.__dict__)
                b2.const = False
                base = b2
            rep.decl_text = spell(base, '%s%s' % ('NAME', '[%d]' % count if is_array else ''))
            rep.decl_text = ('const ' if const else '') + rep.decl_text
        if obj.section == '.bss':
            return rep
        cells = self.cells_of(obj)
        b = TypedBuilder(self, obj, cells, raw)
        mark = len(self.sjis_seen)
        node = b.array(t, obj.start, count) if is_array else b.build(t, obj.start)
        b.check_covered(obj.start, obj.start + size)
        rep.node = node
        if len(self.sjis_seen) > mark:
            rep.sjis = ' / '.join(self.sjis_seen[mark:])
        return rep

    ROW_NOTE = ('MWCC gives a char array a section of its own, which the linker starts 4-aligned; to '
                'stay at offset %#x next to its neighbours it is written as the only row of a 2-D array, '
                'which shares their section')

    def represent_mechanical(self, obj):
        rep = self.represent_mechanical_kind(obj)
        if obj.name in self.rows and rep.kind in ('array', 'string', 'bss') and rep.elem.w == 1:
            rep.row = True
            if obj.name in self.decl_names:
                self.mismatch[obj.name] = self.ROW_NOTE % obj.start
            elif not any(c.startswith('MWCC gives a char array') for c in obj.comments):
                obj.comments.append(self.ROW_NOTE % obj.start + '.')
        return rep

    def represent_mechanical_kind(self, obj):
        if getattr(obj, 'is_pad', False) and obj.section != '.bss':
            rep = Rep('array')
            rep.elem = Field(0, 'u8', obj.size, 'num', 1)
            rep.count = obj.size
            rep.init = ['0']
            return rep
        if obj.section == '.bss':
            rep = Rep('bss')
            rep.elem = Field(0, 'u8', obj.size, 'num', 1)
            rep.count = obj.size
            rep.align = 1
            return rep
        cells = self.cells_of(obj)
        if not cells:
            raise S2CError('%s: empty object %s' % (self.asm.path, obj.names))
        if any(c.reloc is not None for c in cells):
            return self.represent_pointers(obj, cells)
        kinds = set(c.kind for c in cells)
        if 'str' in kinds and kinds <= {'str', 'zero'}:
            rep = Rep('string')
            rep.elem = Field(0, 'char', obj.size, 'char', 1)
            rep.count = obj.size
            data = b''.join(c.data for c in cells)
            rep.init = c_string(data[:-1] if data.endswith(b'\0') else data)
            rep.sjis = sjis_text(data)
            return rep
        nums = [c for c in cells if c.kind == 'num']
        widths = set(c.w for c in nums)
        if kinds == {'num'} and len(widths) == 1:
            w = widths.pop()
            if obj.start % w == 0:
                return self.numeric_array(obj, cells, w)
        if kinds == {'zero'}:
            return self.numeric_array(obj, cells, 1)
        fields = self.fields_for(obj.start, obj.start, obj.end, cells)
        if fields is not None and len(fields) > 1:
            rep = Rep('struct')
            rep.fields = fields
            rep.align = max(f.w for f in fields)
            rep.init = self.struct_init(fields, cells, obj.start)
            return rep
        return self.numeric_array(obj, cells, 1)

    def numeric_array(self, obj, cells, w):
        rep = Rep('array')
        n = obj.size // w
        f = Field(0, UTYPE[w], n, 'num', w)
        self.choose_sign(f, [c for c in cells if c.kind == 'num' and c.w == w])
        rep.elem = f
        rep.count = n
        rep.align = w
        rep.elem_size = w
        vals = self.render_run(f, obj.start, obj.end, cells)
        rep.init = vals
        return rep

    # ..................................................................
    def choose_sign(self, field, cells):
        neg = False
        for c in cells:
            m = INT_LIT.match(c.text or '')
            if m and m.group(1):
                neg = True
        if not neg:
            return
        lim = 1 << (8 * field.w - 1)
        for c in cells:
            m = INT_LIT.match(c.text or '')
            if m:
                v = int(m.group(2), 0) * (-1 if m.group(1) else 1)
                if not -lim <= v < lim:
                    return       # mixes negative and large unsigned literals: stay unsigned
        field.signed = True
        field.ctype = STYPE[field.w]

    def fmt_value(self, field, value):
        w = field.w
        if field.signed and value >= 1 << (8 * w - 1):
            return str(value - (1 << (8 * w)))
        if field.signed:
            return str(value)
        return '0x%0*X' % (2 * w, value) if w > 1 or value > 9 else str(value)

    def cell_text(self, field, c):
        """Source text for a cell rendered into a field of the same width, or None."""
        t = (c.text or '').strip()
        if not t:
            return None
        m = INT_LIT.match(t)
        lim = 1 << (8 * field.w)
        if m:
            v = int(m.group(2), 0) * (-1 if m.group(1) else 1)
            if field.signed:
                if -(lim >> 1) <= v < (lim >> 1):
                    return t.replace(' ', '')
                return None
            if 0 <= v < lim:
                return t
            return None
        if IDENT.search(t) and C_EXPR_OK.match(t) and "'" not in t:
            return t
        return None

    def render_run(self, field, start, end, cells):
        """Comma-separated values for [start, end) rendered as field.w-sized elements."""
        raw = self.raw_for(start)
        by_off = {c.off: c for c in cells if c.kind == 'num'}
        out = []
        off = start
        while off < end:
            c = by_off.get(off)
            if c is not None and c.w == field.w and c.reloc is None:
                t = self.cell_text(field, c)
                out.append(t if t is not None else self.fmt_value(field, c.value))
            else:
                v = int.from_bytes(raw[off:off + field.w], 'little')
                out.append(self.fmt_value(field, v))
            off += field.w
        return out

    def raw_for(self, start):
        return self._raw_cur

    # ..................................................................
    def fields_for(self, base, start, end, cells):
        """Split the non-pointer range [start, end) into fields following the cells.

        Offsets are relative to base. Returns None when the cells cannot form a
        padding-free struct."""
        fields = []
        cs = [c for c in cells if start <= c.off < end]
        cs.sort(key=lambda c: c.off)
        pos = start
        i = 0
        while pos < end:
            c = cs[i] if i < len(cs) else None
            if c is None or c.off != pos:
                return None
            if c.kind == 'num':
                j = i
                while j + 1 < len(cs) and cs[j + 1].kind == 'num' and cs[j + 1].w == c.w and \
                        cs[j + 1].off == cs[j].off + c.w and cs[j + 1].off + c.w <= end:
                    j += 1
                n = j - i + 1
                if (pos - base) % c.w:
                    return None
                f = Field(pos - base, UTYPE[c.w], n if n > 1 else None, 'num', c.w)
                self.choose_sign(f, cs[i:j + 1])
            elif c.kind == 'str':
                j = i
                f = Field(pos - base, 'char', c.w, 'char', 1)
            else:
                j = i
                f = Field(pos - base, 'u8', c.w, 'num', 1)
            if c.off + (f.size) > end:
                return None
            fields.append(f)
            pos += f.size
            i = j + 1
        return fields

    def struct_init(self, fields, cells, base, elem_base=None):
        """Initializer (Node) for one struct instance located at base (absolute)."""
        return Node(items=[self.field_init(f, cells, base) for f in fields])

    def field_init(self, f, cells, base):
        start = base + f.off
        if f.kind in ('fptr', 'dptr', 'ovl'):
            c = next((c for c in cells if c.off == start), None)
            if c is None or c.reloc is None:
                v = int.from_bytes(self._raw_cur[start:start + 4], 'little')
                if v:
                    raise S2CError('non-zero value %#x in a pointer field at %#x' % (v, start))
                return Node('NULL' if f.kind != 'ovl' else '0')
            return Node(self.addr_expr(c.reloc, f.kind if f.kind != 'ovl' else 'u32'))
        if f.kind == 'char':
            data = self._raw_cur[start:start + f.size]
            return Node(c_string(data.rstrip(b'\0') if data.endswith(b'\0') else data))
        vals = self.render_run(f, start, start + f.size, cells)
        if f.count:
            if all(re.match(r'^(0x0+|0)$', v) for v in vals):
                return Node(items=[])
            return Node(items=[Node(v) for v in vals])
        return Node(vals[0])

    # ..................................................................
    def represent_pointers(self, obj, cells):
        if obj.start % 4:
            raise S2CError('%s: pointer data at unaligned offset in %s' % (self.asm.path, obj.name))
        for c in cells:
            if c.reloc is not None and (c.off - obj.start) % 4:
                raise S2CError('%s: unaligned pointer in %s' % (self.asm.path, obj.name))
        st = self.slot_status(obj, cells)
        nslots = len(st)
        tail = obj.size - 4 * nslots
        period = None
        for p in range(1, nslots + 1):
            if nslots % p or (tail and p != nslots):
                continue
            ok = True
            kinds = []
            for k in range(p):
                col = set(st[k::p])
                if 'P' in col and ('N' in col or 'O' in col):
                    ok = False
                    break
                if 'O' in col and ('N' in col or 'P' in col):
                    ok = False
                    break
                kinds.append('P' if 'P' in col else 'O' if 'O' in col else 'num')
            if ok:
                period = (p, kinds)
                break
        p, kinds = period
        esize = 4 * p if not tail else obj.size
        n = obj.size // esize
        # pointer kinds per position: function pointer if every target is a function
        elem_fields = []
        pos = 0
        base = obj.start
        while pos < esize:
            k = kinds[pos // 4] if pos // 4 < len(kinds) else 'num'
            if k in ('P', 'O'):
                if k == 'O':
                    elem_fields.append(Field(pos, 'u32', None, 'ovl', 4))
                else:
                    targets = []
                    for e in range(n):
                        c = next((c for c in cells if c.off == base + e * esize + pos), None)
                        if c is not None and c.reloc is not None:
                            targets.append(c.reloc)
                    func = all(t.kind == 'extern' and self.symidx.is_func(t.name) and t.addend == 0
                               for t in targets)
                    elem_fields.append(Field(pos, None, None, 'fptr' if func else 'dptr', 4))
                pos += 4
                continue
            end = pos
            while end < esize and (end // 4 >= len(kinds) or kinds[end // 4] == 'num'):
                end += 4
            end = min(end, esize)
            sub = self.fields_for(base, base + pos, base + end, cells)
            if sub is None:
                # fall back to bytes for this span
                sub = [Field(pos, 'u8', end - pos, 'num', 1)]
            elem_fields.extend(sub)
            pos = end
        rep = Rep('array' if (len(elem_fields) == 1 and n > 1) else ('structarray' if n > 1 else 'struct'))
        if len(elem_fields) == 1 and n == 1 and elem_fields[0].kind in ('fptr', 'dptr'):
            rep = Rep('struct')
        rep.align = max(4, max(f.w for f in elem_fields))
        if rep.kind == 'array':
            rep.elem = elem_fields[0]
            rep.count = n
            rep.elem_size = esize
            rep.init = [self.field_init(rep.elem, cells, base + e * esize - rep.elem.off).flat() for e in range(n)]
        elif rep.kind == 'structarray':
            rep.fields = elem_fields
            rep.count = n
            rep.elem_size = esize
            rep.init = Node(items=[self.struct_init(elem_fields, cells, base + e * esize) for e in range(n)])
        else:
            rep.fields = elem_fields
            rep.init = self.struct_init(elem_fields, cells, base)
        return rep

    # ..................................................................
    # Emission
    # ..................................................................
    def build(self):
        self.order = []
        for sname, objs in self.objs.items():
            self.order.extend(objs)
        # representations (two passes so addresses of later objects are known)
        for sname, objs in self.objs.items():
            self._raw_cur = self.raw(sname)
            for o in objs:
                if o.size == 0:
                    continue
                self.reps[o.name] = self.represent(o)
        self.fix_placement()
        for o in self.order:
            rep = self.reps.get(o.name)
            if rep is not None and rep.kind == 'typed' and not rep.typed['from_hint'] and not o.public_names:
                # the C code declares it extern, so it cannot be static
                o.public_names = {o.name}
                o.comments.append('global: C declares it extern although the asm label was local')
        self.reps_done = True
        return self

    def stripped_sections(self):
        """Sections the linker drops: none of their labels is used outside the file, nor by a section
        that stays (it keeps or drops an assembler's section whole, a compiler's objects one by one)."""
        live = {s: [o for o in objs if o.size] for s, objs in self.objs.items()}
        live = {s: objs for s, objs in live.items() if objs}

        def names(o):
            return list(o.names) + [n for n, owner, off in self.interior if owner == o.name]
        kept = set(s for s, objs in live.items() if s == '.version' or any(
            self.symidx.referenced_outside(n, self.own_path) for o in objs for n in names(o)))
        changed = True
        while changed:
            changed = False
            for s in list(kept):
                for rtype, sym in self.elf.relocs.get(s, {}).values():
                    t = sym if sym in DATA_SECTIONS else (self.by_name[sym].section if sym in self.by_name else None)
                    if t in live and t not in kept:
                        kept.add(t)
                        changed = True
        return set(live) - kept

    def c_size(self, o):
        rep = self.reps[o.name]
        if rep.kind == 'typed':
            return rep.typed.get('mw_size', rep.typed['size'])
        return o.size

    def insert_pad(self, after, end, comment):
        """A zero pad object from the end of `after` (as C sizes it) to end; an existing pad
        right after it is stretched instead."""
        objs = self.objs[after.section]
        start = after.start + self.c_size(after)
        i = objs.index(after)
        nxt = objs[i + 1] if i + 1 < len(objs) else None
        if getattr(after, 'is_pad', False):
            pad = after
            pad.comments.append(comment)
        elif nxt is not None and getattr(nxt, 'is_pad', False) and nxt.start <= end:
            pad = nxt
            pad.start = start
            pad.comments.append(comment)
        else:
            name = '%s_pad' % after.name
            while name in self.by_name:
                name += '_'
            pad = Obj(after.section, start, [name], False, after.line)
            pad.is_pad = True
            pad.end = end
            pad.comments = [comment]
            objs.insert(i + 1, pad)
            self.by_name[name] = pad
        if pad is not after and after.end > start:
            after.end = start
        pad.end = max(pad.end, end)
        self.reps[pad.name] = self.represent_mechanical(pad)
        return pad

    def adopt_mw_sizes(self, sizes):
        """MWCC's sizes for the typed objects (64-bit members are only 4-aligned there). A .bss
        object MWCC makes smaller is padded back out; anything else that differs is returned
        (it has to be written untyped)."""
        bad = []
        for sname, objs in self.objs.items():
            for o in list(objs):
                rep = self.reps.get(o.name)
                if rep is None or rep.kind != 'typed' or o.name not in sizes:
                    continue
                gnu, mw = rep.typed['size'], sizes[o.name]
                if mw == gnu:
                    continue
                if sname != '.bss' or mw > gnu:
                    bad.append(o.name)
                    continue
                end = o.start + gnu
                rep.typed['mw_size'] = mw
                self.insert_pad(o, end, 'MWCC makes %s %#x bytes (gcc: %#x); the asm reserves %#x'
                                % (o.name, mw, gnu, max(gnu, o.size)))
        return bad

    def fix_placement(self):
        """Typed objects can be shorter than their label (the asm spelled out padding).
        Recreate each gap with the next object's alignment when it is a natural one, else
        with a zero pad object, else give up the type."""
        for sname, objs in self.objs.items():
            self._raw_cur = self.raw(sname)
            changed = True
            while changed:
                changed = False
                live = [o for o in objs if o.size]
                for o in live:
                    o.align_need = 1
                for k, prev in enumerate(live):
                    if self.reps[prev.name].kind != 'typed':
                        continue
                    end = prev.start + self.c_size(prev)
                    nxt = live[k + 1] if k + 1 < len(live) else None
                    target = nxt.start if nxt is not None else prev.end
                    if end == target or (nxt is None and ((end + 3) & -4) == target):
                        continue
                    if nxt is not None:
                        rep = self.reps[nxt.name]
                        a = max(rep.align, self.wanted_align(nxt, rep) or 1)
                        while a <= 4 and ((end + a - 1) & -a) != target:
                            a *= 2
                        if a <= max(4, nxt.align_before) and target % a == 0 and ((end + a - 1) & -a) == target:
                            nxt.align_need = a
                            continue
                    if sname in ('.bss', '.rodata', '.data'):
                        pad = Obj(sname, end, ['%s_pad' % prev.name], False, prev.line)
                        pad.end = target
                        pad.is_pad = True
                        pad.comments = ['zero bytes after %s in the asm' % prev.name]
                        prev.end = end
                        objs.insert(objs.index(prev) + 1, pad)
                        self.reps[pad.name] = self.represent_mechanical(pad)
                        self.by_name[pad.name] = pad
                        changed = True
                        break
                    self.untyped.add(prev.name)
                    self.notes.append('%s: kept untyped (the %d bytes after it need an explicit spelling)'
                                      % (prev.name, target - end))
                    if prev.name in self.decl_names:
                        self.mismatch[prev.name] = 'the label also covers the %d zero bytes after it' % (target - end)
                    self.reps[prev.name] = self.represent_mechanical(prev)
                    changed = True
                    break
            self.order = [o for objs2 in self.objs.values() for o in objs2]

    def linkage(self, obj):
        return 'static ' if not obj.public_names else ''

    def type_and_name(self, obj, rep, const):
        """Declarator text for the object definition."""
        name = obj.name
        c = 'const ' if const else ''
        if rep.kind == 'typed':
            if rep.typed.get('from_hint'):
                return rep.decl_text.replace('NAME', name)
            return rep.decl_text
        row = '[1]' if getattr(rep, 'row', False) else ''
        if rep.kind == 'bss':
            return 'u8 %s%s[%d]' % (name, row, rep.count)
        if rep.kind in ('array', 'string'):
            f = rep.elem
            if f.kind == 'fptr':
                return 'void (*%s%s[%d])(void)' % (c, name, rep.count)
            if f.kind == 'dptr':
                return 'const void *%s%s[%d]' % (c, name, rep.count)
            if f.kind == 'ovl':
                return '%su32 %s[%d]' % (c, name, rep.count)
            return '%s%s %s%s[%d]' % (c, f.ctype, name, row, rep.count)
        if rep.kind in ('struct', 'structarray'):
            dims = '[%d]' % rep.count if rep.kind == 'structarray' else ''
            if getattr(rep, 'tag', None):
                return '%sstruct %s %s%s' % (c, rep.tag, name, dims)
            lines = ['%sstruct {' % c] + self.struct_body(rep) + ['} %s%s' % (name, dims)]
            return '\n'.join(lines)
        raise S2CError('unknown representation %s' % rep.kind)

    def struct_body(self, rep):
        return ['    %s;' % f.decl('unk%X' % f.off) for f in rep.fields]

    def wanted_align(self, obj, rep):
        if getattr(obj, 'plan_align', None) is not None:
            return obj.plan_align if obj.plan_align > rep.align else None
        want = max(obj.align_before, getattr(obj, 'align_need', 1))
        if obj.first_in_section:
            want = max(want, 4)
        if rep.kind in ('array', 'string', 'bss') and rep.align < 4 and not rep.typed:
            low = obj.start & -obj.start if obj.start else 4
            want = max(want, min(4, low))
        return want if want > rep.align else None

    def all_zero_data(self, obj):
        """Initialised data MWCC would move to .bss (its initialiser is all zero)."""
        if obj.section != '.data':
            return False
        end = obj.start + self.c_size(obj)
        rels = self.elf.relocs.get('.data', {})
        return not any(self.raw('.data')[obj.start:end]) and not any(obj.start <= r < end for r in rels)

    def render_object(self, obj):
        text = self.render_object_body(obj)
        if self.all_zero_data(obj):
            text = '#pragma explicit_zero_data on\n%s\n#pragma explicit_zero_data reset' % text
        return text

    def render_object_body(self, obj):
        rep = self.reps[obj.name]
        const = obj.section == '.rodata'
        out = []
        import textwrap
        for cmt in obj.comments:
            lines = textwrap.wrap(cmt, 97, break_long_words=False, break_on_hyphens=False) if cmt else ['']
            out.extend('// ' + l if l else '//' for l in lines)
        if getattr(rep, 'sjis', None):
            out.append('// Shift-JIS: "%s"' % rep.sjis)
        if obj.name in self.mismatch and rep.kind != 'typed':
            import textwrap
            d = self.decl_names.get(obj.name)
            if d:
                msg = 'C declares this as `%s`, but %s.' % (d, self.mismatch[obj.name])
            else:
                msg = '%s.' % self.mismatch[obj.name].capitalize()
            out.extend('// ' + l for l in textwrap.wrap(msg, 100, break_long_words=False, break_on_hyphens=False))
        decl = self.linkage(obj) + self.type_and_name(obj, rep, const)
        align = self.wanted_align(obj, rep)
        if align:
            decl += ' __attribute__((aligned(%d)))' % align
        if rep.kind == 'bss' or obj.section == '.bss':
            out.append(decl + ';')
            return '\n'.join(out)
        if rep.kind == 'typed':
            text = fmt_node(rep.node, 0, 110, len(decl.split('\n')[-1]) + 3)
            table = '\n' in text and rep.node.items is not None and all(i.items is None for i in rep.node.items)
            out.append(self.protect('%s = %s;' % (decl, text), table))
            return '\n'.join(out)
        init = rep.init
        table = False
        if isinstance(init, list):
            text = self.wrap_list(init, rep, len(decl) + 3)
            table = '\n' in text and rep.elem is not None and rep.elem.kind in ('num', 'char')
        elif isinstance(init, Node):
            text = fmt_node(init, 0, 110, len(decl.split('\n')[-1]) + 3)
        else:
            text = init
        if getattr(rep, 'row', False):
            text = '{ %s }' % text if '\n' not in text else '{\n%s\n}' % text
        out.append(self.protect('%s = %s;' % (decl, text), table))
        return '\n'.join(out)

    @staticmethod
    def protect(text, table):
        """clang-format would put every element of a long number table on its own line."""
        if not table:
            return text
        return '// clang-format off\n%s\n// clang-format on' % text

    def wrap_list(self, items, rep, lead=0):
        if not items:
            return '{ 0 }'
        if any(len(i) > 40 for i in items) or rep.kind == 'structarray' or \
                (rep.elem is not None and rep.elem.kind in ('fptr', 'dptr')):
            return '{\n' + ''.join('    %s,\n' % i for i in items) + '}'
        per = {1: 16, 2: 8, 4: 4}.get(rep.elem_size if rep.elem_size in (1, 2, 4) else 1, 8)
        if rep.elem is not None and rep.elem.kind == 'num':
            per = {1: 16, 2: 8, 4: 4}[rep.elem.w]
            if any(not INT_LIT.match(i) for i in items):
                per = max(1, per // 2)
        one = '{ ' + ', '.join(items) + ' }'
        if len(items) <= per and lead + len(one) <= 110:
            return one
        lines = []
        for i in range(0, len(items), per):
            lines.append('    ' + ', '.join(items[i:i + per]) + ',')
        return '{\n' + '\n'.join(lines) + '\n}'

    PLACEHOLDER = re.compile(r'@@([\w$?.]+)@(-?\d+)(?:@(\d+))?@@')

    SECTION_TITLES = {'.rodata': 'Read-only data', '.data': 'Initialised data', '.bss': 'Uninitialised data',
                      '.version': 'Middleware version strings'}

    def emit(self, orders=None):
        """Render all objects; returns the C file text. orders: section -> object names in the
        order to define them (default: the order of the asm)."""
        import itertools
        rendered = {}
        refs = {}
        for sname, objs in self.objs.items():
            for o in objs:
                if o.size == 0:
                    self.notes.append('zero-size label(s) %s at the end of %s dropped' % (', '.join(o.names), sname))
                    continue
                text = self.render_object(o)
                rendered[o.name] = text
                refs[o.name] = [m.group(1) for m in self.PLACEHOLDER.finditer(text)]
        live = [(sname, [o for o in objs if o.size]) for sname, objs in self.objs.items()]
        live = [(sname, objs) for sname, objs in live if objs]
        self.reordered = False
        if orders:
            for k, (sname, objs) in enumerate(live):
                if sname in orders:
                    want = [self.by_name[n] for n in orders[sname]]
                    assert sorted(id(o) for o in want) == sorted(id(o) for o in objs)
                    if want != objs:
                        self.reordered = True
                    live[k] = (sname, want)
        # section order with the fewest forward references (sections are laid out independently)
        best = None
        for perm in itertools.permutations(range(len(live))):
            seen = set()
            fwd = []
            for k in perm:
                for o in live[k][1]:
                    for r in refs[o.name]:
                        if r not in seen and r != o.name:
                            fwd.append((o.name, r))
                    seen.add(o.name)
            key = (len(fwd), list(perm) != sorted(perm))
            if best is None or key < best[0]:
                best = (key, perm, fwd)
        order = [live[k] for k in best[1]]
        self.forward = best[2]
        fwd_targets = OrderedDict()
        for user, target in self.forward:
            fwd_targets[target] = True
        promoted = set()
        tags = []
        for t in fwd_targets:
            rep = self.reps[t]
            if rep.kind in ('struct', 'structarray'):
                # an anonymous struct cannot be declared twice: name its layout
                rep.tag = t + '_Layout'
                tags.append('struct %s {\n%s\n};' % (rep.tag, '\n'.join(self.struct_body(rep))))
                rendered[t] = self.render_object(self.by_name[t])
        for t in fwd_targets:
            o = self.by_name[t]
            if not o.public_names:
                promoted.add(t)
                o.public_names = {t}
                if 'not static: used above its definition' not in o.comments:
                    o.comments.append('not static: used above its definition')
                rendered[t] = self.render_object(o)
        self.promoted = promoted
        sections = []
        for sname, objs in order:
            body = ['// %s (%s)' % (self.SECTION_TITLES[sname], sname), '']
            if sname == '.version':
                body += ['#pragma section VERSION begin', '']
            for o in objs:
                body.append((o.name, self.PLACEHOLDER.sub(self.sub_placeholder, rendered[o.name])))
                body.append('')
            if sname == '.version':
                body += ['#pragma section VERSION end', '']
            sections.append(body)
        fwd_decls = []
        for t in fwd_targets:
            o = self.by_name[t]
            rep = self.reps[t]
            decl = self.type_and_name(o, rep, o.section == '.rodata')
            if rep.kind in ('array', 'string', 'bss', 'structarray') and not getattr(rep, 'row', False):
                decl = re.sub(r'\[\d+\]((?:\)\(void\))?)$', r'[]\1', decl)
            fwd_decls.append('extern %s;' % decl)
        return self.file_text(sections, tags + fwd_decls)

    def emit_plan(self, tus):
        """Texts of the files of a layout plan: tus = [(initialised objects, .bss objects) in
        definition order] per file. Returns [(text, line map)]."""
        tu_of = {}
        for k, (ini, bss, keep) in enumerate(tus):
            for n in ini + bss:
                tu_of[n] = k
        refs = {}
        for n in tu_of:
            refs[n] = [m.group(1) for m in self.PLACEHOLDER.finditer(self.render_object(self.by_name[n]))]
        decls = [OrderedDict() for _ in tus]
        cross = set()
        for k, (ini, bss, keep) in enumerate(tus):
            seen = set()
            for n in ini + bss:
                for r in refs[n]:
                    if r != n and (tu_of[r] != k or r not in seen):
                        decls[k][r] = True
                        if tu_of[r] != k:
                            cross.add(r)
                seen.add(n)
        needed = set(r for d in decls for r in d)
        for n in sorted(needed):
            o = self.by_name[n]
            if not o.public_names:
                o.public_names = {n}
                why = 'not static: used in another part of asm/%s.s' % self.asm.name if n in cross \
                    else 'not static: used above its definition'
                o.comments.append(why)
            rep = self.reps[n]
            if rep.kind in ('struct', 'structarray') and not getattr(rep, 'tag', None):
                rep.tag = n + '_Layout'
        for n in tu_of:
            o = self.by_name[n]
            rep = self.reps[n]
            if not o.public_names and o.section == '.rodata' and rep.kind == 'typed' and not rep.typed['array'] \
                    and strip_quals(rep.typed['type']).kind in ('base', 'enum', 'ptr'):
                o.public_names = {n}
                o.comments.append('not static: MWCC drops unused static constants')
        self.reordered = True
        out = []
        for k, (ini, bss, keep) in enumerate(tus):
            tags = []
            for n in list(decls[k]) + ini + bss:
                rep = self.reps[n]
                if getattr(rep, 'tag', None) and rep.tag not in [t[0] for t in tags]:
                    tags.append((rep.tag, 'struct %s {\n%s\n};' % (rep.tag, '\n'.join(self.struct_body(rep)))))
            fwd = []
            for n in decls[k]:
                o = self.by_name[n]
                rep = self.reps[n]
                decl = self.type_and_name(o, rep, o.section == '.rodata')
                if rep.kind in ('array', 'string', 'bss', 'structarray') and not getattr(rep, 'row', False):
                    decl = re.sub(r'\[\d+\]((?:\)\(void\))?)$', r'[]\1', decl)
                fwd.append('extern %s;' % decl)
            body = []
            for n in ini:
                o = self.by_name[n]
                text = self.PLACEHOLDER.sub(self.sub_placeholder, self.render_object(o))
                if o.section == '.version':
                    text = '#pragma section VERSION begin\n%s\n#pragma section VERSION end' % text
                body.append((n, text))
                body.append('')
            for n in bss:
                body.append((n, self.PLACEHOLDER.sub(self.sub_placeholder, self.render_object(self.by_name[n]))))
                body.append('')
            part = None if len(tus) == 1 else (k + 1, len(tus))
            text = self.file_text([body], [t for _, t in tags] + fwd, part, keep)
            out.append((text, list(self.line_map)))
        return out

    def file_text(self, sections, fwd_decls, part=None, keep=True):
        if part:
            out = ['// Converted from asm/%s.s (part %d of %d) by tools/s2c.py.' % ((self.asm.name,) + part)]
        else:
            out = ['// Converted from asm/%s.s by tools/s2c.py.' % self.asm.name]
        if self.reordered:
            import textwrap
            msg = ('MWCC sorts the data of a file by size before laying it out, so the definitions are in '
                   'the order that makes the sort reproduce the asm layout%s. Keep that when editing, or '
                   'rerun tools/s2c.py.' % (', and the data is split across files where one sort cannot'
                                             if part else ''))
            out += ['//'] + ['// ' + l for l in textwrap.wrap(msg, 97)]
        for c in self.asm.top_comments:
            out.append('// ' + c)
        out.append('')
        used = '\n'.join(b[1] if isinstance(b, tuple) else b for body in sections for b in body)
        used += '\n' + '\n'.join(fwd_decls)

        def mentioned(n):
            return re.search(r'(?<![\w$])%s(?![\w$])' % re.escape(n), used) is not None
        renames = [n for n in self.all_renames() if not part or mentioned(n)]
        if renames:
            out.append('// The C declarations of these do not match the data (see the notes at each')
            out.append('// definition): keep them out of the way of the definitions below.')
            for n in renames:
                out.append('#define %s %s_header_decl' % (n, n))
            out.append('')
        out.append('#include "global.h"')
        out.append('')
        incs = [i for i in self.asm.cpp_includes if i.strip('"<>') != 'config.h']
        extra = [i for i in self.includes if i not in incs]
        if incs or extra:
            for i in incs + extra:
                out.append('#include %s' % i)
            out.append('')
        if '.version' in self.objs and '#pragma section VERSION' in used:
            out.append('#include <nitro/section.h>')
            out.append('')
        if re.search(r'[A-Za-z_]\w*\$', used):
            out.append('#pragma dollar_identifiers on')
            out.append('')
        if keep:
            # the linker drops objects nothing uses; the asm's sections stayed whole
            out.append('#pragma force_active on')
            out.append('')
        else:
            out.append('// Nothing uses these: the linker drops them, as it dropped their asm section.')
            out.append('')
        if renames:
            for n in renames:
                out.append('#undef %s' % n)
            out.append('')
        overlays = [ov for ov in self.overlays if not part or mentioned(ov)]
        if overlays:
            for ov in overlays:
                out.append('FS_EXTERN_OVERLAY(%s);' % ov)
            out.append('')
        funcs = [n for n in sorted(self.extern_funcs) if not part or mentioned(n)]
        data = [n for n in sorted(self.extern_data) if not part or mentioned(n)]
        if funcs or data:
            for n in funcs:
                out.append('extern void %s(void);' % n)
            for n in data:
                out.append('extern const u8 %s[];' % n)
            out.append('')
        if fwd_decls:
            out.extend(fwd_decls)
            out.append('')
        self.line_map = []          # (first line, last line, object name), 1-based
        lines = list(out)
        for body in sections:
            for blk in body:
                if isinstance(blk, tuple):
                    name, txt = blk
                    first = len(lines) + 1
                    lines.extend(txt.split('\n'))
                    self.line_map.append((first, len(lines), name))
                else:
                    lines.append(blk)
        self.header_lines = len(out)
        text = '\n'.join(lines).rstrip() + '\n'
        return text

    def all_renames(self):
        names = list(self.renamed)
        for n in self.mismatch:
            if n in self.reps and self.reps[n].kind != 'typed' and n not in names:
                names.append(n)
        return names

    def object_at_line(self, line):
        for a, b, name in self.line_map:
            if a <= line <= b:
                return name
        return None


# --------------------------------------------------------------------------------------
# Typed definitions: use the declarations the C code already has
# --------------------------------------------------------------------------------------

class TypedFail(Exception):
    pass


BASIC_TYPES = {'u8', 'u16', 'u32', 's8', 's16', 's32', 'int', 'char', 'fx32', 'fx16', 'u64', 's64',
               'BOOL', 'unsigned', 'short', 'long', 'vu8', 'vu16', 'vu32', 'unk32', 'f32', 'u16 *', 'void'}


class DeclIndex:
    """extern declarations of the labels, found in headers and C files."""

    DECL = re.compile(r'^\s*extern\s+([^;]*?)\s*;')

    def __init__(self, root, names):
        self.decls = defaultdict(list)    # name -> [(file, decltext)]
        names = set(names)
        ident = re.compile(r'[A-Za-z_$][\w$]*')
        files = list(root.glob('include/**/*.h')) + list(root.glob('src/**/*.h')) + list(root.glob('src/**/*.c')) \
            + list(root.glob('lib/include/**/*.h')) + list(root.glob('lib/**/*.c'))
        for f in files:
            try:
                txt = f.read_text(errors='replace')
            except OSError:
                continue
            for line in txt.splitlines():
                m = self.DECL.match(line)
                if not m:
                    continue
                body = m.group(1)
                if ',' in body.split('(')[0] or '=' in body:
                    continue
                found = [t for t in ident.findall(body) if t in names]
                if len(found) != 1:
                    continue
                self.decls[found[0]].append((str(f.relative_to(root)), body))

    def best(self, name):
        """(include path or None, declaration text) for a name, or None."""
        cands = self.decls.get(name, [])
        if not cands:
            return None
        texts = set(re.sub(r'\s+', ' ', d) for _, d in cands)
        headers = [(f, d) for f, d in cands if f.endswith('.h')]
        if headers:
            htexts = set(re.sub(r'\s+', ' ', d) for _, d in headers)
            if len(htexts) > 1:
                return None
            f, d = headers[0]
            return (header_include_path(f), d)
        if len(texts) > 1:
            return None
        f, d = cands[0]
        return (None, d)


def header_include_path(f):
    for prefix in ('include/library/', 'include/', 'src/', 'lib/include/'):
        if f.startswith(prefix):
            return '"%s"' % f[len(prefix):]
    return '"%s"' % f


class CType:
    def __init__(self, kind, **kw):
        self.kind = kind     # base enum ptr struct union array func void
        self.name = None     # typedef or tag spelling
        self.const = False
        self.size = 0
        self.align = 1
        self.signed = False
        self.encoding = 'int'
        self.target = None
        self.count = None
        self.members = []
        self.params = []
        self.ret = None
        self.variadic = False
        self.__dict__.update(kw)

    def __repr__(self):
        return '<CType %s %s size=%s>' % (self.kind, self.name, self.size)


class DwarfTypes:
    """Read variable types from a probe object's DWARF."""

    def __init__(self, obj_path):
        from elftools.elf.elffile import ELFFile
        self.memo = {}
        self.vars = {}
        with open(obj_path, 'rb') as fh:
            elf = ELFFile(fh)
            dw = elf.get_dwarf_info()
            for cu in dw.iter_CUs():
                for die in cu.iter_DIEs():
                    if die.tag == 'DW_TAG_variable' and 'DW_AT_name' in die.attributes:
                        name = die.attributes['DW_AT_name'].value.decode()
                        if name.startswith('s2c_probe_') and 'DW_AT_type' in die.attributes:
                            ptr = die.get_DIE_from_attribute('DW_AT_type')
                            target = ptr.get_DIE_from_attribute('DW_AT_type')
                            self.vars[name[len('s2c_probe_'):]] = self.convert(target)
        self.refresh_wrappers()

    OWN = ('name', 'const', 'qual_of', 'typedef_of', 'volatile')

    def refresh_wrappers(self):
        """Typedef/const wrappers copy their inner type when created, which can be before a
        recursive struct is complete; copy the finished fields again."""
        for _ in range(8):
            changed = False
            for t in self.memo.values():
                inner = getattr(t, 'qual_of', None) or getattr(t, 'typedef_of', None)
                if inner is None:
                    continue
                for k, v in inner.__dict__.items():
                    if k in self.OWN:
                        continue
                    if k == 'align' and getattr(t, 'explicit_align', False):
                        continue
                    if t.__dict__.get(k) is not v and t.__dict__.get(k) != v:
                        t.__dict__[k] = v
                        changed = True
            if not changed:
                break

    def convert(self, die):
        key = die.offset
        if key in self.memo:
            return self.memo[key]
        tag = die.tag
        name = die.attributes['DW_AT_name'].value.decode() if 'DW_AT_name' in die.attributes else None
        if tag in ('DW_TAG_typedef', 'DW_TAG_const_type', 'DW_TAG_volatile_type'):
            inner = self.convert(die.get_DIE_from_attribute('DW_AT_type')) if 'DW_AT_type' in die.attributes \
                else CType('void', name='void')
            t = CType(inner.kind)
            t.__dict__.update(inner.__dict__)
            if tag == 'DW_TAG_typedef':
                t.name = name
                t.typedef_of = inner
            elif tag == 'DW_TAG_const_type':
                t.const = True
                t.qual_of = inner
            else:
                t.qual_of = inner
                t.volatile = True
            if 'DW_AT_alignment' in die.attributes:
                t.align = die.attributes['DW_AT_alignment'].value
                t.explicit_align = True
            self.memo[key] = t
            return t
        if tag == 'DW_TAG_base_type':
            enc = die.attributes['DW_AT_encoding'].value
            size = die.attributes['DW_AT_byte_size'].value
            t = CType('base', name=name, size=size, align=min(size, 8))
            t.signed = enc in (5, 6, 0xd)       # signed, signed_char, signed_fixed
            t.encoding = {4: 'float', 2: 'bool', 6: 'char', 8: 'char'}.get(enc, 'int')
            if name == 'char':
                t.encoding = 'char'
        elif tag == 'DW_TAG_enumeration_type':
            size = die.attributes['DW_AT_byte_size'].value
            t = CType('enum', size=size, align=size, signed=True)
            t.name = ('enum ' + name) if name else None
            t.enumerators = {}
            for c in die.iter_children():
                if c.tag == 'DW_TAG_enumerator':
                    t.enumerators.setdefault(c.attributes['DW_AT_const_value'].value,
                                             c.attributes['DW_AT_name'].value.decode())
        elif tag == 'DW_TAG_pointer_type':
            t = CType('ptr', size=4, align=4)
            self.memo[key] = t
            t.target = self.convert(die.get_DIE_from_attribute('DW_AT_type')) if 'DW_AT_type' in die.attributes \
                else CType('void', name='void')
            return t
        elif tag in ('DW_TAG_structure_type', 'DW_TAG_union_type'):
            kind = 'struct' if tag == 'DW_TAG_structure_type' else 'union'
            t = CType(kind)
            t.name = ('%s %s' % (kind, name)) if name else None
            self.memo[key] = t
            if die.attributes.get('DW_AT_declaration'):
                t.incomplete = True
                return t
            t.size = die.attributes['DW_AT_byte_size'].value
            al = 1
            for c in die.iter_children():
                if c.tag != 'DW_TAG_member':
                    continue
                mt = self.convert(c.get_DIE_from_attribute('DW_AT_type'))
                mname = c.attributes['DW_AT_name'].value.decode() if 'DW_AT_name' in c.attributes else None
                if 'DW_AT_data_bit_offset' in c.attributes:
                    bitoff = c.attributes['DW_AT_data_bit_offset'].value
                    off = None
                else:
                    off = c.attributes['DW_AT_data_member_location'].value if 'DW_AT_data_member_location' in c.attributes else 0
                    bitoff = None
                bits = c.attributes['DW_AT_bit_size'].value if 'DW_AT_bit_size' in c.attributes else None
                if bits is not None and bitoff is None:
                    if 'DW_AT_bit_offset' in c.attributes:
                        stor = c.attributes['DW_AT_byte_size'].value if 'DW_AT_byte_size' in c.attributes else mt.size
                        bitoff = off * 8 + stor * 8 - c.attributes['DW_AT_bit_offset'].value - bits
                    else:
                        bitoff = off * 8
                if bits is None:
                    t.members.append((mname, off, mt, None, None))
                else:
                    t.members.append((mname, bitoff // 8, mt, bits, bitoff))
                al = max(al, mt.align)
            t.align = die.attributes['DW_AT_alignment'].value if 'DW_AT_alignment' in die.attributes else al
            return t
        elif tag == 'DW_TAG_array_type':
            elem = self.convert(die.get_DIE_from_attribute('DW_AT_type'))
            dims = []
            for c in die.iter_children():
                if c.tag == 'DW_TAG_subrange_type':
                    if 'DW_AT_count' in c.attributes:
                        dims.append(c.attributes['DW_AT_count'].value)
                    elif 'DW_AT_upper_bound' in c.attributes:
                        dims.append(c.attributes['DW_AT_upper_bound'].value + 1)
                    else:
                        dims.append(None)
            t = elem
            for d in reversed(dims):
                t = CType('array', target=t, count=d, size=(t.size * d if d is not None else 0), align=t.align)
            self.memo[key] = t
            return t
        elif tag == 'DW_TAG_subroutine_type':
            t = CType('func', size=1, align=1)
            self.memo[key] = t
            t.ret = self.convert(die.get_DIE_from_attribute('DW_AT_type')) if 'DW_AT_type' in die.attributes \
                else CType('void', name='void')
            for c in die.iter_children():
                if c.tag == 'DW_TAG_formal_parameter':
                    t.params.append(self.convert(c.get_DIE_from_attribute('DW_AT_type')))
                elif c.tag == 'DW_TAG_unspecified_parameters':
                    t.variadic = True
            t.prototyped = bool(die.attributes.get('DW_AT_prototyped'))
            return t
        else:
            raise TypedFail('unsupported DWARF tag %s' % tag)
        self.memo[key] = t
        return t


def spell(t, inner=''):
    """C spelling of a type with an inner declarator."""
    q = 'const ' if t.const else ''
    if t.name and t.kind != 'array':
        return ('%s%s %s' % (q, t.name, inner)).strip()
    if t.kind == 'void':
        return ('%svoid %s' % (q, inner)).strip()
    if t.kind == 'ptr':
        cq = ' const' if t.const else ''
        tgt = t.target
        if tgt.kind in ('array', 'func') and not tgt.name:
            return spell(tgt, '(*%s%s)' % (cq.strip() + ' ' if cq else '', inner))
        return spell(tgt, '*%s%s' % (cq.strip() + ' ' if cq else '', inner))
    if t.kind == 'array':
        return spell(t.target, '%s[%s]' % (inner, t.count if t.count is not None else ''))
    if t.kind == 'func':
        params = ', '.join(spell(p) for p in t.params) or ('void' if getattr(t, 'prototyped', True) else '')
        if t.variadic:
            params += ', ...'
        return spell(t.ret, '%s(%s)' % (inner, params))
    raise TypedFail('cannot spell an anonymous %s' % t.kind)


def toggle_const(decl, name, how):
    """Add or remove the const that makes the declared object itself read-only."""
    n = re.escape(name)
    if how == 'add':
        if re.search(r'\*\s*%s\b' % n, decl):
            return re.sub(r'(\*\s*)(%s\b)' % n, r'\1const \2', decl, count=1)
        return 'const ' + decl
    if re.search(r'\*\s*const\s+%s\b' % n, decl):
        return re.sub(r'(\*\s*)const\s+(%s\b)' % n, r'\1\2', decl, count=1)
    return re.sub(r'^\s*const\s+', '', decl, count=1)


def unconst(t):
    if not t.const:
        return t
    u = CType(t.kind)
    u.__dict__.update(t.__dict__)
    u.const = False
    return u


def strip_quals(t):
    while getattr(t, 'qual_of', None) is not None or getattr(t, 'typedef_of', None) is not None:
        t = getattr(t, 'qual_of', None) or getattr(t, 'typedef_of', None)
    return t


def is_const_object(t):
    """Is the object itself const (lands in .rodata)?"""
    while True:
        if t.const:
            return True
        if t.kind == 'array':
            t = t.target
            continue
        inner = getattr(t, 'qual_of', None) or getattr(t, 'typedef_of', None)
        if inner is None:
            return False
        t = inner


def type_align(t):
    if t.kind in ('struct', 'union', 'base', 'enum'):
        return t.align
    if t.kind == 'array':
        return type_align(t.target)
    if t.kind == 'ptr':
        return 4
    return t.align or 1


def contains_wide(t, seen=None):
    """Types whose MWCC layout we do not trust gcc to mirror (64-bit scalars)."""
    seen = seen or set()
    if id(t) in seen:
        return False
    seen.add(id(t))
    if t.kind == 'base' and t.size > 4:
        return True
    if t.kind == 'array':
        return contains_wide(t.target, seen)
    if t.kind in ('struct', 'union'):
        return any(contains_wide(m[2], seen) for m in t.members)
    return False


class Node:
    """Initializer tree: a scalar text or a list of nodes (optionally designated)."""

    def __init__(self, text=None, items=None, desig=None):
        self.text = text
        self.items = items
        self.desig = desig

    def flat(self):
        if self.items is None:
            s = self.text
        else:
            s = '{ ' + ', '.join(i.flat() for i in self.items) + ' }' if self.items else '{ 0 }'
        return ('.%s = %s' % (self.desig, s)) if self.desig else s

    def is_zero(self):
        if self.items is None:
            return self.text in ('0', 'NULL', '0x00', '0x0000', '0x00000000', '""')
        return all(i.is_zero() for i in self.items)


def fmt_node(node, indent=0, width=110, lead=0):
    flat = node.flat()
    # clang-format (AlignArrayOfStructures) mangles a one-line top-level initializer that
    # mixes scalars and braces, so those always get one member per line
    mixed = node.items is not None and indent == 0 and any(i.items is not None for i in node.items) \
        and any(i.items is None for i in node.items)
    if node.items is None or (len(flat) + indent + lead <= width and not mixed):
        return flat
    pre = ('.%s = ' % node.desig) if node.desig else ''
    pad = ' ' * (indent + 4)
    if all(i.items is None for i in node.items):
        # wrap scalars several per line
        lines = []
        cur = ''
        for i in node.items:
            t = i.flat() + ','
            if cur and len(pad) + len(cur) + 1 + len(t) > width:
                lines.append(pad + cur)
                cur = t
            else:
                cur = (cur + ' ' + t) if cur else t
        if cur:
            lines.append(pad + cur)
        return pre + '{\n' + '\n'.join(lines) + '\n' + ' ' * indent + '}'
    return pre + '{\n' + ''.join(pad + fmt_node(i, indent + 4, width) + ',\n' for i in node.items) + ' ' * indent + '}'


class TypedBuilder:
    """Builds the initializer of one object from its bytes, following a C type."""

    def __init__(self, gen, obj, cells, raw):
        self.gen = gen
        self.obj = obj
        self.raw = raw
        self.cells = {c.off: c for c in cells}
        self.str_cells = [c for c in cells if c.kind == 'str']
        self.covered = bytearray(len(raw))   # bitmask per byte of explained bits
        self.casts = gen.force_casts.get(obj.name, False)

    def mark(self, off, size, mask=None):
        for i in range(size):
            self.covered[off + i] |= 0xFF if mask is None else (mask >> (8 * i)) & 0xFF

    def check_covered(self, start, end):
        for i in range(start, end):
            if self.raw[i] & ~self.covered[i] & 0xFF:
                raise TypedFail('byte %#x is padding in that type but holds %#x' % (i - self.obj.start, self.raw[i]))

    def build(self, t, off):
        k = t.kind
        if k == 'array':
            return self.array(t, off, t.count)
        if k in ('struct', 'union'):
            if getattr(t, 'incomplete', False):
                raise TypedFail('incomplete struct')
            return self.struct(t, off) if k == 'struct' else self.union(t, off)
        if k == 'ptr':
            return self.pointer(t, off)
        if k in ('base', 'enum'):
            return self.scalar(t, off)
        raise TypedFail('cannot initialise %s' % k)

    def array(self, t, off, count):
        el = t.target
        es = el.size
        if es == 0:
            raise TypedFail('zero-size element')
        base = strip_quals(el)
        if base.kind == 'base' and base.encoding == 'char' and base.size == 1:
            data = self.raw[off:off + count]
            if self.looks_like_string(off, count):
                self.mark(off, count)
                if sjis_text(data):
                    self.gen.sjis_seen.append(sjis_text(data))
                body = data
                while body.endswith(b'\0'):
                    body = body[:-1]
                return Node(c_string(body))
        items = [self.build(el, off + i * es) for i in range(count)]
        # trailing zero elements may be left to C's zero fill
        return Node(items=items)

    def looks_like_string(self, off, count):
        for c in self.str_cells:
            if off <= c.off < off + count:
                return True
        data = self.raw[off:off + count]
        body = data.rstrip(b'\0')
        return len(body) >= 2 and all(0x20 <= b < 0x7F for b in body)

    def struct(self, t, off):
        items = []
        for (mname, moff, mt, bits, bitoff) in t.members:
            if bits is not None:
                items.append(self.bitfield(mt, off, bitoff, bits))
            else:
                items.append(self.build(mt, off + moff))
        return Node(items=items)

    def bitfield(self, mt, off, bitoff, bits):
        base = strip_quals(mt)
        start = off + bitoff // 8
        nbytes = (bitoff % 8 + bits + 7) // 8
        word = int.from_bytes(self.raw[start:start + nbytes], 'little')
        shift = bitoff % 8
        v = (word >> shift) & ((1 << bits) - 1)
        self.mark(start, nbytes, ((1 << bits) - 1) << shift)
        if base.signed and base.kind != 'enum' and v >> (bits - 1):
            v -= 1 << bits
        if (off + bitoff // 8) in self.rel_offsets():
            raise TypedFail('an address sits in a bitfield of that type')
        if base.kind == 'enum':
            return self.enum_value(mt, base, v)
        return Node(str(v) if abs(v) < 10 or base.signed else '0x%X' % v)

    def rel_offsets(self):
        return set(o for o, c in self.cells.items() if c.reloc is not None)

    def union(self, t, off):
        saved = bytes(self.covered)
        last = None
        for i, (mname, moff, mt, bits, bitoff) in enumerate(t.members):
            self.covered[:] = saved
            try:
                n = self.build(mt, off + moff)
                self.check_covered(off, off + t.size)
            except TypedFail as e:
                last = e
                continue
            if i:
                if not mname:
                    raise TypedFail('anonymous union member')
                n.desig = mname
            return n
        self.covered[:] = saved
        raise TypedFail('no member of a union in that type explains its bytes (%s)' % last)

    def scalar(self, t, off):
        base = strip_quals(t)
        size = base.size
        cell = self.cells.get(off)
        if cell is not None and cell.reloc is not None:
            if size != 4:
                raise TypedFail('an address sits where that type has a %d-byte field' % size)
            self.mark(off, 4)
            tg = cell.reloc
            if tg.kind == 'overlay':
                return Node(self.gen.addr_expr(tg, 'u32'))
            # an address in an integer field would not survive a 64-bit build: keep the
            # pointer and let the declaration be fixed instead
            raise TypedFail('an address sits where that type has an integer field')
        for r in self.rel_offsets():
            if off < r + 4 and r < off + size:
                raise TypedFail('an address straddles fields of that type')
        self.mark(off, size)
        raw = self.raw[off:off + size]
        if base.encoding == 'float':
            import struct as st
            if size == 4:
                v = st.unpack('<f', raw)[0]
                txt = repr(v)
                if st.pack('<f', float(txt)) != raw:
                    raise TypedFail('float not representable')
                return Node(txt + 'f')
            v = st.unpack('<d', raw)[0]
            return Node(repr(v))
        v = int.from_bytes(raw, 'little', signed=base.signed)
        if base.kind == 'enum':
            # MWCC refuses int -> enum without a cast, even in C
            return self.enum_value(t, base, v)
        if cell is not None and cell.kind == 'num' and cell.w == size:
            f = Field(0, None, None, 'num', size)
            f.signed = base.signed
            txt = self.gen.cell_text(f, cell)
            if txt is not None:
                return Node(txt)
            lit = (cell.text or '').strip()
            if base.signed and re.match(r'^0[xX][0-9a-fA-F]+$', lit) and int(lit, 16) == int.from_bytes(raw, 'little'):
                # e.g. 0xFBFBFBFB in an int field: keep the spelling of the data
                return Node('(%s)%s' % (spell(unconst(t)) if t.name else base.name, lit))
        if base.kind == 'enum' and v in getattr(base, 'enumerators', {}) and False:
            return Node(base.enumerators[v])
        if base.encoding == 'bool':
            return Node(str(v))
        if base.signed or abs(v) < 10:
            return Node(str(v))
        return Node('0x%0*X' % (2 * size, v))

    def enum_value(self, t, base, v):
        names = getattr(base, 'enumerators', {})
        if v in names:
            return Node(names[v])
        name = t.name or base.name
        if name:
            return Node('(%s)%d' % (name, v))
        raise TypedFail('the value %d has no name in an anonymous enum' % v)

    def pointer(self, t, off):
        cell = self.cells.get(off)
        self.mark(off, 4)
        tgt = strip_quals(t.target) if t.target is not None else None
        if cell is None or cell.reloc is None:
            v = int.from_bytes(self.raw[off:off + 4], 'little')
            if v == 0:
                return Node('NULL')
            return Node('(%s)0x%08X' % (spell(unconst(t)), v))
        tg = cell.reloc
        if tg.kind == 'overlay':
            raise TypedFail('an overlay id sits in a pointer field')
        if tgt is not None and tgt.kind == 'func':
            if tg.kind == 'local':
                raise TypedFail('a function pointer field points at data')
            expr = self.gen.addr_expr(tg, 'fptr', typed=True)
            if self.casts or tg.name not in self.gen.header_idents or tg.name in self.gen.declare:
                return Node('(%s)%s' % (spell(unconst(t)), expr))
            return Node(expr)
        if tg.kind == 'local':
            # remember the pointee type for the target (it may be typed through this pointer)
            self.gen.pointee_hints.setdefault(tg.name, []).append((t.target, tg.addend))
            if self.casts:
                return Node('(%s)%s' % (spell(unconst(t)), self.gen.addr_expr(tg, 'dptr', typed=True)))
            self.gen.cast_specs.append(t)
            return Node('@@%s@%d@%d@@' % (tg.name, tg.addend, len(self.gen.cast_specs) - 1))
        expr = self.gen.addr_expr(tg, 'dptr', typed=True)
        if self.casts or tg.kind == 'extern' and (tg.name not in self.gen.header_idents or tg.name in self.gen.declare) \
                or tg.kind == 'local':
            return Node('(%s)%s' % (spell(t), expr) if not expr.startswith('@@') else '(%s)%s' % (spell(t), expr))
        return Node(expr)


# --------------------------------------------------------------------------------------
# Verification: compile the C with arm-none-eabi-gcc and compare with the assembled asm
# --------------------------------------------------------------------------------------

def gcc_compile(c_text, out_obj, game, workdir, name):
    """Compile generated C for comparison. GCC does not know MWCC's section pragmas, so
    objects inside '#pragma section VERSION' get a section attribute instead."""
    def to_attr(m):
        block = m.group(1)
        block = re.sub(r'^([A-Za-z_][^=\n/]*?)( = )', r'\1 __attribute__((section(".version")))\2', block, flags=re.M)
        return block
    c_text = re.sub(r'#pragma section VERSION begin(.*?)#pragma section VERSION end', to_attr, c_text, flags=re.S)
    src = Path(workdir) / (name + '.verify.c')
    src.write_text(c_text)
    res = subprocess.run([tool('gcc')] + GCC_FLAGS + ['-Os', '-Werror=incompatible-pointer-types',
                          '-Werror=int-conversion', '-Werror=overflow', '-Wno-attributes']
                         + GAME_DEFINES[game] + ['-o', str(out_obj), str(src)],
                         capture_output=True, text=True, cwd=ROOT)
    if res.returncode != 0:
        raise S2CError('gcc failed on %s:\n%s' % (name, res.stderr))
    warnings = [l for l in res.stderr.splitlines() if str(src) in l and 'warning' in l]
    return Elf(out_obj), warnings


def canon_relocs(elf, sname):
    """{offset: (kind, name, addend)} with local targets made section-relative."""
    out = {}
    data = elf.section_bytes(sname)
    for off, (rtype, name) in elf.relocs.get(sname, {}).items():
        if off in elf.addends.get(sname, {}):
            addend = elf.addends[sname][off] & 0xFFFFFFFF
        else:
            addend = int.from_bytes(data[off:off + 4], 'little')
        if name in elf.by_name:
            out[off] = (rtype, 'sect:' + name, addend)
            continue
        sym = next((y for y in elf.symbols if y['name'] == name), None)
        if sym is not None and sym['shndx'] not in (0, 0xFFF1, 0xFFF2):
            sec = elf.sections[sym['shndx']]['name']
            out[off] = (rtype, 'sect:' + sec, (sym['value'] + addend) & 0xFFFFFFFF)
        else:
            out[off] = (rtype, name, addend)
    return out


class LinkedObjects:
    """Several objects viewed as the linker places them one after another."""

    def __init__(self, elfs):
        self.elfs = list(elfs)
        self.sections = [s for e in self.elfs for s in e.sections]
        self._merged = {}

    def merged(self, secname):
        if secname not in self._merged:
            self._merged[secname] = link_view(self.elfs, secname)
        return self._merged[secname]


def compare(gen, gnu, celf):
    problems, culprits = compare_detail(gen, gnu, celf)
    return problems


def compare_detail(gen, ref, celf, exact=False):
    """Problems as text, plus the objects most likely responsible (earliest first).

    Both objects are viewed per section name as the linker lays them out. With exact, the
    section sizes and alignments must match too (MWCC against MWAS)."""
    problems = []
    culprits = []
    for sname, objs in gen.objs.items():
        live = [o for o in objs if o.size]
        if not live:
            continue
        ma, mc = ref.merged(sname), celf.merged(sname)
        if not mc['present']:
            problems.append('%s: missing' % sname)
            continue
        syms = mc['syms']
        prev = None
        for o in live:
            y = syms.get(o.name)
            if y is not None and y['value'] != o.start:
                culprits.append(prev.name if prev is not None and gen.reps[prev.name].kind == 'typed' else o.name)
                break
            prev = o
        a, b = ma['data'], mc['data']
        if exact:
            # whatever is linked next starts at the next LINK_ALIGNALL boundary anyway
            def rounded(n):
                return (n + LINK_ALIGNALL - 1) & -LINK_ALIGNALL
            if rounded(len(a)) != rounded(len(b)) or (sname != '.bss' and any(a[len(b):] + b[len(a):])):
                problems.append('%s: size %#x, expected %#x' % (sname, len(b), len(a)))
            # the first section must be placed like the original, and none may need more
            if ma['align'] != mc['first_align'] or mc['align'] > ma['align']:
                problems.append('%s: alignment %d (first section %d), expected %d' % (
                    sname, mc['align'], mc['first_align'], ma['align']))
        elif len(b) > len(a) or len(a) - len(b) >= 4 or (sname != '.bss' and any(a[len(b):])):
            problems.append('%s: size %#x, expected %#x' % (sname, len(b), len(a)))
        if sname != '.bss':
            ra, rb = ma['relocs'], mc['relocs']
            xa, xb = bytearray(a), bytearray(b)
            for off in ra:
                xa[off:off + 4] = b'\0\0\0\0'
            for off in rb:
                xb[off:off + 4] = b'\0\0\0\0'
            n = min(len(xa), len(xb))
            if xa[:n] != xb[:n]:
                first = next(i for i in range(n) if xa[i] != xb[i])
                obj = next((o for o in live if o.start <= first < o.end), None)
                if obj is not None:
                    culprits.append(obj.name)
                problems.append('%s+%#x (%s): bytes differ: asm %s c %s' % (
                    sname, first, obj.name if obj else '?', bytes(xa[first:first + 8]).hex(),
                    bytes(xb[first:first + 8]).hex()))
            if ra != rb:
                for off in sorted(set(ra) | set(rb)):
                    if ra.get(off) != rb.get(off):
                        obj = next((o for o in live if o.start <= off < o.end), None)
                        if obj is not None:
                            culprits.append(obj.name)
                        problems.append('%s+%#x (%s): relocation asm %s c %s' % (
                            sname, off, obj.name if obj else '?', ra.get(off), rb.get(off)))
                        break
        for o in live:
            y = syms.get(o.name)
            if y is None:
                problems.append('%s: %s missing' % (sname, o.name))
            elif y['value'] != o.start:
                problems.append('%s: %s at %#x, expected %#x' % (sname, o.name, y['value'], o.start))
            elif (y['bind'] == 1) != bool(o.public_names):
                problems.append('%s: %s binding %s' % (sname, o.name, 'global' if y['bind'] == 1 else 'local'))
    return problems, culprits


# --------------------------------------------------------------------------------------
# MWCC's data layout (measured against the compiler; tools/s2c.py --mwcc checks every file)
#
#   * all objects go in one list: the .bss ones in definition order, then the initialised ones
#     (.rodata, .data, .version) in reverse definition order; the list is sorted by size with
#     MSL's qsort (a heapsort, so equal sizes come out in a definite but shuffled order)
#   * walking that order, every one-dimensional array of char-sized elements gets a section of
#     its own; all other objects of a section kind share one section, created where the first
#     of them comes
#   * the linker then places the sections in file order, each at its alignment
# --------------------------------------------------------------------------------------

def msl_qsort(items, key):
    """MSL_C qsort (lib/MSL_C/src/msl_qsort.c): an in-place heapsort."""
    a = list(items)
    num = len(a)
    if num < 2:
        return a
    r = num
    l = (num >> 1) + 1
    while True:
        if l > 1:
            l -= 1
        else:
            a[0], a[r - 1] = a[r - 1], a[0]
            r -= 1
            if r == 1:
                return a
        j = l
        while j * 2 <= r:
            i = j
            j *= 2
            if j < r and key(a[j - 1]) < key(a[j]):
                j += 1
            if key(a[i - 1]) >= key(a[j - 1]):
                break
            a[i - 1], a[j - 1] = a[j - 1], a[i - 1]


def mw_layout(defs, size, own, section):
    """Predicted layout {section: [objects]} for objects defined in the order defs."""
    init = [o for o in defs if section(o) != '.bss']
    bss = [o for o in defs if section(o) == '.bss']
    blocks = defaultdict(list)
    shared = {}
    for o in msl_qsort(bss + list(reversed(init)), size):
        sec = section(o)
        if own(o):
            blocks[sec].append([o])
        else:
            if sec not in shared:
                shared[sec] = []
                blocks[sec].append(shared[sec])
            shared[sec].append(o)
    return {sec: [o for b in bl for o in b] for sec, bl in blocks.items()}


def mw_definition_order(init_walk, bss_walk, size):
    """Definition orders (initialised, .bss) that make MWCC's sort produce the wanted orders
    (each sorted by size; only the order within a section matters). Take any arrangement of the
    keys that keeps the .bss sizes in front, see where the heapsort sends each position, and put
    the next wanted object of that size and kind there."""
    nb = len(bss_walk)
    keys = sorted(size(o) for o in bss_walk) + sorted(size(o) for o in init_walk)
    perm = msl_qsort(range(len(keys)), lambda i: keys[i])     # output k <- input perm[k]
    queues = (defaultdict(list), defaultdict(list))
    for q, walk in zip(queues, (bss_walk, init_walk)):
        for o in walk:
            q[size(o)].append(o)
    slots = [None] * len(keys)
    for src in perm:
        slots[src] = queues[0 if src < nb else 1][keys[src]].pop(0)
    return list(reversed(slots[nb:])), slots[:nb]


class InfeasibleLayout(S2CError):
    def __init__(self, obj):
        S2CError.__init__(self, '%s cannot be placed where the asm has it (offset %#x)' % (obj.name, obj.start))
        self.obj = obj


def mw_plan_section(seq, size, kinds, align_of, can_start):
    """Split one section's objects (in layout order) into the fewest runs MWCC can lay out from
    single files. Returns [(objs, own flags)].

    A run is feasible when it reads: own-section objects sorted by size, then every shared object
    (sorted by size, starting no smaller than what came before), then own-section objects no
    smaller than the first shared one. can_start(o, a): a section aligned to a (and to
    LINK_ALIGNALL) that starts right after the object before o lands where o is; it must hold for
    every own-section object and for the first shared one with the alignment of all its members."""
    # state (phase, last size, first shared size, first shared index, shared alignment)
    #   -> (cost, choices); cost = (char arrays moved into the shared section, runs)
    best = {(None,): ((0, 0), ())}
    for i, o in enumerate(seq):
        sz = size(o)
        a = align_of(o)
        nxt = {}
        for st, (runs, hist) in best.items():
            options = []
            if st != (None,):
                phase, last, s0, s0i, sa = st
                for k in kinds(o):
                    if k == 'own':
                        if not can_start(o, a):
                            continue
                        if phase == 'C1' and sz >= last:
                            options.append((('C1', sz, None, None, None), runs, k, False))
                        elif phase in ('S', 'C2') and sz >= s0 and (phase == 'S' or sz >= last):
                            options.append((('C2', sz, s0, s0i, sa), runs, k, False))
                    elif phase == 'C1' and sz >= last and can_start(o, a):
                        options.append((('S', sz, sz, i, a), runs, k, False))
                    elif phase == 'S' and sz >= last and can_start(seq[s0i], max(sa, a)):
                        options.append((('S', sz, s0, s0i, max(sa, a)), runs, k, False))
            for k in kinds(o):
                if can_start(o, a):
                    ns = ('C1', sz, None, None, None) if k == 'own' else ('S', sz, sz, i, a)
                    options.append((ns, (runs[0], runs[1] + 1), k, True))
            moved = 'own' in kinds(o)
            for ns, r, k, newrun in options:
                if k == 'shared' and moved:
                    r = (r[0] + 1, r[1])
                if ns not in nxt or r < nxt[ns][0]:
                    nxt[ns] = (r, (hist, (newrun, k)))
        if not nxt:
            raise InfeasibleLayout(o)
        best = nxt
    cost, hist = min(best.values(), key=lambda v: v[0])
    choices = []
    while hist:
        hist, c = hist
        choices.append(c)
    choices.reverse()
    out = []
    for o, (newrun, k) in zip(seq, choices):
        if newrun:
            out.append(([], []))
        out[-1][0].append(o)
        out[-1][1].append(k == 'own')
    return out


def mw_own_section(gen, o):
    """Does MWCC give this object a section of its own (a one-dimensional array of char-sized
    elements)?"""
    if o.section == '.version':
        return True     # a section of the program's own (#pragma section): one per object
    rep = gen.reps[o.name]
    if getattr(rep, 'row', False):
        return False
    if rep.kind == 'typed':
        t = strip_quals(rep.typed['type'])
        if t.kind != 'array':
            return False
        t = strip_quals(t.target)
        return t.kind == 'base' and t.size == 1
    if rep.kind in ('string', 'bss') or getattr(o, 'is_pad', False):
        return True
    return rep.kind == 'array' and rep.elem.kind in ('num', 'char') and rep.elem.w == 1


def aligned_up(n, a):
    return (n + a - 1) & -a


def section_starts(gen, ref):
    """Per object: (end of the object before it, the smallest alignment that recreates the gap
    before it). The first object of a section gets the asm section's alignment."""
    out = {}
    for sname, objs in gen.objs.items():
        prev_end = None
        for o in objs:
            if not o.size:
                continue
            if prev_end is None:
                out[o.name] = (0, ref.merged(sname)['align'] if ref is not None else LINK_ALIGNALL)
            else:
                a = 1
                while aligned_up(prev_end, a) != o.start:
                    a *= 2
                    if a > 64:
                        raise S2CError('%s: no alignment explains the gap before it' % o.name)
                out[o.name] = (prev_end, a)
            prev_end = o.start + gen.c_size(o)
    return out


def can_start_section(starts, o, a):
    prev_end, _ = starts[o.name]
    return aligned_up(prev_end, max(a, LINK_ALIGNALL)) == o.start


class Rows(S2CError):
    def __init__(self, names):
        S2CError.__init__(self, 'rows wanted: %s' % ', '.join(names))
        self.names = names


def plan_tus(gen, ref):
    """Split a file's objects into C files that MWCC lays out like the asm (ref: the original
    assembled by MWAS). Returns [(initialised objects, .bss objects)] in definition order.

    Each section's objects are cut into the fewest runs one file can produce (mw_plan_section);
    file k gets run k of every section. Within a run the wanted sort order is: the own-section
    objects before the shared section, the first shared object, then the rest merged by size.

    A char array may also be written as the only row of a 2-D array, which shares the section of
    its neighbours; the plan does that only where the layout needs it. Raises Rows with the names
    when the plan wants rows the generator does not have yet."""
    import heapq
    size = gen.c_size
    starts = section_starts(gen, ref)
    runs = OrderedDict()
    for sname, objs in gen.objs.items():
        live = [o for o in objs if o.size]
        if not live:
            continue
        for o in live:
            o.plan_align = starts[o.name][1]
        own = {o.name: mw_own_section(gen, o) for o in live}

        def kinds(o):
            if o.section == '.version':
                return ['own']
            return ['own', 'shared'] if own[o.name] else ['shared']
        runs[sname] = mw_plan_section(live, size, kinds,
                                      lambda o: max(gen.reps[o.name].align, o.plan_align),
                                      lambda o, a: can_start_section(starts, o, a))
    want = []
    for rl in runs.values():
        for objs, flags in rl:
            for o, f in zip(objs, flags):
                if not f and mw_own_section(gen, o):
                    want.append(o.name)
    if want:
        raise Rows(want)
    # the linker keeps every object of a file compiled with force_active, and drops the ones nothing
    # uses otherwise: sections it dropped from the asm go to files of their own without the pragma
    dropped = gen.stripped_sections()
    tus = []
    for family, keep in (([s for s in runs if s not in dropped], True), ([s for s in runs if s in dropped], False)):
        if family:
            tus += plan_files(gen, OrderedDict((s, runs[s]) for s in family), keep)
    return tus


def plan_files(gen, runs, keep):
    """Files for the runs of some sections: file k gets run k of each. Returns
    [(initialised objects, .bss objects, keep)] in definition order."""
    import heapq
    size = gen.c_size
    tus = []
    for k in range(max(len(r) for r in runs.values())):
        init_walks, bss_walk = [], []
        layout = {}
        for sname, rl in runs.items():
            if k >= len(rl):
                continue
            objs, flags = rl[k]
            layout[sname] = [o.name for o in objs]
            shared = [o for o, f in zip(objs, flags) if not f]
            if shared:
                first = objs.index(shared[0])
                c1 = objs[:first]
                c2 = [o for o, f in zip(objs, flags) if f and objs.index(o) > first]
                walk = c1 + [shared[0]] + list(heapq.merge(shared[1:], c2, key=size))
            else:
                walk = list(objs)
            if sname == '.bss':
                bss_walk = walk
            else:
                init_walks.append(walk)
        init_walk = list(heapq.merge(*init_walks, key=size))
        ini, bss = mw_definition_order(init_walk, bss_walk, size)
        # check the plan against the model before anyone compiles it
        sec = {o.name: s for s, objs in gen.objs.items() for o in objs}
        got = mw_layout([o.name for o in ini + bss], lambda n: size(gen.by_name[n]),
                        lambda n: mw_own_section(gen, gen.by_name[n]), lambda n: sec[n])
        if got != layout:
            raise S2CError('layout plan for part %d does not hold: %s != %s' % (k + 1, got, layout))
        tus.append(([o.name for o in ini], [o.name for o in bss], keep))
    return tus


# --------------------------------------------------------------------------------------
# MWCC check: the real compiler and assembler (metroskrew's native builds)
# --------------------------------------------------------------------------------------

def make_var(name, game):
    """A variable as the Makefile computes it."""
    helper = Path(tempfile.mkdtemp(prefix='s2c-mk-')) / 'print.mk'
    helper.write_text('print-%:\n\t@echo "$($*)"\n')
    out = run(['make', '-s', '--no-print-directory', '-f', 'Makefile', '-f', str(helper), 'print-' + name,
               'GAME_VERSION=' + game], cwd=ROOT)
    shutil.rmtree(helper.parent, ignore_errors=True)
    return out.split()


def mw_tool(bindir, name):
    return [str(Path(bindir) / name), '-wrap:sdk', '2.0/sp2p2']


class MwccError(S2CError):
    pass


_MW_FLAGS = {}


def mw_flags(game):
    if game not in _MW_FLAGS:
        cc = make_var('MWCFLAGS', game)
        i = cc.index('-ipa')
        del cc[i:i + 2]          # as the Makefile does for src/data/
        _MW_FLAGS[game] = (cc, make_var('MWASFLAGS', game) + ['-DPM_ASM'])
    return _MW_FLAGS[game]


def mwcc_compile(text, bindir, workdir, name, game):
    cc, _ = mw_flags(game)
    src = Path(workdir) / (name + '.c')
    obj = Path(workdir) / (name + '.mw.%s.o' % game)
    src.write_text(text)
    res = subprocess.run(mw_tool(bindir, 'mwccarm') + cc + ['-c', '-o', str(obj), str(src)],
                         capture_output=True, text=True, cwd=ROOT)
    if res.returncode != 0:
        raise MwccError(res.stdout + res.stderr)
    return Elf(obj)


_MW_ASM = {}


def mwcc_sizes(text, bindir, workdir, name, game):
    """The size MWCC gives each object a file defines."""
    e = mwcc_compile(text, bindir, workdir, name, game)
    return {y['name']: y['size'] for y in e.symbols
            if y['name'] and y['type'] == 1 and y['shndx'] not in (0, 0xFFF1, 0xFFF2)}


def mwasm_original(asm, bindir, workdir, game):
    key = (str(asm.path), game)
    if key not in _MW_ASM:
        _, asf = mw_flags(game)
        obj = Path(workdir) / (asm.name + '.mwas.%s.o' % game)
        run(mw_tool(bindir, 'mwasmarm') + asf + ['-o', str(obj), str(asm.path)], cwd=ROOT)
        _MW_ASM[key] = Elf(obj)
    return _MW_ASM[key]


def mwcc_check(asm, gen, files, bindir, workdir, game):
    """Compile the files with MWCC (the Makefile's flags for src/data/) and compare them, linked
    in order, with the original assembled by MWAS: bytes, relocations, symbol offsets, section
    sizes and alignment. files: [(name, text)]. MwccError carries the index of the failing file."""
    a = mwasm_original(asm, bindir, workdir, game)
    elfs = []
    for k, (name, text) in enumerate(files):
        try:
            elfs.append(mwcc_compile(text, bindir, workdir, name, game))
        except MwccError as e:
            e.index = k
            raise
    c = LinkedObjects(elfs)
    problems, culprits = compare_detail(gen, a, c, exact=True)
    extra = defaultdict(int)
    for s in c.sections:
        if s['name'] in ('.data', '.rodata', '.bss', '.text', '.version', '.sdata', '.sbss') \
                and s['size'] and s['name'] not in gen.objs:
            extra[s['name']] += s['size']
    for sname, n in extra.items():
        problems.append('%s: MWCC emitted %#x bytes the asm does not have' % (sname, n))
    return problems, culprits


MW_ERR = re.compile(r'^(?P<file>[^\n]*?\.c):(?P<line>\d+): (?P<msg>.*)$', re.M)


def handle_mwcc_errors(out, gen, untyped, force_casts, declare, history):
    """MWCC is stricter than gcc about implicit conversions; react like for gcc errors."""
    progress = False
    seen = set()
    msgs = defaultdict(list)
    for m in MW_ERR.finditer(out):
        msgs[int(m.group('line'))].append(m.group('msg'))
    for line, parts in sorted(msgs.items()):
        msg = ' '.join(parts)
        obj = gen.object_at_line(line)
        nm = re.search(r"undefined identifier '([\w$]+)'", msg)
        if nm and nm.group(1) not in declare:
            declare.add(nm.group(1))
            history.append('mwcc: declare %s' % nm.group(1))
            progress = True
            continue
        if obj is None or obj in seen or gen.reps.get(obj) is None or gen.reps[obj].kind != 'typed':
            continue
        seen.add(obj)
        if 'implicit conversion' in msg and '*' in msg and not force_casts.get(obj):
            force_casts[obj] = True
            history.append('mwcc: casts for %s' % obj)
            progress = True
        elif obj not in untyped:
            untyped.add(obj)
            history.append('mwcc: untyped %s: %s' % (obj, msg))
            progress = True
    return progress


# --------------------------------------------------------------------------------------
# Driver
# --------------------------------------------------------------------------------------

def header_macros(workdir, includes):
    """Macros global.h (and the given extra includes) define."""
    src = Path(workdir) / 'hdr_macros.c'
    src.write_text('#include "global.h"\n' + ''.join('#include %s\n' % i for i in includes))
    out = run([tool('gcc')] + [f for f in GCC_FLAGS if f != '-c'] + ['-E', '-dM'] + GAME_DEFINES['HEARTGOLD']
              + [str(src)], cwd=ROOT)
    return set(re.findall(r'^#define ([A-Za-z_$][\w$]*)', out, re.M))


def header_identifiers(workdir, includes):
    """Identifiers declared by global.h (and the given extra includes)."""
    src = Path(workdir) / 'hdr_probe.c'
    src.write_text('#include "global.h"\n' + ''.join('#include %s\n' % i for i in includes))
    out = run([tool('gcc')] + [f for f in GCC_FLAGS if f != '-c'] + ['-E', '-P'] + GAME_DEFINES['HEARTGOLD']
              + [str(src)], cwd=ROOT)
    return set(re.findall(r'[A-Za-z_$][\w$]*', out))


def basic_decl(decl, name):
    """True if a declaration only uses types global.h provides."""
    toks = set(re.findall(r'[A-Za-z_$][\w$]*', decl)) - {name}
    return toks <= BASIC_TYPES | {'const', 'unsigned', 'signed', 'volatile', 'static'}


def probe_types(asm, names, decls, workdir, game):
    """Compile a probe that takes the type of every declared label; returns name -> CType."""
    includes = []
    lines = []
    for n in names:
        inc, d = decls[n]
        if inc is not None and inc not in includes:
            includes.append(inc)
    base = ['#include "global.h"'] + ['#include %s' % i for i in asm.cpp_includes]

    def attempt(incs, ns):
        body = base + ['#include %s' % i for i in incs]
        for n in ns:
            inc, d = decls[n]
            if inc is None:
                body.append('extern %s;' % d)
            body.append('__typeof__(%s) *s2c_probe_%s;' % (n, n))
        src = Path(workdir) / (asm.name + '.probe.c')
        obj = Path(workdir) / (asm.name + '.probe.o')
        src.write_text('\n'.join(body) + '\n')
        res = subprocess.run([tool('gcc')] + GCC_FLAGS + ['-O0', '-g', '-gdwarf-5', '-fno-eliminate-unused-debug-types']
                             + GAME_DEFINES[game] + ['-o', str(obj), str(src)], capture_output=True, text=True, cwd=ROOT)
        return res, obj

    res, obj = attempt(includes, names)
    if res.returncode != 0:
        # find the headers and names that break the probe
        good_incs = []
        for inc in includes:
            r, _ = attempt(good_incs + [inc], [])
            if r.returncode == 0:
                good_incs.append(inc)
        ok_names = []
        for n in names:
            inc, d = decls[n]
            if inc is not None and inc not in good_incs:
                continue
            r, _ = attempt(good_incs, ok_names + [n])
            if r.returncode == 0:
                ok_names.append(n)
        includes, names = good_incs, ok_names
        res, obj = attempt(includes, names)
        if res.returncode != 0:
            raise S2CError('probe compile failed:\n' + res.stderr[-3000:])
    types = DwarfTypes(obj).vars
    return {n: types[n] for n in names if n in types}


GCC_ERR = re.compile(r'^(?P<file>[^:\n]+):(?P<line>\d+):(?:\d+:)? (?P<kind>error|note|warning): (?P<msg>.*)$', re.M)


def convert(path, symidx, decl_index, workdir, args):
    asm = AsmFile(path)
    gnu = {g: assemble_original(asm, workdir, g) for g in args.games}
    first = gnu[args.games[0]]
    for g in args.games[1:]:
        for s in DATA_SECTIONS:
            if gnu[g].section_bytes(s) != first.section_bytes(s):
                raise S2CError('%s: %s differs between versions; s2c does not emit #if' % (path, s))
    labels = [it.name for sec in asm.sections.values() for it in sec.items if it.kind == 'label']
    decls = {}
    if not args.no_typed:
        for n in labels:
            b = decl_index.best(n)
            if b is None:
                continue
            inc, d = b
            if inc is None and not basic_decl(d, n):
                continue
            decls[n] = b
    ctypes = probe_types(asm, list(decls), decls, workdir, args.games[0]) if decls else {}
    typed_info = {n: (decls[n][0], decls[n][1], t) for n, t in ctypes.items()}
    headers = []
    for n, (inc, d, t) in typed_info.items():
        if inc is not None and inc not in headers:
            headers.append(inc)
    untyped, force_casts, hint_types, declare, renames, rows, merges = set(), {}, {}, set(), set(), set(), set()
    header_decls = {}
    for n in labels:
        hd = [d for f, d in decl_index.decls.get(n, []) if f.endswith('.h')]
        if hd:
            header_decls[n] = hd[0]
    history = []
    for attempt in range(25):
        active = {n: v for n, v in typed_info.items() if v[0] is None or v[0] in headers}
        hdr_idents = header_identifiers(workdir, list(asm.cpp_includes) + headers)
        hdr_macros = header_macros(workdir, list(asm.cpp_includes) + headers)
        gen = Generator(asm, first, symidx, hdr_idents, active, dict(force_casts), set(untyped), dict(hint_types),
                        list(headers), set(declare), header_decls, set(renames), set(rows), set(merges))
        gen.build()
        # a label the headers turn into a macro is reached through another object: it was folded
        # into the object before it (see plan_tus) and the code was pointed there
        folded_now = False
        for objs in gen.objs.values():
            labelled = [o for o in objs if not getattr(o, 'is_pad', False)]
            for k, o in enumerate(labelled):
                if k and o.name in hdr_macros and o.name not in merges:
                    merges.add(o.name)
                    untyped.update((labelled[k - 1].name, o.name))
                    history.append('folded %s into %s (the headers make it a macro)' % (o.name, labelled[k - 1].name))
                    folded_now = True
        if folded_now:
            continue
        text = gen.emit()
        changed = False
        # new pointee hints for untyped locals
        for name, hints in gen.pointee_hints.items():
            if name in hint_types or name in untyped or name in active:
                continue
            o = gen.by_name.get(name)
            if o is None or gen.reps[name].kind == 'typed':
                continue
            cand = [h for h, addend in hints if addend == 0]
            cand = [strip_quals(h) and h for h in cand if hint_usable(h)]
            spellings = set()
            for h in cand:
                try:
                    spellings.add(spell(h))
                except TypedFail:
                    pass
            if len(spellings) != 1:
                continue
            h = cand[0]
            elem_size = h.size
            if elem_size and o.size >= elem_size:
                n = o.size // elem_size
                t = CType('array', target=h, count=n, size=n * elem_size, align=type_align(h)) if n > 1 or \
                    o.size > elem_size else h
                hint_types[name] = t
                changed = True
        if changed:
            continue
        if not args.verify:
            return asm, gen, [(asm.name, text)], [], [], history
        problems = []
        warnings = []
        culprits = []
        compile_errors = None
        for g in args.games:
            try:
                celf, warns = gcc_compile(text, Path(workdir) / (asm.name + '.%s.o' % g), g, workdir, asm.name)
            except S2CError as e:
                compile_errors = str(e)
                break
            warnings += warns
            pr, cu = compare_detail(gen, gnu[g], celf)
            problems += [(g, p) for p in pr]
            culprits += cu
        if compile_errors:
            nheaders = len(headers)
            if not handle_compile_errors(compile_errors, gen, untyped, force_casts, declare, headers, history,
                                         decl_index, text, renames):
                errs = [l for l in compile_errors.splitlines() if ' error: ' in l]
                raise S2CError('\n'.join(errs[:10]) or compile_errors[-3000:])
            if len(headers) != nheaders:
                hint_types.clear()
            continue
        bad = set()
        for name in culprits:
            if name in gen.reps and gen.reps[name].kind == 'typed' and name not in untyped:
                bad.add(name)
        if bad:
            for n in bad:
                untyped.add(n)
                hint_types.pop(n, None)
                history.append('untyped %s after a mismatch' % n)
            continue
        if args.mwcc and not problems:
            # the real compiler: files and definition orders that reproduce the layout, then an
            # exact check against MWAS
            ref = mwasm_original(asm, args.mwcc, workdir, args.games[0])
            try:
                sizes = mwcc_sizes(text, args.mwcc, workdir, asm.name, args.games[0])
            except MwccError as e:
                if not handle_mwcc_errors(str(e), gen, untyped, force_casts, declare, history):
                    raise S2CError('mwcc failed on %s:\n%s' % (asm.name, str(e)[-3000:]))
                continue
            bad = gen.adopt_mw_sizes(sizes)
            if bad:
                for n in bad:
                    untyped.add(n)
                    hint_types.pop(n, None)
                    history.append('mwcc: untyped %s (MWCC sizes it %#x)' % (n, sizes[n]))
                continue
            try:
                tus = plan_tus(gen, ref)
            except Rows as e:
                for n in e.names:
                    rows.add(n)
                    untyped.add(n)
                    hint_types.pop(n, None)
                    history.append('row form for %s (offset %#x)' % (n, gen.by_name[n].start))
                continue
            except InfeasibleLayout as e:
                o = e.obj
                objs = gen.objs[o.section]
                k = objs.index(o) - 1
                while k >= 0 and (getattr(objs[k], 'is_pad', False) or not objs[k].size):
                    k -= 1
                if k < 0:
                    raise
                prev = objs[k]
                if getattr(o, 'is_pad', False):
                    # the padding after a typed object: let the label cover it again
                    untyped.add(prev.name)
                    hint_types.pop(prev.name, None)
                    history.append('untyped %s (its padding cannot be placed)' % prev.name)
                else:
                    merges.add(o.name)
                    untyped.add(prev.name)
                    hint_types.pop(prev.name, None)
                    untyped.add(o.name)
                    history.append('folded %s into %s' % (o.name, prev.name))
                continue
            planned = gen.emit_plan(tus)
            stems = [asm.name] if len(planned) == 1 else ['%s_%d' % (asm.name, k + 1) for k in range(len(planned))]
            files = [(stem, t) for stem, (t, _) in zip(stems, planned)]
            mw_problems, mw_culprits = [], []
            try:
                for g in args.games:
                    pr, cu = mwcc_check(asm, gen, files, args.mwcc, workdir, g)
                    mw_problems += ['%s (mwcc): %s' % (g, p) for p in pr]
                    mw_culprits += cu
            except MwccError as e:
                gen.line_map = planned[e.index][1]
                if not handle_mwcc_errors(str(e), gen, untyped, force_casts, declare, history):
                    raise S2CError('mwcc failed on %s:\n%s' % (stems[e.index], str(e)[-3000:]))
                continue
            bad = set(n for n in mw_culprits if n in gen.reps and gen.reps[n].kind == 'typed' and n not in untyped)
            if bad:
                for n in bad:
                    untyped.add(n)
                    hint_types.pop(n, None)
                    history.append('mwcc: untyped %s after a mismatch' % n)
                continue
            # the files must still build with gcc (for the port)
            for g in args.games:
                for stem, t in files:
                    try:
                        gcc_compile(t, Path(workdir) / (stem + '.final.%s.o' % g), g, workdir, stem)
                    except S2CError as e:
                        mw_problems.append('%s (gcc, %s): %s' % (g, stem, str(e).splitlines()[-1]))
            return asm, gen, files, ['%s: %s' % gp for gp in problems] + mw_problems, warnings, history
        return asm, gen, [(asm.name, text)], ['%s: %s' % gp for gp in problems], warnings, history
    raise S2CError('no stable conversion after %d attempts: %s' % (attempt + 1, history[-5:]))


def hint_usable(t):
    b = strip_quals(t)
    if b.kind in ('void', 'func'):
        return False
    if b.kind == 'base' and b.size == 1:
        return False
    if b.kind in ('struct', 'union') and (getattr(b, 'incomplete', False) or not b.size):
        return False
    return True


def handle_compile_errors(stderr, gen, untyped, force_casts, declare, headers, history, decl_index, text, renames):
    """Adjust the conversion state from gcc's errors. Returns True if anything changed."""
    progress = False
    seen = set()
    src_lines = text.split('\n')
    chain = []          # (file, line) of the current "In file included from" chain
    pending = None      # last error waiting for its "previous declaration" note
    for raw in stderr.splitlines():
        m = re.match(r'^(?:In file included from|\s+from) (\S+):(\d+)[,:]$', raw)
        if m:
            if raw.startswith('In file'):
                chain = []
            chain.append((m.group(1), int(m.group(2))))
            continue
        m = GCC_ERR.match(raw)
        if not m:
            continue
        kind, msg, fname, line = m.group('kind'), m.group('msg'), m.group('file'), int(m.group('line'))
        cur_chain, chain = chain, []
        if kind == 'note' and pending is not None and 'previous' in msg:
            # find which of our #includes brought the conflicting declaration in
            top = [ln for f, ln in cur_chain if f.endswith('.verify.c')]
            inc = None
            if top:
                mm = re.match(r'#include\s+(.*)$', src_lines[top[-1] - 1].strip())
                inc = mm.group(1) if mm else None
            elif fname.endswith('.verify.c'):
                inc = None
            if inc in headers:
                headers.remove(inc)
                history.append('dropped %s: %s' % (inc, pending))
                progress = True
            pending = None
            continue
        if kind != 'error' or not fname.endswith('.verify.c'):
            continue
        obj = gen.object_at_line(line)
        nm = re.search(r"'([\w$]+)'", msg)
        if 'undeclared' in msg and nm:
            if nm.group(1) not in declare:
                declare.add(nm.group(1))
                history.append('declare %s' % nm.group(1))
                progress = True
            continue
        if ('conflicting' in msg or 'follows non-static' in msg or 'redefinition' in msg
                or 'redeclared as different kind' in msg) and nm:
            pending = 'conflicts on %s' % nm.group(1)
            if nm.group(1) in gen.by_name and nm.group(1) not in renames and \
                    (gen.reps.get(nm.group(1)) is None or gen.reps[nm.group(1)].kind != 'typed'):
                renames.add(nm.group(1))
                history.append('rename the header declaration of %s' % nm.group(1))
                progress = True
                pending = None
            if obj is not None and gen.reps.get(obj) is not None and gen.reps[obj].kind == 'typed' \
                    and obj not in untyped and nm.group(1) == obj and gen.reps[obj].typed['from_hint']:
                untyped.add(obj)
                progress = True
            continue
        if obj is not None and gen.reps.get(obj) is not None and gen.reps[obj].kind == 'typed':
            if obj in seen:
                continue
            seen.add(obj)
            if 'incompatible pointer type' in msg and not force_casts.get(obj):
                force_casts[obj] = True
                history.append('casts for %s' % obj)
                progress = True
            elif obj not in untyped:
                untyped.add(obj)
                history.append('untyped %s: %s' % (obj, msg))
                progress = True
    return progress


def write_report(path, items, outputs, argv):
    """What the C declarations get wrong about the data, for whoever fixes the headers."""
    const_rows, overlap_rows, other_rows, zero_rows, unread_rows = [], [], [], [], []
    nobj = ntyped = 0
    for asm, gen, decl_index in items:
        nobj += len(gen.reps)
        ntyped += sum(1 for r in gen.reps.values() if r.kind == 'typed')
        for n in gen.renamed:
            o = gen.by_name[n]
            rep = gen.reps.get(n)
            if rep is None or rep.kind != 'typed':
                continue
            where = ', '.join(sorted(set(f for f, d in decl_index.decls.get(n, []))))
            how = 'add const' if rep.typed['const_fix'] == 'add' else 'drop const'
            const_rows.append('| `%s` | %s | %s | %s |' % (n, o.section, how, where))
        for n, why in gen.mismatch.items():
            if n not in gen.reps or gen.reps[n].kind == 'typed':
                continue
            d = gen.decl_names.get(n, '')
            row = '| `%s` | `%s` | %s |' % (n, d, why)
            if 'could not read' in why:
                unread_rows.append('| `%s` | `%s` |' % (n, d))
            else:
                (overlap_rows if 'overlap' in why else other_rows).append(row)
        if '.data' in gen.objs:
            raw = gen.raw('.data')
            rels = gen.elf.relocs.get('.data', {})
            for o in gen.objs['.data']:
                if o.size and not any(raw[o.start:o.end]) and not any(o.start <= r < o.end for r in rels):
                    zero_rows.append('| `%s` | %s |' % (o.name, asm.name))
    nfiles = sum(len(v) for v in outputs.values())
    split = sorted(((len(v), Path(k).name) for k, v in outputs.items() if len(v) > 1), reverse=True)
    pads, mwsized, folded = [], [], []
    for asm, gen, decl_index in items:
        for label, owner, off in gen.interior:
            folded.append('| `%s` | `%s` | %#x |' % (label, owner, off))
        for objs in gen.objs.values():
            for o in objs:
                if getattr(o, 'is_pad', False):
                    pads.append('| `%s` | %s | %#x | %s |' % (o.name, o.section, o.size, '; '.join(o.comments)))
    out = ['# Data tables converted from asm', '',
           'Generated by `tools/s2c.py --report`. %d objects from %d asm files, in %d C files under `src/data/`; '
           '%d have the type the C code declares (or the type a typed pointer to them has), the rest are written '
           'from the asm directives: byte, halfword and word arrays, pointer tables, and anonymous structs where '
           'pointers and numbers mix.' % (nobj, len(items), nfiles, ntyped), '',
           'To redo the conversion, check out the commit before it and run', '',
           '    python3 tools/s2c.py ' + ' '.join(argv), '',
           'Checks, for HeartGold and SoulSilver:', '',
           '- `--verify`: each file compiled with arm-none-eabi-gcc matches the original assembled by '
           'arm-none-eabi-as (bytes, relocations, symbol offsets and binding). This is the check of the '
           'contents.',
           '- `--mwcc BINDIR` (metroskrew\'s native mwccarm/mwasmarm): the C files compiled with MWCC, '
           'with the Makefile\'s flags, and laid out as the linker places them, match the original assembled '
           'by MWAS exactly: bytes, relocations, symbol offsets, section sizes and alignment. The final check is '
           'the ROM build itself.', '',
           '## Why some asm files became several C files', '',
           'MWCC does not keep definition order. It puts a file\'s objects in one list (the .bss ones in '
           'definition order, then the initialised ones in reverse definition order), sorts that by size with '
           'MSL\'s heapsort, and gives each one-dimensional char array a section of its own while everything '
           'else of a kind shares one section. The linker then starts every section 4-aligned (`ALIGNALL(4)` in '
           'the SDK\'s LCF templates). One C file can therefore only produce runs of objects sorted by size, '
           'and a char array off a 4-byte boundary cannot have a section of its own. Most asm data files cover '
           'several original files, so s2c cuts each section into the fewest runs one file can produce, puts '
           'run k of every section into file k, and picks the definition order that makes the heapsort put '
           'every object where the asm has it (`plan_tus`, `mw_definition_order`). Char arrays that have to '
           'share a section with their neighbours are written as the only row of a 2-D array '
           '(`u8 x[1][N]`). Keep the order when editing these files, or rerun s2c.', '',
           '| C files | asm file |', '|---|---|'] + ['| %d | `%s` |' % (n, name) for n, name in split] + [
           '', '## Labels folded into the object before them', '',
           'No arrangement of separate objects puts these where the asm has them (each would have to start a '
           '4-aligned section, or follow a larger object in a sorted one): in the original they were parts of '
           'one object. s2c writes the span as one object under the first label; the declarations of the other '
           'labels became macros that reach them through it.', '',
           '| Label | Now inside | At offset |', '|---|---|---|'] + sorted(folded) + [
           '', '## Zero pad objects', '',
           'Bytes the asm has that no C object covers: alignment the asm spelled out after a typed object, '
           'sections MWAS rounded up to 4 bytes, and objects MWCC lays out smaller than gcc (64-bit members '
           'are only 4-aligned there).', '',
           '| Name | Section | Size | Why |', '|---|---|---|---|'] + sorted(pads) + [
           '', '## Declarations with the wrong constness', '',
           'The data file renames the header declaration away (`#define X X_header_decl`) so the definition can '
           'match the section the data lives in. Fixing the header removes the need for that.', '',
           '| Name | Section | Header fix | Declared in |', '|---|---|---|---|'] + sorted(const_rows) + [
           '', '## Declarations that overlap later labels', '',
           'The C type is larger than the label: the code treats several asm labels as one object. The DS build '
           'is exact (the labels stay contiguous), but a 64-bit build will size these objects differently, so '
           'they need one real struct before the port can rely on them.', '',
           '| Name | Declared as | Problem |', '|---|---|---|'] + sorted(overlap_rows) + [
           '', '## Other declarations that do not describe the data', '',
           '| Name | Declared as | Problem |', '|---|---|---|'] + sorted(other_rows) + [
           '', '## Declarations s2c could not read', '',
           'Their headers include files the build generates (NARC indexes), so these stay untyped until s2c '
           'runs on a tree where those exist.', '',
           '| Name | Declared as |', '|---|---|'] + sorted(unread_rows) + [
           '', '## Initialised data that is all zero', '',
           'MWCC would put these in .bss: they are wrapped in `#pragma explicit_zero_data`.', '',
           '| Name | File |', '|---|---|'] + sorted(zero_rows) + ['']
    Path(path).write_text('\n'.join(out))
    print('report: %s' % path)


def remove_outputs(out_dir, name):
    """Delete what an earlier run wrote for asm/<name>.s (it may have been split differently)."""
    for f in Path(out_dir).glob(name + '*.c'):
        if re.fullmatch(re.escape(name) + r'(_\d+)?\.c', f.name) and \
                f.read_text(errors='replace').startswith('// Converted from asm/%s.s ' % name):
            f.unlink()


def install(outputs, out_dir):
    """Swap the converted .s files for their C in the build. outputs: .s path -> file stems."""
    paths = list(outputs)
    lsf = ROOT / 'main.lsf'
    text = lsf.read_text()
    for p, stems in outputs.items():
        obj = Path(p).resolve().relative_to(ROOT).with_suffix('.o').as_posix()
        m = re.search(r'^([ \t]*)Object %s$' % re.escape(obj), text, re.M)
        if m is None:
            raise S2CError('main.lsf has no Object %s' % obj)
        new = '\n'.join('%sObject %s/%s.o' % (m.group(1), out_dir.rstrip('/'), st) for st in stems)
        text = text[:m.start()] + new + text[m.end():]
    lsf.write_text(text)
    used_by_converted = set()
    for p in paths:
        used_by_converted.update(AsmFile(p).asm_includes)
    for p in paths:
        Path(p).unlink()
    still = set()
    for f in list(ROOT.glob('**/*.s')) + list(ROOT.glob('**/*.inc')):
        if 'build' in f.parts:
            continue
        try:
            txt = f.read_text(errors='replace')
        except OSError:
            continue
        still.update(re.findall(r'\.include\s+"([^"]+)"', txt))
    removed = []
    for inc in sorted(used_by_converted - still):
        for d in ASM_INCLUDE_DIRS:
            f = ROOT / d / inc
            if d.endswith('asm/include') and f.is_file():
                f.unlink()
                removed.append(inc)
                break
    print('installed: main.lsf updated for %d objects, %d .s and %d .inc files removed'
          % (sum(len(v) for v in outputs.values()), len(paths), len(removed)))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('files', nargs='+', help='asm data files')
    ap.add_argument('-o', '--out-dir', default='src/data', help='output directory (default src/data)')
    ap.add_argument('--verify', action='store_true', help='compile with arm-none-eabi-gcc and compare with the asm')
    ap.add_argument('--games', default='HEARTGOLD,SOULSILVER')
    ap.add_argument('--dry-run', action='store_true', help='do not write files')
    ap.add_argument('--keep', action='store_true', help='keep the temporary directory')
    ap.add_argument('--no-typed', action='store_true', help='mechanical definitions only')
    ap.add_argument('--no-format', action='store_true', help='do not run clang-format on the output')
    ap.add_argument('--report', help='write a Markdown summary of declarations that disagree with the data')
    ap.add_argument('--mwcc', metavar='BINDIR',
                    help="order and check the output with the real compiler (needs --verify): metroskrew's bin "
                         "directory with mwccarm and mwasmarm. MWCC does not keep definition order, so without "
                         "this the files only match GNU tools")
    ap.add_argument('--install', action='store_true',
                    help='after a clean run: point main.lsf at the C objects, delete the .s files and the '
                         'asm/include/*.inc files only they used')
    ap.add_argument('-v', '--verbose', action='store_true')
    args = ap.parse_args(argv)
    args.games = args.games.split(',')
    os.chdir(ROOT)
    workdir = tempfile.mkdtemp(prefix='s2c-')
    names = []
    asms = []
    for f in args.files:
        a = AsmFile(f)
        asms.append(a)
    symidx = SymbolIndex(ROOT)
    allnames = set()
    for a in asms:
        for sec in a.sections.values():
            allnames.update(it.name for it in sec.items if it.kind == 'label')
    symidx.scan_mentions(allnames)
    decl_index = DeclIndex(ROOT, allnames)
    failed = 0
    report = []
    outputs = OrderedDict()
    for f in args.files:
        try:
            asm, gen, files, problems, warnings, history = convert(f, symidx, decl_index, workdir, args)
        except S2CError as e:
            msg = str(e)
            print('%s: ERROR %s' % (f, msg if len(msg) < 4000 else msg[:4000] + ' ...'))
            failed += 1
            continue
        if not args.no_format and shutil.which('clang-format'):
            # (the repository's .clang-format, wherever the output goes)
            files = [(stem, run(['clang-format', '--assume-filename=src/data/%s.c' % stem], input=t, cwd=ROOT))
                     for stem, t in files]
            if args.verify and not problems:
                # the formatted files are the ones that ship: check them too
                for g in args.games:
                    for stem, t in files:
                        celf, _ = gcc_compile(t, Path(workdir) / (stem + '.fmt.%s.o' % g), g, workdir, stem)
                        if not args.mwcc:
                            gnu = assemble_original(asm, workdir, g)
                            problems += ['%s (formatted): %s' % (g, p) for p in compare(gen, gnu, celf)]
                    if args.mwcc:
                        pr, _ = mwcc_check(asm, gen, files, args.mwcc, workdir, g)
                        problems += ['%s (formatted, mwcc): %s' % (g, p) for p in pr]
        status = 'ok' if not problems else 'MISMATCH'
        if not args.dry_run:
            remove_outputs(args.out_dir, asm.name)
            for stem, t in files:
                out = Path(args.out_dir) / (stem + '.c')
                out.parent.mkdir(parents=True, exist_ok=True)
                out.write_text(t)
        outputs[str(f)] = [stem for stem, _ in files]
        checked = ' (verified%s)' % (', mwcc' if args.mwcc else '') if args.verify and not problems else ''
        where = '%s/%s.c' % (args.out_dir, files[0][0]) if len(files) == 1 else \
            '%s/%s_{1..%d}.c' % (args.out_dir, asm.name, len(files))
        print('%s -> %s: %s%s' % (f, where, status, checked))
        for p in problems[:10]:
            print('    ' + p)
        for w in warnings[:5]:
            print('    warning: ' + w)
        report.append((asm, gen, decl_index))
        typed = sum(1 for r in gen.reps.values() if r.kind == 'typed')
        print('    %d objects, %d typed' % (len(gen.reps), typed))
        for n in gen.notes if args.verbose else [n for n in gen.notes if 'kept untyped' not in n]:
            print('    note: ' + n)
        if args.verbose:
            for h in history:
                print('    fix: ' + h)
        if problems:
            failed += 1
    if args.report:
        # the command line to redo it, as one would type it
        files = [Path(f).as_posix() for f in args.files]
        top = sorted(Path(f).as_posix() for f in ROOT.glob('asm/*.s'))
        if top and all(f in files for f in ('asm/' + Path(t).name for t in top)):
            files = ['asm/*.s'] + [f for f in files if not re.fullmatch(r'asm/[^/]+\.s', f)]
        cmd = ['--verify'] + (['--mwcc', '<metroskrew>/bin'] if args.mwcc else []) + \
            (['--install'] if args.install else []) + ['--report', args.report] + files
        write_report(args.report, report, outputs, cmd)
    if args.install:
        if failed:
            print('not installing: %d file(s) failed' % failed)
        else:
            install(outputs, args.out_dir)
    if not args.keep:
        shutil.rmtree(workdir, ignore_errors=True)
    else:
        print('work directory: ' + workdir)
    return 1 if failed else 0


if __name__ == '__main__':
    sys.exit(main())
