#ifndef INCLUDE_UI_NEWGAMESCREEN_H_
#define INCLUDE_UI_NEWGAMESCREEN_H_

#include "UI/IScreen.h"
#include "UI/NewGameScreen/INewGameView.h"
#include "UI/NewGameScreen/INewGameViewObserver.h"

class NewGameScreen : public IScreen, public INewGameViewObserver
{
public:
    NewGameScreen(std::unique_ptr<INewGameView> view);
    std::unique_ptr<IScreen> Update() override;
    void OnBackButton() override;
    void OnCreateGameButton(std::string save_name, int geometry_id) override;

private:
    std::unique_ptr<INewGameView> m_View;
    std::unique_ptr<IScreen> m_NextScreen;
};

#endif // INCLUDE_UI_NEWGAMESCREEN_H_