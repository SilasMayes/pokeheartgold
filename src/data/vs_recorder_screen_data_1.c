// Converted from asm/vs_recorder_screen_data.s (part 1 of 3) by tools/s2c.py.
//
// MWCC sorts the data of a file by size before laying it out, so the definitions are in the order
// that makes the sort reproduce the asm layout, and the data is split across files where one sort
// cannot. Keep that when editing, or rerun tools/s2c.py.

#include "global.h"

#include "msgdata/msg/msg_0013.h"

#include "vs_recorder_app_internal.h"

#pragma force_active on

extern const struct VsRecorderMenuEntry sVsRecorderBattleVideosMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderOtherVideosMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderDeleteVideosMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderDeleteOtherVideoMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode1SubMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderSearchMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderQuitMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode4QuitMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode3QuitMenu[5];
extern const struct VsRecorderMenuEntry sVsRecorderMode2QuitMenu[5];

const VsRecorderMenuEntry sVsRecorderMode0MenuNoFrontier[5] = {
    { 1, 1, msg_0013_00000, 0, 1, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderBattleVideosMenu },
    { 1, 1, msg_0013_00002, 4, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderBattleVideosMenu[5] = {
    { 1, 1, msg_0013_00004, 6, 4, 3, 0,          (int)0xFBFBFBFB, NULL                        },
    { 1, 1, msg_0013_00005, 7, 1, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderOtherVideosMenu  },
    { 1, 1, msg_0013_00006, 1, 1, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderDeleteVideosMenu },
    { 1, 1, msg_0013_00003, 5, 3, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderOtherVideosMenu[5] = {
    { 1, 1, msg_0013_00008, 7, 4, 3, 1,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00008, 7, 4, 3, 2,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00008, 7, 4, 3, 3,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00003, 5, 3, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderDeleteVideosMenu[5] = {
    { 1, 1, msg_0013_00039, 6, 7, 3, 0,          (int)0xFBFBFBFB, NULL                            },
    { 1, 1, msg_0013_00040, 7, 0, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderDeleteOtherVideoMenu },
    { 1, 1, msg_0013_00003, 5, 3, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                            },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                            },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                            },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderDeleteOtherVideoMenu[5] = {
    { 1, 1, msg_0013_00041, 7, 7, 3, 1,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00041, 7, 7, 3, 2,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00041, 7, 7, 3, 3,          (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00003, 5, 3, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode1Menu[5] = {
    { 1, 1, msg_0013_00043, 2,  1,  3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderMode1SubMenu },
    { 1, 1, msg_0013_00044, 9,  20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                    },
    { 1, 1, msg_0013_00002, 14, 2,  2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                    },
    { 0, 0, 0,              0,  0,  0, 0,          0,               NULL                    },
    { 0, 0, 0,              0,  0,  0, 0,          0,               NULL                    },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderMode1SubMenu[5] = {
    { 1, 1, msg_0013_00045, 10, 20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                  },
    { 1, 1, msg_0013_00046, 0,  1,  3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderSearchMenu },
    { 1, 1, msg_0013_00047, 11, 20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                  },
    { 1, 1, msg_0013_00003, 5,  3,  4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                  },
    { 0, 0, 0,              0,  0,  0, 0,          0,               NULL                  },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderSearchMenu[5] = {
    { 1, 1, msg_0013_00048, 1, 20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00049, 0, 20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00050, 0, 20, 6, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00003, 5, 3,  4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0,  0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode5Menu[5] = {
    { 1, 1, msg_0013_00052, 0, 9, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                },
    { 1, 1, msg_0013_00051, 0, 8, 3, 0,          (int)0xFBFBFBFB, NULL                },
    { 1, 1, msg_0013_00002, 2, 2, 3, 999,        (int)0xFBFBFBFB, sVsRecorderQuitMenu },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderViewVideosMenu[5] = {
    { 1, 1, msg_0013_00105, 7, 16, 3, 200,        (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00106, 0, 17, 3, 210,        (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00107, 8, 18, 3, 220,        (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00003, 3, 3,  4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0,  0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode4Menu[5] = {
    { 1, 1, msg_0013_00078, 0, 12, 3, 0,   (int)0xFBFBFBFB, NULL                     },
    { 1, 1, msg_0013_00079, 1, 13, 3, 1,   (int)0xFBFBFBFB, NULL                     },
    { 1, 1, msg_0013_00002, 2, 2,  3, 999, (int)0xFBFBFBFB, sVsRecorderMode4QuitMenu },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
};

const VsRecorderMenuEntry sVsRecorderMode3MenuNoFrontier[5] = {
    { 1, 1, msg_0013_00092, 0, 14, 3, 300, (int)0xFBFBFBFB, NULL                     },
    { 1, 1, msg_0013_00002, 2, 2,  3, 999, (int)0xFBFBFBFB, sVsRecorderMode3QuitMenu },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode3Menu[5] = {
    { 1, 1, msg_0013_00092, 0, 14, 3, 300, (int)0xFBFBFBFB, NULL                     },
    { 1, 1, msg_0013_00093, 1, 15, 3, 301, (int)0xFBFBFBFB, NULL                     },
    { 1, 1, msg_0013_00002, 2, 2,  3, 999, (int)0xFBFBFBFB, sVsRecorderMode3QuitMenu },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
    { 0, 0, 0,              0, 0,  0, 0,   0,               NULL                     },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderSendVideoMenu[5] = {
    { 1, 1, msg_0013_00130, 4, 19, 3, 100,        (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00003, 3, 3,  4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0,  0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0,  0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0,  0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode2Menu[5] = {
    { 1, 1, msg_0013_00103, 2, 1, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderViewVideosMenu },
    { 1, 1, msg_0013_00104, 6, 1, 3, 9999,       (int)0xFBFBFBFB, sVsRecorderSendVideoMenu  },
    { 1, 1, msg_0013_00002, 9, 2, 3, 999,        (int)0xFBFBFBFB, sVsRecorderMode2QuitMenu  },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                      },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                      },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderMode4QuitMenu[5] = {
    { 1, 1, msg_0013_00130, 5, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00131, 4, 2, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderMode2QuitMenu[5] = {
    { 1, 1, msg_0013_00130, 4, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00131, 3, 2, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used above its definition
const struct VsRecorderMenuEntry sVsRecorderMode3QuitMenu[5] = {
    { 1, 1, msg_0013_00130, 5, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00131, 4, 2, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderQuitMenu[5] = {
    { 1, 1, msg_0013_00130, 4, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 1, 1, msg_0013_00131, 3, 2, 4, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL },
};

// not static: used in another part of asm/vs_recorder_screen_data.s
const struct VsRecorderMenuEntry sVsRecorderMode0Menu[5] = {
    { 1, 1, msg_0013_00000, 0, 1, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, sVsRecorderBattleVideosMenu },
    { 1, 1, msg_0013_00001, 3, 5, 3, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                        },
    { 1, 1, msg_0013_00002, 4, 2, 2, 0xFBFBFBFB, (int)0xFBFBFBFB, NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
    { 0, 0, 0,              0, 0, 0, 0,          0,               NULL                        },
};
