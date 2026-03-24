#ifndef INCLUDE_GAME_CHUNKGENERATOR_H_
#define INCLUDE_GAME_CHUNKGENERATOR_H_

#include "game/IChunkGenerator.h"
#include "game/IChunkFactory.h"
#include "game/Cell.h"
#include <random>

template<Geometry T>
class ChunkGenerator : public IChunkGenerator<T>
{
public:
    using CellPosition = typename T::CellPosition;
    using ChunkPosition = typename T::ChunkPosition;

    ChunkGenerator(std::unique_ptr<IChunkFactory<T>> chunk_factory, double mine_probability) :
        m_ChunkFactory(std::move(chunk_factory)),
        m_MineProbability(mine_probability) {}

    std::unique_ptr<IChunk<T>> GenerateChunk(const ChunkPosition& pos) override
    {
        std::vector<std::pair<CellPosition, std::unique_ptr<ICell>>> cells;
        for(const auto& cell_pos : T::GetAllCellPositions(pos))
        {
            double rand = (double)m_RNG() / m_RNG.max();
            CellType type = rand <= m_MineProbability ? CellType::MINE : CellType::SAFE;
            cells.push_back(std::make_pair(cell_pos, std::make_unique<Cell>(type, CellState::CLOSED)));
        }
        return m_ChunkFactory->CreateChunk(std::move(cells));
    }

private:
    std::mt19937 m_RNG;
    double m_MineProbability;
    std::unique_ptr<IChunkFactory<T>> m_ChunkFactory;
};

#endif // INCLUDE_GAME_CHUNKGENERATOR_H_