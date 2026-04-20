#include "Application.h"
#include "UI/AssetManager.h"
#include <raylib.h>
#include "raygui.h"
#include <filesystem>

Application::Application(std::unique_ptr<IScreen> initial_screen) :
    m_Screen(std::move(initial_screen))
{}

void Application::Run()
{
    SetConfigFlags(FLAG_WINDOW_RESIZABLE);
    InitWindow(0, 0, "Infisweeper");

    std::filesystem::path assets_dir = "../assets/";

    std::unordered_map<TextureID, std::filesystem::path> textures {
        {TextureID::SQUARE_CELL, assets_dir / "Square.png"},
        {TextureID::EQUILATERAL_TRIANGLE, assets_dir / "Triangle.png"},
        {TextureID::FLAG, assets_dir / "flag.png"},
        {TextureID::MAIN_MENU_LOGO, assets_dir / "logo.png"}
    };

    std::unordered_map<FontID, std::filesystem::path> fonts {
        {FontID::DEFAULT, assets_dir / "Roboto-Regular.ttf"}
    };

    for(auto [id, path] : textures)
    {
        AssetManager::Instance().SetTexturePath(id, path);
    }

    for(auto [id, path] : fonts)
    {
        AssetManager::Instance().SetFontPath(id, path);
    }

    GuiSetStyle(DEFAULT, TEXT_SIZE, 30);
    GuiSetFont(AssetManager::Instance().GetFont(FontID::DEFAULT, 30));

    while(!WindowShouldClose())
    {
        std::unique_ptr<IScreen> next_scene = m_Screen->Update();
        if(next_scene)
        {
            m_Screen = std::move(next_scene);
        }
    }
}