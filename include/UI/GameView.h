#ifndef INCLUDE_GAMEVIEW_H_
#define INCLUDE_GAMEVIEW_H_

#include "UI/IGameView.h"
#include <vector>
#include <raylib.h>

class GameView : public IGameView
{
public:
    GameView(Texture2D cell); //TEMP

    std::pair<PlainPosition, PlainPosition> GetVisibleMinefieldCorners() override;
    void Update() override;
    void Draw(const std::vector<ChunkViewData>& data) override;
    void Subscribe(IGameViewObserver* observer) override;

private:
    std::vector<IGameViewObserver*> m_Observers;
    PlainPosition m_Position;
    double m_Zoom;

    Texture2D m_CellTexture; // TEMP

    Vector2 PlainToScreen(const PlainPosition& pos);
    PlainPosition ScreenToPlain(const Vector2& pos);
};

#endif // INCLUDE_GAMEVIEW_H_