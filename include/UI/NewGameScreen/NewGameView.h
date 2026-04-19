#ifndef INCLUDE_UI_NEWGAMESCREEN_NEWGAMEVIEW_H_
#define INCLUDE_UI_NEWGAMESCREEN_NEWGAMEVIEW_H_

#include "UI/NewGameScreen/INewGameView.h"
#include <vector>

#include <raylib.h>
#include "raygui.h"

class NewGameView : public INewGameView
{
public:
    void Update() override;
    void Subscribe(INewGameViewObserver* observer) override;

private:
    std::vector<INewGameViewObserver*> m_Observers;

    void ResolveUILayout();

    Rectangle m_NameLabelBounds {0, 0, 100, 0};
    Rectangle m_NameTextBoxBounds {0, 0, 400, 0};
    char m_Name[20];
    bool m_NameTextBoxActive = false;
    bool m_ShowNameTextBoxError = false;

    Rectangle m_GeometryDropdownBounds {0, 0, 500, 0};
    int m_GeometryId;
    bool m_GeometryDropdownActive = false;
    bool m_ShowGeometryDropdownError = false;

    Rectangle m_ConfirmButtonBounds {0, 0, 200, 0};
    Rectangle m_BackButtonBounds {0, 0, 200, 0};
};

#endif // INCLUDE_UI_NEWGAMESCREEN_NEWGAMEVIEW_H_