#ifndef INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_
#define INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_

#include "UI/MainMenuScreen/IMainMenuView.h"
#include <vector>

#include <raylib.h>
#include "raygui.h"

class MainMenuView : public IMainMenuView
{
public:
    void Update() override;
    void Subscribe(IMainMenuViewObserver* observer) override;

private:
    std::vector<IMainMenuViewObserver*> m_Observers;

    void ResolveUILayout();

    Rectangle m_LogoBounds;
    Rectangle m_LoadButtonBounds;
    Rectangle m_NewButtonBounds;
};

#endif // INCLUDE_UI_MAINMENUSCREEN_MAINMENUVIEW_H_