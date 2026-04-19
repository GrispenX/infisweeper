#include "UI/NewGameScreen/NewGameScreen.h"

#include "UI/MainMenuScreen/MainMenuScreen.h"
#include "UI/MainMenuScreen/MainMenuView.h"

#include "UI/GameScreen/GameScreen.h"
#include "UI/GameScreen/GameView.h"
#include "game/GameModel.h"
#include "game/ChunkFileStorage/ChunkFileStorage.h"
#include "game/ChunkStorageProxy.h"
#include "game/ChunkGenerator.h"
#include "game/ChunkFactory.h"
#include "game/Geometries.h"

NewGameScreen::NewGameScreen(std::unique_ptr<INewGameView> view) :
    m_View(std::move(view))
{
    m_View->Subscribe(this);
}

std::unique_ptr<IScreen> NewGameScreen::Update()
{
    m_View->Update();
    return std::move(m_NextScreen);
}

void NewGameScreen::OnBackButton()
{
    m_NextScreen = std::make_unique<MainMenuScreen>(std::make_unique<MainMenuView>());
}

void NewGameScreen::OnCreateGameButton(std::string save_name, int geometry_id)
{
    if(std::filesystem::exists(save_name)) return;

    switch(geometry_id)
    {
    case 1:
        m_NextScreen = std::make_unique<GameScreen<SquareGeometry>>(
            std::make_unique<GameView>(),
            std::make_unique<GameModel<SquareGeometry>>(
                std::make_unique<ChunkGenerator<SquareGeometry>>(
                    std::make_unique<ChunkFactory<SquareGeometry>>(),
                    0.2
                ),
                std::make_unique<ChunkStorageProxy<SquareGeometry>>(
                    std::make_unique<ChunkFileStorage<SquareGeometry>>(
                        save_name,
                        std::make_unique<ChunkFactory<SquareGeometry>>()
                    )
                )
            )
        );
        break;
    case 2:
        m_NextScreen = std::make_unique<GameScreen<TriHexGeometry>>(
            std::make_unique<GameView>(),
            std::make_unique<GameModel<TriHexGeometry>>(
                std::make_unique<ChunkGenerator<TriHexGeometry>>(
                    std::make_unique<ChunkFactory<TriHexGeometry>>(),
                    0.2
                ),
                std::make_unique<ChunkStorageProxy<TriHexGeometry>>(
                    std::make_unique<ChunkFileStorage<TriHexGeometry>>(
                        save_name,
                        std::make_unique<ChunkFactory<TriHexGeometry>>()
                    )
                )
            )
        );
        break;
    }
}