#ifndef INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEWOBSERVER_H_
#define INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEWOBSERVER_H_

#include <string>

class INewGameViewObserver
{
public:
    virtual ~INewGameViewObserver() = default;

    virtual void OnBackButton() = 0;
    virtual void OnCreateGameButton(std::string save_name, int geometry_id) = 0;
};

#endif // INCLUDE_UI_NEWGAMESCREEN_INEWGAMEVIEWOBSERVER_H_