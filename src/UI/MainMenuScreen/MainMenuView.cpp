#include "UI/MainMenuScreen/MainMenuView.h"
#include <raylib.h>
#include "raygui.h"

void MainMenuView::Update()
{
    const float screen_width = (float)GetScreenWidth();
    const float screen_height = (float)GetScreenHeight();

    Rectangle new_game_button {
        .x = screen_width / 2.0 - 100.0f,
        .y = screen_height / 2.0 - 40.0f,
        .width = 200.0f,
        .height = 40.0f
    };

    Rectangle load_game_button {
        .x = screen_width / 2.0 - 100.0f,
        .y = screen_height / 2.0 + 40.0f,
        .width = 200.0f,
        .height = 40.0f
    };

    BeginDrawing();
    ClearBackground(GRAY);

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