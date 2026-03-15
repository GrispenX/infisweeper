#include <iostream>
#include <unordered_map>
#include <map>
#include "game/GeometryConcept.h"
#include "game/Geometries.h"
#include "game/Chunk.h"
#include "game/Cell.h"
#include "game/IChunkGenerator.h"
#include "game/IChunkStorage.h"
#include "game/GameModel.h"
#include "game/PlainPosition.h"
#include "UI/GameScreen.h"
#include "UI/GameView.h"

class ChunkGenerator : public IChunkGenerator
{
public:
    std::shared_ptr<IChunk> GenerateChunk(size_t chunk_pos_hash, size_t cells_amount) override
    {
        std::vector<std::unique_ptr<ICell>> cells(cells_amount);
        for(size_t i = 0; i < cells_amount; i++)
        {
            cells[i] = std::make_unique<Cell>(CellType::MINE, CellState::CLOSED);
        }
        return std::make_shared<Chunk>(cells);
    }
};

template<Geometry TGeometry>
class ChunkStorage : public IChunkStorage<TGeometry>
{
public:
    std::shared_ptr<IChunk> GetChunk(const TGeometry::ChunkPosition& chunk_pos) override
    {
        if(m_Chunks.contains(chunk_pos))
        {
            return m_Chunks.at(chunk_pos);
        }
        return nullptr;
    }
    void PushChunk(const TGeometry::ChunkPosition& chunk_pos, std::shared_ptr<IChunk> chunk) override
    {
        m_Chunks[chunk_pos] = chunk;
    }

private:
    std::unordered_map<typename TGeometry::ChunkPosition, std::shared_ptr<IChunk>, typename TGeometry::ChunkPositionHasher> m_Chunks;
};

int main()
{
    InitWindow(1920, 1080, "Test");
    SetTargetFPS(75);
    Image img = LoadImage("/home/grispenx/Pictures/cell.png");
    Texture2D texture = LoadTextureFromImage(img);

    std::unique_ptr<IChunkGenerator> gen = std::make_unique<ChunkGenerator>();
    std::shared_ptr<IChunkStorage<SquareGeometry<10>>> storage = std::make_shared<ChunkStorage<SquareGeometry<10>>>();
    std::unique_ptr<IGameModel> model = std::make_unique<GameModel<SquareGeometry<10>>>(std::move(gen), storage);
    
    std::unique_ptr<IGameView> view = std::make_unique<GameView>(texture);

    GameScreen screen(std::move(view), std::move(model));

    while(!WindowShouldClose())
    {
        screen.Update();
    }

    UnloadTexture(texture);
    UnloadImage(img);
}