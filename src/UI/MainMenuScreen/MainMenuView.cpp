#include "UI/MainMenuScreen/MainMenuView.h"
#include <raylib.h>
#include "raygui.h"
#include "UI/AssetManager.h"

void MainMenuView::Update()
{
    const float screen_width = (float)GetScreenWidth();
    const float screen_height = (float)GetScreenHeight();

    Rectangle new_game_button {
        .x = screen_width / 2.0f - 100.0f,
        .y = screen_height / 2.0f - 40.0f,
        .width = 200.0f,
        .height = 40.0f
    };

    Rectangle load_game_button {
        .x = screen_width / 2.0f - 100.0f,
        .y = screen_height / 2.0f + 40.0f,
        .width = 200.0f,
        .height = 40.0f
    };

    BeginDrawing();
    ClearBackground(GRAY);

    Font font = AssetManager::Instance().GetFont(FontID::DEFAULT, 100);
    const char* text = "INFISWEEPER";
    Vector2 text_size = MeasureTextEx(font, text, 100, 1);

    DrawTextPro(
        AssetManager::Instance().GetFont(FontID::DEFAULT, 100),
        "INFISWEEPER",
        {screen_width / 2.0f, screen_height / 2.0f - 100.0f},
        {text_size.x / 2.0f, text_size.y /2.0f},
        0.0f,
        100,
        1,
        BLACK
    );
    if(GuiButton(new_game_button, "New game")) PingObservers(MainMenuButtons::NEW_GAME);
    if(GuiButton(load_game_button, "Load game")) PingObservers(MainMenuButtons::LOAD_GAME);

    EndDrawing();
}

void MainMenuView::Subscribe(IMainMenuViewObserver* observer)
{
    m_Observers.push_back(observer);
}

void MainMenuView::PingObservers(MainMenuButtons button)
{
    for(auto& observer : m_Observers)
    {
        observer->OnMainMenuButtonClick(button);
    }
}