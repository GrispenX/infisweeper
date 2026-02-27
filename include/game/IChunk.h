#ifndef INCLUDE_GAME_ICHUNK_H_
#define INCLUDE_GAME_ICHUNK_H_

#include "ICell.h"
#include "MinefieldPositions.h"

class IChunk
{
public:
    ~IChunk() = default;

    virtual SweepResult Sweep(const CellInChunkPosition& cell_pos) = 0;
    virtual FlagResult Flag(const CellInChunkPosition& cell_pos) = 0;
    virtual const ICell* GetCell(const CellInChunkPosition& cell_pos) const = 0;
};

#endif // INCLUDE_GAME_ICHUNK_H_