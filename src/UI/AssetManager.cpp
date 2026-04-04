#include "UI/AssetManager.h"

AssetManager::AssetManager(
    std::unordered_map<TextureID, std::filesystem::path>& texture_pathes,
    std::unordered_map<FontID, std::filesystem::path>& font_pathes)
{
    for(const auto& [id, path] : texture_pathes)
    {
        m_Textures[id] = LoadTexture(path.c_str());
    }

    for(const auto& [id, path] : font_pathes)
    {
        m_Fonts[id] = LoadFontEx(path.c_str(), 100, nullptr, 0);
    }
}

AssetManager::~AssetManager()
{
    for(const auto& [id, texture] : m_Textures)
    {
        UnloadTexture(texture);
    }

    for(const auto& [id, font] : m_Fonts)
    {
        UnloadFont(font);
    }
}

Texture AssetManager::GetTexture(TextureID asset_id)
{
    return m_Textures.at(asset_id);
}

Font AssetManager::GetFont(FontID asset_id)
{
    return m_Fonts.at(asset_id);
}