#ifndef INCLUDE_UI_IGAMEVIEWOBSERVER_H_
#define INCLUDE_UI_IGAMEVIEWOBSERVER_H_

#include "UI/GameScreen/PlainPosition.h"

class IGameViewObserver
{
public:
    virtual ~IGameViewObserver() = default;

    virtual void OnSweep(const PlainPosition& pos) = 0;
    virtual void OnFlag(const PlainPosition& pos) = 0;
    virtual void OnBackButton() = 0;
};

#endif // INCLUDE_UI_IGAMEVIEWOBSERVER_H_