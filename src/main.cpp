#define RAYGUI_IMPLEMENTATION

#include "UI/MainMenuScreen/MainMenuView.h"
#include "UI/MainMenuScreen/MainMenuScreen.h"
#include "Application.h"

int main()
{
    std::unique_ptr<IScreen> screen = std::make_unique<MainMenuScreen>(
        std::make_unique<MainMenuView>()
    );

    Application application(std::move(screen));
    application.Run();
}
