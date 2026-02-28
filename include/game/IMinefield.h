#ifndef INCLUDE_GAME_IMINEFIELD_H_
#define INCLUDE_GAME_IMINEFIELD_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"
#include <memory>

class IMinefield
{
public:
    ~IMinefield() = default;

    virtual SweepResult Sweep(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos) = 0;
    virtual FlagResult Flag(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos) = 0;
    virtual const IChunk* GetChunk(const ChunkPosition& chunk_pos) const = 0;
};

#endif // INCLUDE_GAME_IMINEFIELD_H_