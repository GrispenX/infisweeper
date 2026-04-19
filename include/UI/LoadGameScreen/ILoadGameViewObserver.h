#ifndef INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEWOBSERVER_H_
#define INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEWOBSERVER_H_

#include <filesystem>

class ILoadGameViewObserver
{
public:
    virtual ~ILoadGameViewObserver() = default;

    virtual void OnBackButton() = 0;
    virtual void OnLoadButton(std::filesystem::path selected_file) = 0;
};

#endif // INCLUDE_UI_LOADGAMESCREEN_ILOADGAMEVIEWOBSERVER_H_