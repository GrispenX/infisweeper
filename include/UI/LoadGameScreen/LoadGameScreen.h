#ifndef INCLUDE_UI_LOADGAMESCREEN_H_
#define INCLUDE_UI_LOADGAMESCREEN_H_

#include "UI/IScreen.h"

class LoadGameScreen : public IScreen
{
public:
    std::unique_ptr<IScreen> Update() override;
};

#endif // INCLUDE_UI_LOADGAMESCREEN_H_