#ifndef INCLUDE_UI_ASSETMANAGER_H_
#define INCLUDE_UI_ASSETMANAGER_H_

#include "UI/IAssetManager.h"
#include <unordered_map>
#include <filesystem>

class AssetManager : public IAssetManager
{
public:
    AssetManager(
        std::unordered_map<TextureID, std::filesystem::path>& texture_pathes,
        std::unordered_map<FontID, std::filesystem::path>& font_pathes
    );
    ~AssetManager();

    Texture GetTexture(TextureID asset_id) override;
    Font GetFont(FontID asset_id) override;

private:
    std::unordered_map<TextureID, Texture> m_Textures;
    std::unordered_map<FontID, Font> m_Fonts;
};

#endif // INCLUDE_UI_ASSETMANAGER_H_