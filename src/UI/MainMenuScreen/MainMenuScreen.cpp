#include "UI/MainMenuScreen/MainMenuScreen.h"

#include "UI/GameScreen/GameScreen.h"
#include "UI/GameScreen/GameView.h"
#include "game/GameModel.h"
#include "game/ChunkGenerator.h"
#include "game/ChunkFactory.h"
#include "game/ChunkStorageProxy.h"
#include "game/ChunkFileStorage.h"
#include "game/Geometries.h"

MainMenuScreen::MainMenuScreen(std::unique_ptr<IMainMenuView> view) :
    m_View(std::move(view))
{
    m_View->Subscribe(this);
}

std::unique_ptr<IScreen> MainMenuScreen::Update()
{
    m_View->Update();
    return std::move(m_NextScreen);
}

void MainMenuScreen::OnMainMenuButtonClick(MainMenuButtons button)
{
    using G = SquareGeometry;

    m_NextScreen = std::make_unique<GameScreen<G>>(
        std::make_unique<GameView>(),
        std::make_unique<GameModel<G>>(
            std::make_unique<ChunkGenerator<G>>(
                std::make_unique<ChunkFactory<G>>(),
                0.2
            ),
            std::make_unique<ChunkStorageProxy<G>>(
                std::make_unique<ChunkFileStorage<G>>(
                    "save_file",
                    std::make_unique<ChunkFactory<G>>()
                )
            )
        )
    );
}