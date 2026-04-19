#ifndef INCLUDE_UI_LOADGAMESCREEN_LOADGAMEVIEW_H_
#define INCLUDE_UI_LOADGAMESCREEN_LOADGAMEVIEW_H_

#include "UI/LoadGameScreen/ILoadGameView.h"
#include <vector>

#include <raylib.h>
#include "raygui.h"

class LoadGameView : public ILoadGameView
{
public:
    void Update() override;
    void Subscribe(ILoadGameViewObserver* observer) override;
    void SetSaveFiles(std::unordered_map<std::filesystem::path, Header>& files) override;

private:
    std::vector<ILoadGameViewObserver*> m_Observers;
    std::unordered_map<std::filesystem::path, Header> m_SaveFiles;

    void ResolveUILayout();

    Rectangle m_FileSelectorBounds {0, 0, 500, 0};
    Rectangle m_FileSelectorContent {0, 0, 485, 0};
    Rectangle m_FileSelectorView;
    Vector2 m_FileSelectorScroll;
    int m_FileSelectorEntrySize;
    std::filesystem::path m_SelectedPath;

    Rectangle m_ConfirmButtonBounds {0, 0, 200, 30};
    Rectangle m_BackButtonBounds {0, 0, 200, 30};
};

#endif // INCLUDE_UI_LOADGAMESCREEN_LOADGAMEVIEW_H_