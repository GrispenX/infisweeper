#include "UI/MainMenuScreen/MainMenuScreen.h"

#include "UI/GameScreen/GameScreen.h"
#include "UI/GameScreen/GameView.h"
#include "game/GameModel.h"

MainMenuScreen::MainMenuScreen(std::unique_ptr<IMainMenuView> view) :
    m_View(std::move(view))
{
    m_View->Subscribe(this);
}

std::unique_ptr<IScreen> MainMenuScreen::Update()
{

}

void MainMenuScreen::OnMainMenuButtonClick(MainMenuButtons button)
{
    m_NextScreen = std::make_unique<GameScreen>(
        std::make_unique<GameView>()
    )
}