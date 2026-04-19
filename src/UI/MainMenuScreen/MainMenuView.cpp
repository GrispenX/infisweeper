#include "UI/MainMenuScreen/MainMenuView.h"
#include "UI/AssetManager.h"

void MainMenuView::Update()
{
    ResolveUILayout();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    Texture logo = AssetManager::Instance().GetTexture(TextureID::MAIN_MENU_LOGO);

    DrawTexturePro(logo, {0, 0, (float)logo.width, (float)logo.height}, m_LogoBounds, {0, 0}, 0, BLACK);

    if(GuiButton(m_NewButtonBounds, "New game"))
    {
        for(auto observer : m_Observers)
        {
            observer->OnNewGameButton();
        }
    }

    if(GuiButton(m_LoadButtonBounds, "Load game"))
    {
        for(auto observer : m_Observers)
        {
            observer->OnLoadGameButton();
        }
    }

    EndDrawing();
}

void MainMenuView::Subscribe(IMainMenuViewObserver* observer)
{
    m_Observers.push_back(observer);
}

void MainMenuView::ResolveUILayout()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();

    Texture logo = AssetManager::Instance().GetTexture(TextureID::MAIN_MENU_LOGO);
    m_LogoBounds.height = 150;
    m_LogoBounds.width = logo.width * m_LogoBounds.height / logo.height;

    static constexpr int gap = 50;
    int text_size = GuiGetStyle(DEFAULT, TEXT_SIZE);
    int y_start = (screen_height - 2 * text_size - 2 * gap - m_LogoBounds.height) / 2;

    m_LogoBounds.x = (screen_width - m_LogoBounds.width) / 2;
    m_LogoBounds.y = y_start;

    m_NewButtonBounds.width = 200;
    m_NewButtonBounds.height = text_size;
    m_NewButtonBounds.x = (screen_width - m_NewButtonBounds.width) / 2;
    m_NewButtonBounds.y = y_start + m_LogoBounds.height + gap;

    m_LoadButtonBounds.width = 200;
    m_LoadButtonBounds.height = text_size;
    m_LoadButtonBounds.x = (screen_width - m_LoadButtonBounds.width) / 2;
    m_LoadButtonBounds.y = m_NewButtonBounds.y + m_NewButtonBounds.height + gap;
}