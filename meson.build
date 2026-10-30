# Native build of HeartGold/SoulSilver against libntr (Linux desktop and Android/Thor).
# Modeled on SilasMayes/pokeplatinum's meson build. The DS ROM keeps building with make;
# nothing here is used by it.
#
# No data pipeline: NARCs come from the player's ROM at runtime (SIM_NDSExtractTo). The
# compile-time IDs the C code needs (msgdata/msg/*.h, *.naix) are checked in under
# generated/ and refreshed with tools/port/gen_headers.sh.
#
# Linux:   meson setup build_linux && meson compile -C build_linux
# Android: see meson/cross_android.ini (NDK clang, -Dbuild_target=android)
project('pokeheartgold', ['c', 'cpp', 'nasm'],
    version: '1.0',
    meson_version: '>=1.3.0',
    default_options: [
        'buildtype=plain',
        'warning_level=0',
    ]
)

build_target = get_option('build_target')
is_desktop = (build_target == 'linux')
cc = meson.get_compiler('c')

############################################################
###                    INCLUDE PATHS                     ###
############################################################
# generated/: msgdata/msg/*.h and *.naix, checked in (see tools/port/gen_headers.sh). The DS
# build writes the same files under files/; generated/ comes first so the port never depends
# on a make run. files/ is still needed for the checked-in headers there (script event IDs).
# include/port_sdk/: port versions of the few SDK headers below that can't be used as is.
hgss_includes = include_directories(
    'include/port_sdk',
    'include',
    'include/library',
    'generated',
    'files',
    'src',
)

# The decomp's own SDK headers (lib/include) declare SDK internals the game reaches into
# (nnsys/*_internal.h, dwc/*_internal.h, nitro/wm/wm_internal.h, ...). libntr is the SDK
# here, so its headers and the system's must win: -idirafter puts lib/include behind both,
# and only headers neither has (the internal ones) are taken from it.
sdk_fallback_args = ['-idirafter', meson.current_source_dir() / 'lib' / 'include']

############################################################
###                    COMPILER FLAGS                    ###
############################################################
# mwcc defaults this code was written against:
#   -char signed      -> -fsigned-char (aarch64 chars are unsigned by default)
#   -enum int         -> nothing (clang/gcc already use int-sized enums for these values)
#   -gccext,on        -> gnu99 (typeof in ARRAY_ASSIGN, statement expressions)
# Plus the Platinum port's lessons: the decomp type-puns and relies on wrapping signed
# arithmetic, so never let the optimizer assume otherwise.
hgss_common_args = [
    '-fsigned-char',
    '-fno-strict-aliasing',
    '-fwrapv',
    '-g',
    '-D' + get_option('game_version'),
    '-DGAME_REMASTER=0',
    '-DENGLISH',
    '-DPM_KEEP_ASSERTS',
]

if get_option('logging_enabled')
    hgss_common_args += '-DLOGGING_ENABLED'
endif

# mwcc pragmas (#pragma thumb, opt_*, force_active, ...) are meaningless here
hgss_common_args += cc.get_supported_arguments('-Wno-unknown-pragmas')

# libntr's compile args carry -w for its own sources. Game code takes the SDK defines and
# include paths from the dependencies but keeps a curated warning set, so the 64-bit hazards
# (pointer <-> u32 casts) stay visible.
if get_option('lp64_warnings')
    hgss_warning_args = cc.get_supported_arguments(
        '-Wint-to-pointer-cast',
        '-Wpointer-to-int-cast',
        '-Wint-conversion',
        '-Wincompatible-pointer-types',
        '-Wimplicit-function-declaration',
        '-Wreturn-type',
    )
else
    hgss_warning_args = ['-w']
endif

if build_target == 'android'
link_args = [
    # libmain.so is loaded by SDL's Java activity, which looks up SDL_main
    '-static-libstdc++',
    '-Wl,--no-undefined',
    '-Wl,-z,max-page-size=16384',
    '-Wl,-soname,libmain.so',
]
else
link_args = []
endif

############################################################
###                     DEPENDENCIES                     ###
############################################################
# The game code check in libntr's carts accepts IPKE (HG) and IPGE (SS); the one binary
# runs either ROM once GAME_VERSION is read from the header at runtime.
libntr_prj = subproject('libntr',
    default_options: [
        'card_game_code=' + (get_option('game_version') == 'HEARTGOLD' ? 'IPKE' : 'IPGE'),
        'card_maker_code=01',
    ])

nitrosdk_dep = dependency('NitroSDK',
    default_options: {
        'mwrap_sdk': '2.0/sp2p2',
    }
)

nitrosystem_dep = dependency('NitroSystem',
    default_options: {
        'mwrap_sdk': '2.0/sp2p2',
    }
)

nitrowifi_dep = dependency('NitroWiFi',
    default_options: {
        'mwrap_sdk': '2.0/sp2p2',
    }
)

nitrodwc_dep = dependency('NitroDWC',
    default_options: {
        'mwrap_sdk': '2.0/sp2p2',
        'link_ppwlobby': true,
    }
)

libvct_dep = dependency('libvct')

sdk_deps = [nitrosdk_dep, nitrosystem_dep, nitrowifi_dep, nitrodwc_dep, libvct_dep]

