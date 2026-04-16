#ifndef INCLUDE_UI_IGAMEVIEW_H_
#define INCLUDE_UI_IGAMEVIEW_H_

#include "UI/GameScreen/ViewData.h"
#include "UI/GameScreen/IGameViewObserver.h"

class IGameView
{
public:
    virtual ~IGameView() = default;

    virtual std::pair<PlainPosition, PlainPosition> GetVisibleMinefieldCorners() = 0;
    virtual void Update() = 0;
    virtual void Draw(const std::vector<ChunkViewData>& data) = 0;
    virtual void Subscribe(IGameViewObserver* observer) = 0;
};

#endif // INCLUDE_UI_IGAMEVIEW_H_