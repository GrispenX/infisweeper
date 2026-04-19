#ifndef INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_
#define INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_

class IMainMenuViewObserver
{
public:
    virtual ~IMainMenuViewObserver() = default;

    virtual void OnNewGameButton() = 0;
    virtual void OnLoadGameButton() = 0;
};

#endif // INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_