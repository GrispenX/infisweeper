#include "UI/MainMenuScreen/MainMenuScreen.h"

#include "UI/NewGameScreen/NewGameScreen.h"
#include "UI/NewGameScreen/NewGameView.h"

#include "UI/LoadGameScreen/LoadGameScreen.h"
#include "UI/LoadGameScreen/LoadGameView.h"

MainMenuScreen::MainMenuScreen(std::unique_ptr<IMainMenuView> view) :
    m_View(std::move(view))
{
    m_View->Subscribe(this);
}

std::unique_ptr<IScreen> MainMenuScreen::Update()
{
    m_View->Update();
    return std::move(m_NextScreen);
}

void MainMenuScreen::OnNewGameButton()
{
    m_NextScreen = std::make_unique<NewGameScreen>(std::make_unique<NewGameView>());
}

void MainMenuScreen::OnLoadGameButton()
{
    m_NextScreen = std::make_unique<LoadGameScreen>(std::make_unique<LoadGameView>());
}