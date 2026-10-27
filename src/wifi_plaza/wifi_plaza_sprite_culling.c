#include "global.h"

#include "model_box_test.h"
#include "wifi_plaza/wifi_plaza_internal.h"

// Whether a player's billboard is inside the view: box test of its model's bounding box, moved to the billboard
// position and scaled by the box scale.
BOOL WiFiPlaza_IsBillboardInView(BillboardObject *billboard) {
    VecFx32 position;
    BoxTestBounds bounds;
    MtxFx33 rotation;
    NNSG3dResMdl *model = BillboardObject_GetModel(billboard);
    NNSG3dResMdlInfo *info;
    if (model != NULL) {
        info = &model->info;
    } else {
        info = NULL;
    }
    position = *BillboardObject_GetPosition(billboard);
    bounds.width = info->boxW;
    bounds.height = info->boxH;
    bounds.depth = info->boxH;
    bounds.scaleX = info->boxPosScale >> FX32_SHIFT;
    bounds.scaleY = info->boxPosScale >> FX32_SHIFT;
    bounds.scaleZ = info->boxPosScale >> FX32_SHIFT;
    position.x += FX_Mul(info->boxX, info->boxPosScale);
    position.y += FX_Mul(info->boxY, info->boxPosScale);
    position.z += FX_Mul(info->boxZ, info->boxPosScale);
    position.z -= FX_Mul(info->boxH, info->boxPosScale);
    MTX_Identity33_(&rotation);
    MI_Copy36B(&rotation, &NNS_G3dGlb.prmBaseRot);
    NNS_G3dGlb.flag &= ~0xA4;
    NNS_G3dGlbSetBaseScale(BillboardObject_GetScale(billboard));
    if (!GF3d_BoundsBoxTest(&position, &bounds)) {
        return FALSE;
    }
    return TRUE;
}
