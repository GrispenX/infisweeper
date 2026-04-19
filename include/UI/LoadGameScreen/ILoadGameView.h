#ifndef INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEW_H_
#define INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEW_H_

#include "UI/LoadGameScreen/ILoadGameViewObserver.h"
#include "game/ChunkFileStorage/Header.h"
#include <filesystem>
#include <unordered_map>

class ILoadGameView
{
public:
    virtual ~ILoadGameView() = default;

    virtual void Update() = 0;
    virtual void Subscribe(ILoadGameViewObserver* observer) = 0;
    virtual void SetSaveFiles(std::unordered_map<std::filesystem::path, Header>& files) = 0;
};

#endif // INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEW_H_