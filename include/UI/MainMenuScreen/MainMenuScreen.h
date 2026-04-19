#ifndef INCLUDE_UI_MAINMENUSCREEN_H_
#define INCLUDE_UI_MAINMENUSCREEN_H_

#include "UI/IScreen.h"
#include "UI/MainMenuScreen/IMainMenuView.h"

class MainMenuScreen : public IScreen, public IMainMenuViewObserver
{
public:
    MainMenuScreen(std::unique_ptr<IMainMenuView> view);

    std::unique_ptr<IScreen> Update() override;
    void OnNewGameButton() override;
    void OnLoadGameButton() override;

private:
    std::unique_ptr<IMainMenuView> m_View;
    std::unique_ptr<IScreen> m_NextScreen = nullptr;
};

#endif // INCLUDE_UI_MAINMENUSCREEN_H_