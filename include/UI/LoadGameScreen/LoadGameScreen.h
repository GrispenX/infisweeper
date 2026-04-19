#ifndef INCLUDE_UI_LOADGAMESCREEN_H_
#define INCLUDE_UI_LOADGAMESCREEN_H_

#include "UI/IScreen.h"
#include "UI/LoadGameScreen/ILoadGameView.h"
#include "UI/LoadGameScreen/ILoadGameViewObserver.h"

class LoadGameScreen : public IScreen, public ILoadGameViewObserver
{
public:
    LoadGameScreen(std::unique_ptr<ILoadGameView> view);

    std::unique_ptr<IScreen> Update() override;

    void OnBackButton() override;
    void OnLoadButton(std::filesystem::path selected_file) override;

private:
    std::unique_ptr<ILoadGameView> m_View;
    std::unique_ptr<IScreen> m_NextScreen;
};

#endif // INCLUDE_UI_LOADGAMESCREEN_H_