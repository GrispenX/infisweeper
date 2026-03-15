#ifndef INCLUDE_UI_IGAMEVIEW_H_
#define INCLUDE_UI_IGAMEVIEW_H_

#include "game/ViewportData.h"
#include "UI/IGameViewObserver.h"

class IGameView
{
public:
    ~IGameView() = default;

    virtual std::pair<PlainPosition, PlainPosition> GetVisibleMinefieldCorners() = 0;
    virtual void Update() = 0;
    virtual void Draw(const ViewportData& data) = 0;
    virtual void Subscribe(IGameViewObserver* observer) = 0;
};

#endif // INCLUDE_UI_IGAMEVIEW_H_