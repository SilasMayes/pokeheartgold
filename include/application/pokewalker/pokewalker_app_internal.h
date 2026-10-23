#ifndef POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_APP_INTERNAL_H
#define POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_APP_INTERNAL_H

#include "application/pokewalker/pokewalker_app.h"

#include "obj_char_transfer.h"
#include "touchscreen.h"

typedef int (*PokewalkerAppStateFunc)(PokewalkerApp *app);

// The functions of one mode of the app (PokewalkerApp_Main runs them).
typedef struct PokewalkerAppModeFuncs {
    PokewalkerAppStateFunc enter;
    PokewalkerAppStateFunc update;
    PokewalkerAppStateFunc exit;
} PokewalkerAppModeFuncs;

// Pixel positions of one of Spinda's four spots, terminated by x = 0xFF.
typedef struct PokewalkerSpotPixel {
    u8 x;
    u8 y;
} PokewalkerSpotPixel;

extern const PokewalkerAppModeFuncs gPokewalkerAppModes[];
extern const GraphicsModes gPokewalkerAppGraphicsModes;
extern const GraphicsBanks gPokewalkerAppGraphicsBanks;
extern const BgTemplate gPokewalkerAppBgTemplate_Main1;
extern const BgTemplate gPokewalkerAppBgTemplate_Main2;
extern const BgTemplate gPokewalkerAppBgTemplate_Main3;
extern const BgTemplate gPokewalkerAppBgTemplate_Sub0;
extern const BgTemplate gPokewalkerAppBgTemplate_Sub1;
extern const BgTemplate gPokewalkerAppBgTemplate_Sub2;

extern const u16 gPokewalkerPictureFiles[][2];  // Pokewalker picture file per species: {male, female}
extern const u8 gWindowBankScreens[];           // window bank -> 0 main screen, 1 sub screen
extern const u8 gPokewalkerAppSpritePalettes[]; // palettes of the first 17 sprites
extern const OamCharTransferParam gPokewalkerAppOamCharTransferParam;
extern const SpriteResourceCountsListUnion gPokewalkerAppSpriteResourceCounts;
extern const OamManagerParam gPokewalkerAppOamManagerParam;
// Cursor positions {x, y, anim, palette}
extern const u8 gPokewalkerAppCursorX[];
extern const u8 gPokewalkerAppCursorY[];
extern const u8 gPokewalkerAppCursorAnims[];
extern const u8 gPokewalkerAppCursorPalettes[];
extern const ManagedSpriteTemplate gPokewalkerAppSpriteTemplates[];
extern const ManagedSpriteTemplate gPokewalkerAppMainSpriteTemplate;
extern const ManagedSpriteTemplate gPokewalkerAppSubSpriteTemplate;
extern const PokewalkerSpotPixel *gSpindaSpotPixels[];
extern const TouchscreenHitbox *gTouchButtons[];
extern const WindowTemplate *gWindowBank2Templates[];
extern const WindowTemplate *gWindowBank1Templates[];
extern const WindowTemplate *gWindowBank7Templates[];
extern const WindowTemplate *gWindowBank0Templates[];
extern const WindowTemplate *gWindowBank5Templates[];
extern const WindowTemplate *gWindowBank3Templates[];
extern const WindowTemplate *gWindowBank4Templates[];
extern const WindowTemplate *gWindowBank6Templates[];

extern const PokewalkerAppStateFunc gMainMenuStates[];
// Cursor positions of the menus' items.
extern const int gReceiveMenuCursorPositions[];
extern const int gFullMenuCursorPositions[];
extern const int gTopMenuCursorPositions[];
extern const PokewalkerAppStateFunc gQuitMessageStates[];
extern const PokewalkerAppStateFunc gEraseRecordsStates[];
extern const PokewalkerAppStateFunc gStartStrollStates[];
extern const PokewalkerAppStateFunc gLinkSaveStates[];
extern const PokewalkerAppStateFunc gStrollReportStates[];
extern const GraphicsBanks gSelectMonGraphicsBanks;
extern const GraphicsModes gSelectMonGraphicsModes;
extern const ObjCharTransferTemplate gSelectMonObjCharTransferTemplate;
extern const OverlayManagerTemplate gEventLogAppTemplate;
extern const BgTemplate gBoxDisplayBgTemplateSub1;
extern const BgTemplate gBoxDisplayBgTemplateSub3;

