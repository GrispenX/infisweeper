#include <raylib.h>
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"

#include <unordered_map>

#include "UI/AssetManager.h"
#include "UI/MainMenuScreen/MainMenuView.h"
#include "UI/MainMenuScreen/MainMenuScreen.h"


int main()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(800, 800, "Test");

    std::unordered_map<TextureID, std::filesystem::path> textures {
        {TextureID::SQUARE_CELL, "/home/grispenx/projects/infisweeper/assets/Square.png"},
        {TextureID::EQUILATERAL_TRIANGLE, "/home/grispenx/projects/infisweeper/assets/Triangle.png"},
        {TextureID::FLAG, "/home/grispenx/projects/infisweeper/assets/flag.png"}
    };

    std::unordered_map<FontID, std::filesystem::path> fonts {
        {FontID::DEFAULT, "/home/grispenx/projects/infisweeper/assets/SpaceMono-Bold.ttf"}
    };

    for(auto [id, path] : textures)
    {
        AssetManager::Instance().SetTexturePath(id, path);
    }

    for(auto [id, path] : fonts)
    {
        AssetManager::Instance().SetFontPath(id, path);
    }

    std::unique_ptr<IScreen> screen = std::make_unique<MainMenuScreen>(
        std::make_unique<MainMenuView>()
    );

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiSetFont(AssetManager::Instance().GetFont(FontID::DEFAULT, 30));

    while(!WindowShouldClose())
    {
        std::unique_ptr<IScreen> next = screen->Update();
        if(next) screen = std::move(next);
    }
}