# The SDK defines that libntr's nitrosdk_dep would pass, minus its -w
nitrosdk_args = libntr_prj.get_variable('nitrosdk_args')
nitrosdk_defines = []
foreach a : nitrosdk_args
    if a != '-w'
        nitrosdk_defines += a
    endif
endforeach

# Headers only, as system includes so warnings inside the SDK headers stay quiet
sdk_headers_deps = []
foreach d : sdk_deps
    sdk_headers_deps += d.partial_dependency(includes: true, sources: true).as_system('system')
endforeach

hgss_c_args = ['-std=gnu99'] + hgss_common_args + nitrosdk_defines + sdk_fallback_args + hgss_warning_args

############################################################
###                       SOURCES                        ###
############################################################
subdir('src')

# Game-side libraries the DS build links from lib/src (nitrocrypto, particle system)
hgss_lib_c = files(
    'lib/src/nitrocrypto_alloc.c',
    'lib/src/nitrocrypto_bn_arith.c',
    'lib/src/nitrocrypto_bn_bin2bn.c',
    'lib/src/nitrocrypto_bn_bits.c',
    'lib/src/nitrocrypto_bn_ctx.c',
    'lib/src/nitrocrypto_bn_exp.c',
    'lib/src/nitrocrypto_bn_expand.c',
    'lib/src/nitrocrypto_bn_fix_top.c',
    'lib/src/nitrocrypto_bn_free.c',
    'lib/src/nitrocrypto_bn_num_bits.c',
    'lib/src/nitrocrypto_bn_word.c',
    'lib/src/nitrocrypto_rc4.c',
    'lib/src/nitrocrypto_rc4_fast.c',
    'lib/src/nitrocrypto_rc4_init.c',
    'lib/src/nitrocrypto_sign.c',
    'lib/src/spl_anim.c',
    'lib/src/spl_draw.c',
    'lib/src/spl_draw_ptcl.c',
    'lib/src/spl_emitter.c',
    'lib/src/spl_field.c',
    'lib/src/spl_generate.c',
    'lib/src/spl_list.c',
    'lib/src/spl_manager.c',
    'lib/src/spl_random.c',
)

# Port-only replacements for what the DS build links from MSL, the mwcc runtime and
# lib/dsprot (lib/port/ is not part of the make build)
hgss_port_lib_c = files(
    'lib/port/dsprot_port.c',
    'lib/port/heap_debug.c',
    'lib/port/msl_runtime.c',
    'lib/port/stats_upload_data.c',
)

############################################################
###                   WI-FI PLAZA LOBBY                  ###
############################################################
# Same split as Platinum's ppwlobby: built for the desktop, left out on Android (the lobby
# server is gone and the C++ assumes 32-bit pointers in places clang rejects).
build_lobby = get_option('lobby').require(is_desktop,
    error_message: 'the Wi-Fi Plaza lobby is desktop-only').allowed()

hgss_link_with = []
if not build_lobby
    # Without the library the Plaza's PPW_* calls go to stubs that fail to connect
    hgss_port_lib_c += files('lib/port/ppw_lobby_stub.c')
endif
if build_lobby
    hgss_lobby = static_library('hgss_lobby',
        sources: [hgss_lobby_c, hgss_lobby_cpp, files('lib/port/lobby_aliases.c', 'lib/port/dwc_lobby_chat_data.c')],
        c_args: hgss_c_args,
        cpp_args: hgss_common_args + nitrosdk_defines + sdk_fallback_args + [
            '-std=gnu++03',
            '-include', 'lobby_cpp_prelude.h',
            '-fpermissive',
            '-fno-exceptions',
            '-fno-rtti',
            '-w',
        ],
        include_directories: hgss_includes,
        dependencies: sdk_headers_deps,
        pic: true,
        native: is_desktop,
    )
    hgss_link_with += hgss_lobby
endif

############################################################
###                     MAIN BINARY                      ###
############################################################
# Game code is compiled into a static library that only sees the SDK headers (so the -w in
# libntr's compile args doesn't reach it), then linked whole into the binary together with
# the full SDK dependencies (libraries, crt objects, link args).
hgss_game = static_library('hgss_game',
    sources: [hgss_c, hgss_lib_c, hgss_port_lib_c],
    c_args: hgss_c_args,
    c_pch: 'include/pch/global_pch.h',
    include_directories: hgss_includes,
    dependencies: sdk_headers_deps,
    pic: true,
    native: is_desktop,
)

if build_target == 'linux'
main = executable('main',
    link_whole: hgss_game,
    link_with: hgss_link_with,
    dependencies: sdk_deps,
    link_args: link_args + ['-Wl,--no-undefined'],
    native: true,
)
elif build_target == 'android'
# SDL's Android activity loads libmain.so and calls SDL_main (libntr's main()). Linked as an
# "executable" with -shared, as in Platinum: libntr's static libraries are declared non-PIC
# and meson refuses them in a shared_library(), but the android target compiles everything
# with -fPIC anyway, so the result is a normal .so. The APK script renames main.so.
main = executable('main',
    link_whole: hgss_game,
    link_with: hgss_link_with,
    dependencies: sdk_deps,
    link_args: link_args + ['-shared'],
    name_suffix: 'so',
    native: false,
)
endif