extern const u8 gStrollTextWindowWidths[];
extern const u8 sSpindaSpotMask[]; // where Spinda's spots may be drawn (2bpp picture)
extern const u8 *const gPokewalkerRouteImages[];
// Bitmaps of the upload image
extern const u8 gPokewalkerUploadImageArrowRightShifted[];
extern const u8 gPokewalkerUploadImageArrowDownShifted[];
extern const u8 gPokewalkerUploadImageArrowRightHollow[];
extern const u8 ov112_021F55B8[];
extern const u8 gPokewalkerUploadImageArrowLeftHollow[];
extern const u8 gPokewalkerUploadImageArrowLeft[];
extern const u8 gPokewalkerUploadImageArrowDownHollow[];
extern const u8 gPokewalkerUploadImageArrowUpHollow[];
extern const u8 ov112_021F5608[];
extern const u8 ov112_021F5618[];
extern const u8 ov112_021F5628[];
extern const u8 ov112_021F5638[];
extern const u8 ov112_021F5648[];
extern const u8 gPokewalkerUploadImageMusicNote[];
extern const u8 ov112_021F5668[];
extern const u8 ov112_021F5678[];
extern const u8 gPokewalkerUploadImageArrowLeftShifted[];
extern const u8 gPokewalkerUploadImageArrowDown[];
extern const u8 ov112_021F56A8[];
extern const u8 gPokewalkerUploadImageArrowRight[];
extern const u8 gPokewalkerUploadImageArrowUp[];
extern const u8 gPokewalkerUploadImageHeart[];
extern const u8 ov112_021F56E8[];
extern const u8 gPokewalkerUploadImagePokeBall[];
extern const u8 ov112_021F5708[];
extern const u8 gPokewalkerUploadImageArrowUpShifted[];
extern const u8 ov112_021F5738[];
extern const u8 ov112_021F5748[];
extern const u8 gPokewalkerUploadImageDigit0[];
extern const u8 gPokewalkerUploadImageDigit2[];
extern const u8 gPokewalkerUploadImageDigit6[];
extern const u8 gPokewalkerUploadImageDigit8[];
extern const u8 ov112_021F57D8[];
extern const u8 gPokewalkerUploadImageSlash[];
extern const u8 gPokewalkerUploadImageColon[];
extern const u8 gPokewalkerUploadImageDigit4[];
extern const u8 gPokewalkerUploadImageDigit1[];
extern const u8 gPokewalkerUploadImageDigit7[];
extern const u8 ov112_021F5898[];
extern const u8 gPokewalkerUploadImageDigit9[];
extern const u8 ov112_021F58D8[];
extern const u8 ov112_021F58F8[];
extern const u8 gPokewalkerUploadImageDigit3[];
extern const u8 gPokewalkerUploadImageDash[];
extern const u8 ov112_021F5958[];
extern const u8 gPokewalkerUploadImageDigit5[];
extern const u8 ov112_021F5998[];
extern const u8 ov112_021F59D8[];
extern const u8 ov112_021F5A18[];
extern const u8 ov112_021F5A58[];
extern const u8 ov112_021F5A98[];
extern const u8 ov112_021F5AD8[];
extern const u8 ov112_021F5B18[];
extern const u8 ov112_021F5B58[];
extern const u8 ov112_021F5B98[];
extern const u8 ov112_021F5BD8[];
extern const u8 ov112_021F5C18[];
extern const u8 ov112_021F5C58[];
extern const u8 ov112_021F5C98[];
extern const u8 ov112_021F5CD8[];
extern const u8 ov112_021F5D18[];
extern const u8 ov112_021F5D58[];
extern const u8 ov112_021F5DB8[];
extern const u8 ov112_021F5E18[];
extern const u8 ov112_021F5E78[];
extern const u8 ov112_021F5ED8[];
extern const u8 ov112_021F5F38[];
extern const u8 ov112_021F5F98[];
extern const u8 ov112_021F5FF8[];
extern const u8 ov112_021F6058[];
extern const u8 ov112_021F60B8[];
extern const u8 ov112_021F6118[];
extern const u8 ov112_021F6178[];
extern const u8 ov112_021F61F8[];
extern const u8 ov112_021F6278[];
extern const u8 ov112_021F62F8[];
extern const u8 ov112_021F6378[];
extern const u8 ov112_021F63F8[];
extern const u8 ov112_021F6498[];
extern const u8 ov112_021F6538[];
extern const u8 ov112_021F65D8[];
extern const u8 ov112_021F6678[];
extern const u8 ov112_021F6718[];
extern const u8 ov112_021F67D8[];
extern const u8 ov112_021F6898[];
extern const u8 ov112_021F6DD8[];
extern const u8 ov112_021F7018[];
extern const u8 ov112_021F70D8[];
extern const u8 ov112_021F71D8[];
extern const u8 ov112_021F72D8[];
extern const u8 ov112_021F7418[];
extern const u8 ov112_021F7558[];
extern const u8 ov112_021F7698[];
extern const u8 ov112_021F77D8[];
extern const u8 ov112_021F7918[];
extern const u8 ov112_021F7A58[];
extern const u8 ov112_021F7B98[];
extern const u8 ov112_021F7D18[];
extern const u8 ov112_021F7E98[];
extern const u8 ov112_021F8018[];
extern const u8 ov112_021F8198[];
extern const u8 ov112_021F8318[];
extern const u8 ov112_021F8498[];
extern const u8 ov112_021F8618[];
extern const u8 ov112_021F8798[];
extern const u8 ov112_021F8918[];
extern const u8 ov112_021F8A98[];
extern const u8 ov112_021F8C18[];
extern const u8 ov112_021F8D98[];
extern const u8 ov112_021F8F18[];
extern const u8 ov112_021F9098[];
extern const u8 ov112_021F9218[];
extern const u8 ov112_021F9398[];
extern const u8 ov112_021F9518[];
extern const u8 ov112_021F9698[];
extern const u8 ov112_021F9818[];
extern const u8 ov112_021F9998[];
extern const u8 ov112_021F9B18[];
extern const u8 ov112_021F9C98[];
extern const u8 ov112_021F9E18[];
extern const u8 ov112_021F9F98[];
extern const u8 ov112_021FA118[];
extern const u8 ov112_021FA298[];
extern const u8 ov112_021FA418[];
extern const u8 ov112_021FA598[];
extern const u8 ov112_021FA718[];
extern const u8 ov112_021FA898[];
extern const u8 ov112_021FAA18[];
extern const u8 ov112_021FAB98[];
extern const u8 ov112_021FAD18[];
extern const u8 ov112_021FAE98[];
extern const u8 ov112_021FB018[];
extern const u8 ov112_021FB198[];
extern const u8 ov112_021FB318[];
extern const u8 ov112_021FB498[];
extern const u8 ov112_021FB618[];
extern const u8 ov112_021FB798[];
extern const u8 ov112_021FB918[];
extern const u8 ov112_021FBA98[];
extern const u8 ov112_021FBC18[];
extern const u8 ov112_021FBD98[];
extern const u8 ov112_021FBF18[];
extern const u8 ov112_021FC098[];
extern const u8 ov112_021FC218[];
extern const u8 ov112_021FC398[];
extern const u8 ov112_021FC518[];
extern const u8 ov112_021FC698[];
extern const u8 ov112_021FC818[];
extern const u8 ov112_021FC998[];
extern const u8 ov112_021FCB18[];
extern const u8 ov112_021FCC98[];
extern const u8 ov112_021FCE18[];
extern const u8 ov112_021FCF98[];
extern const u8 ov112_021FD118[];
extern const u8 ov112_021FD298[];
extern const u8 ov112_021FD418[];
extern const u8 ov112_021FD598[];
extern const u8 ov112_021FD718[];
extern const u8 ov112_021FD898[];
extern const u8 ov112_021FDA18[];
extern const u8 ov112_021FDB98[];
extern const u8 ov112_021FDD18[];
extern const u8 ov112_021FDE98[];
extern const u8 ov112_021FE018[];
extern const u8 ov112_021FE198[];

#endif // POKEHEARTGOLD_APPLICATION_POKEWALKER_POKEWALKER_APP_INTERNAL_H
