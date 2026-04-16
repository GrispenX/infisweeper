#include "UI/AssetManager.h"

AssetManager::AssetManager()
{
    Image img = GenImageChecked(64, 64, 32, 32, MAGENTA, BLACK);
    m_ErrorTexture = LoadTextureFromImage(img);
    UnloadImage(img);
}

AssetManager::~AssetManager()
{
    for(auto [id, texture] : m_Textures)
    {
        UnloadTexture(texture);
    }

    for(auto [id, font] : m_Fonts)
    {
        for(auto [size, sized_font] : font)
        {
            UnloadFont(sized_font);
        }
    }
}

AssetManager& AssetManager::Instance()
{
    static AssetManager instance;
    return instance;
}

void AssetManager::SetTexturePath(TextureID id, std::filesystem::path path)
{
    auto it = m_Textures.find(id);
    if(it != m_Textures.end())
    {
        UnloadTexture(it->second);
        m_Textures.erase(id);
    }
    m_TexturePathes[id] = path;
}

void AssetManager::SetFontPath(FontID id, std::filesystem::path path)
{
    auto it = m_Fonts.find(id);
    if(it != m_Fonts.end())
    {
        for(auto [size, font] : it->second)
        {
            UnloadFont(font);            
        }
        m_Fonts.erase(id);
    }
    m_FontPathes[id] = path;
}

Texture AssetManager::GetTexture(TextureID id)
{
    auto texture_it = m_Textures.find(id);
    if(texture_it != m_Textures.end())
    {
        return texture_it->second;
    }

    auto path_it = m_TexturePathes.find(id);
    if(path_it != m_TexturePathes.end())
    {
        Texture texture = LoadTexture(path_it->second.c_str());
        if(texture.id != 0)
        {
            m_Textures[id] = texture;
            return texture;
        }
    }

    return m_ErrorTexture;
}

Font AssetManager::GetFont(FontID id, int font_size)
{
    auto font_it = m_Fonts.find(id);
    if(font_it != m_Fonts.end())
    {
        auto size_it = font_it->second.find(font_size);
        if(size_it != font_it->second.end())
        {
            return size_it->second;
        }
    }

    auto path_it = m_FontPathes.find(id);
    if(path_it != m_FontPathes.end())
    {
        Font font = LoadFontEx(path_it->second.c_str(), font_size, nullptr, 0);
        if(font.texture.id != 0)
        {
            m_Fonts[id][font_size] = font;
            return font;
        }
    }

    return GetFontDefault();
}