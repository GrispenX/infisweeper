#ifndef INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_
#define INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_

enum class MainMenuButtons
{
    NEW_GAME,
    LOAD_GAME
};

class IMainMenuViewObserver
{
public:
    virtual ~IMainMenuViewObserver() = default;

    virtual void OnMainMenuButtonClick(MainMenuButtons button) = 0;
};

#endif // INCLUDE_UI_IMAINMENUVIEWOBSERVER_H_