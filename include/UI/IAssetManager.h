#ifndef INCLUDE_UI_IASSETMANAGER_H_
#define INCLUDE_UI_IASSETMANAGER_H_

#include "UI/AssetIDs.h"
#include <raylib.h>
#include <memory>

class IAssetManager
{
public:
    virtual ~IAssetManager() = default;

    virtual Texture GetTexture(TextureID asset_id) = 0;
    virtual Font GetFont(FontID asset_id) = 0;
};

#endif // INCLUDE_UI_IASSETMANAGER_H_