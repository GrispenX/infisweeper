#include "UI/LoadGameScreen/LoadGameScreen.h"
#include "game/ChunkFileStorage/SaveFileInspector.h"

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

LoadGameScreen::LoadGameScreen(std::unique_ptr<ILoadGameView> view) :
    m_View(std::move(view))
{
    m_View->Subscribe(this);

    SaveFileInspector file_inspector;
    auto files = file_inspector.GetValidFiles(std::filesystem::current_path());
    m_View->SetSaveFiles(files);
}

std::unique_ptr<IScreen> LoadGameScreen::Update()
{
    m_View->Update();
    return std::move(m_NextScreen);
}

void LoadGameScreen::OnBackButton()
{
    m_NextScreen = std::make_unique<MainMenuScreen>(std::make_unique<MainMenuView>());
}

void LoadGameScreen::OnLoadButton(std::filesystem::path selected_file)
{
    SaveFileInspector inspector;
    Header header = inspector.ReadHeader(selected_file);
    switch(header.geometry_id)
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
                        selected_file,
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
                        selected_file,
                        std::make_unique<ChunkFactory<TriHexGeometry>>()
                    )
                )
            )
        );
        break;
    }
}