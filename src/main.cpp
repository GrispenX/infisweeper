#include <iostream>
#include <unordered_map>
#include "game/GameModel.h"
#include "game/ChunkGenerator.h"
#include "game/Geometries.h"
#include "game/ChunkFactory.h"

#include "UI/AssetManager.h"
#include "UI/GameView.h"
#include "UI/GameScreen.h"

#include <raylib.h>

template<>
struct std::hash<SquareGeometry::ChunkPosition>
{
    size_t operator()(const SquareGeometry::ChunkPosition& pos) const
    {
        size_t seed = 0;
        HashCombine(seed, pos.row);
        HashCombine(seed, pos.col);
        return seed;
    }
};

template<Geometry T>
class ChunkStorage : public IChunkStorage<T>
{
public:
    using ChunkPosition = typename T::ChunkPosition;

    std::shared_ptr<IChunk<T>> GetChunk(const ChunkPosition& chunk_pos) override
    {
        if(m_Chunks.contains(chunk_pos))
        {
            return m_Chunks.at(chunk_pos);
        }
        return nullptr;
    }

    std::vector<std::pair<ChunkPosition, std::shared_ptr<IChunk<T>>>> GetAllChunks() override
    {
        std::vector<std::pair<ChunkPosition, std::shared_ptr<IChunk<T>>>> chunks;
        for(const auto& [pos, chunk] : m_Chunks)
        {
            chunks.push_back(std::make_pair(pos, chunk));
        }
        return chunks;
    }

    void PushChunk(const ChunkPosition& chunk_pos, std::shared_ptr<IChunk<T>> chunk) override
    {
        m_Chunks[chunk_pos] = chunk;
    }

private:
    std::unordered_map<ChunkPosition, std::shared_ptr<IChunk<T>>> m_Chunks;
};

int main()
{
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(75);


    std::unordered_map<TextureID, std::filesystem::path> textures {
        {TextureID::SQUARE_CELL, "/home/grispenx/projects/infisweeper/assets/opened_cell.png"}
    };

    std::unordered_map<FontID, std::filesystem::path> fonts {
        {FontID::DEFAULT, "/home/grispenx/projects/infisweeper/assets/SpaceMono-Bold.ttf"}
    };



    std::unique_ptr<IChunkGenerator<SquareGeometry>> generator = std::make_unique<ChunkGenerator<SquareGeometry>>(std::make_unique<ChunkFactory<SquareGeometry>>(), 0.2);
    std::unique_ptr<IChunkStorage<SquareGeometry>> storage = std::make_unique<ChunkStorage<SquareGeometry>>();
    std::unique_ptr<IGameModel<SquareGeometry>> model = std::make_unique<GameModel<SquareGeometry>>(std::move(generator), std::move(storage));

    std::shared_ptr<IAssetManager> assets = std::make_unique<AssetManager>(textures, fonts);
    std::unique_ptr<IGameView> view = std::make_unique<GameView>(assets);
    GameScreen<SquareGeometry> screen(std::move(view), std::move(model));



    while(!WindowShouldClose())
    {
        screen.Update();
    }
}
