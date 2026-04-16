#include <iostream>
#include <unordered_map>
#include "game/GameModel.h"
#include "game/ChunkGenerator.h"
#include "game/Geometries.h"
#include "game/ChunkFactory.h"
#include "game/ChunkFileStorage.h"
#include "game/ChunkStorageProxy.h"

#include "UI/AssetManager.h"
#include "UI/GameScreen/GameView.h"
#include "UI/GameScreen/GameScreen.h"

#include <raylib.h>

int main()
{
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(75);

    using G = TriHexGeometry;

    std::unordered_map<TextureID, std::filesystem::path> textures {
        {TextureID::SQUARE_CELL, "/home/grispenx/projects/infisweeper/assets/Square.png"},
        {TextureID::EQUILATERAL_TRIANGLE, "/home/grispenx/projects/infisweeper/assets/Triangle.png"},
        {TextureID::FLAG, "/home/grispenx/projects/infisweeper/assets/flag.png"}
    };

    std::unordered_map<FontID, std::filesystem::path> fonts {
        {FontID::DEFAULT, "/home/grispenx/projects/infisweeper/assets/SpaceMono-Bold.ttf"}
    };



    std::unique_ptr<IChunkGenerator<G>> generator = std::make_unique<ChunkGenerator<G>>(std::make_unique<ChunkFactory<G>>(), 0.15);
    std::unique_ptr<IChunkStorage<G>> storage = std::make_unique<ChunkStorageProxy<G>>(
        std::make_unique<ChunkFileStorage<G>>(
            "save_file",
            std::make_unique<ChunkFactory<G>>()
        )
    );
    
    std::unique_ptr<IGameModel<G>> model = std::make_unique<GameModel<G>>(std::move(generator), std::move(storage));

    for(auto [id, path] : textures)
    {
        AssetManager::Instance().SetTexturePath(id, path);
    }

    for(auto [id, path] : fonts)
    {
        AssetManager::Instance().SetFontPath(id, path);
    }

    std::unique_ptr<IGameView> view = std::make_unique<GameView>();
    GameScreen<G> screen(std::move(view), std::move(model));



    while(!WindowShouldClose())
    {
        screen.Update();
    }
}
