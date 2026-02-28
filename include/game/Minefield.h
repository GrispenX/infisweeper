#ifndef INCLUDE_GAME_MINEFIELD_H_
#define INCLUDE_GAME_MINEFIELD_H_

#include "game/MinefieldPositions.h"
#include "game/IMinefield.h"
#include <memory>
#include <unordered_map>

class Minefield : public IMinefield
{
public:
    SweepResult Sweep(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos) override;
    FlagResult Flag(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos) override;
    const IChunk* GetChunk(const ChunkPosition& chunk_pos) const override;

private:
    std::unordered_map<ChunkPosition, std::unique_ptr<IChunk>, ChunkPositionHash> m_LoadedChunks;
};

#endif // INCLUDE_GAME_MINEFIELD_H_