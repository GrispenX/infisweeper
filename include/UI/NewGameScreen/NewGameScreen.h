#ifndef INCLUDE_UI_NEWGAMESCREEN_H_
#define INCLUDE_UI_NEWGAMESCREEN_H_

#include "UI/IScreen.h"

class NewGameScreen : public IScreen
{
public:
    std::unique_ptr<IScreen> Update() override;
};

#endif // INCLUDE_UI_NEWGAMESCREEN_H_