#ifndef INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEW_H_
#define INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEW_H_

#include "UI/NewGameScreen/INewGameViewObserver.h"
#include "game/ChunkFileStorage/Header.h"
#include <unordered_map>
#include <filesystem>

class INewGameView
{
public:
    virtual ~INewGameView() = default;

    virtual void Update() = 0;
    virtual void Subscribe(INewGameViewObserver* observer) = 0;
};

#endif // INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEW_H_