#ifndef INCLUDE_UI_ASSETMANAGER_H_
#define INCLUDE_UI_ASSETMANAGER_H_

#include <unordered_map>
#include <filesystem>
#include <raylib.h>

enum class TextureID
{
    SQUARE_CELL,
    EQUILATERAL_TRIANGLE,
    FLAG
};

enum class FontID
{
    DEFAULT
};

class AssetManager
{
public:
    static AssetManager& Instance();
    AssetManager(AssetManager& other) = delete;
    void operator=(const AssetManager& other) = delete;

    Texture GetTexture(TextureID id);
    Font GetFont(FontID id, int font_size);

    void SetTexturePath(TextureID id, std::filesystem::path path);
    void SetFontPath(FontID id, std::filesystem::path);

private:
    AssetManager();
    ~AssetManager();

    std::unordered_map<TextureID, std::filesystem::path> m_TexturePathes;
    std::unordered_map<FontID, std::filesystem::path> m_FontPathes;

    std::unordered_map<TextureID, Texture> m_Textures;
    std::unordered_map<FontID, std::unordered_map<int, Font>> m_Fonts;

    Texture m_ErrorTexture;
};

#endif // INCLUDE_UI_ASSETMANAGER_H_