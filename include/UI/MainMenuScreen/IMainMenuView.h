#ifndef INCLUDE_UI_IMAINMENUVIEW_H_
#define INCLUDE_UI_IMAINMENUVIEW_H_

#include "UI/MainMenuScreen/IMainMenuViewObserver.h"

class IMainMenuView
{
public:
    virtual ~IMainMenuView() = default;

    virtual void Update() = 0;
    virtual void Subscribe(IMainMenuViewObserver* observer) = 0;
};

#endif // INCLUDE_UI_IMAINMENUVIEW_H_