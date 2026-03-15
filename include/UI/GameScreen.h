#ifndef INCLUDE_GAMESCREEN_H_
#define INCLUDE_GAMESCREEN_H_

#include "UI/IScreen.h"
#include "UI/IGameView.h"
#include "UI/IGameViewObserver.h"
#include "game/IGameModel.h"

class GameScreen : public IScreen, public IGameViewObserver
{
public:
    GameScreen(std::unique_ptr<IGameView> view, std::unique_ptr<IGameModel> model);

    std::unique_ptr<IScreen> Update() override;

    void OnMinefieldLeftClick(const PlainPosition& pos) override;
    void OnMinefieldRightClick(const PlainPosition& pos) override;

private:
    std::unique_ptr<IGameView> m_View;
    std::unique_ptr<IGameModel> m_Model;
};

#endif // INCLUDE_GAMESCREEN_H_