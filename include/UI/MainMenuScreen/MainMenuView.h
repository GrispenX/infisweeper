#ifndef INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_
#define INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_

#include "UI/MainMenuScreen/IMainMenuView.h"
#include <vector>

class MainMenuView : public IMainMenuView
{
public:
    void Update() override;
    void Subscribe(IMainMenuViewObserver* observer) override;

private:
    std::vector<IMainMenuViewObserver*> m_Observers;
    void PingObservers(MainMenuButtons button);
};

#endif // INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_