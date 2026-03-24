#ifndef INCLUDE_UI_IGAMEVIEWOBSERVER_H_
#define INCLUDE_UI_IGAMEVIEWOBSERVER_H_

#include "game/PlainPosition.h"

class IGameViewObserver
{
public:
    ~IGameViewObserver() = default;

    virtual void OnMinefieldLeftClick(const PlainPosition& pos) = 0;
    virtual void OnMinefieldRightClick(const PlainPosition& pos) = 0;
};

#endif // INCLUDE_UI_IGAMEVIEWOBSERVER_H_