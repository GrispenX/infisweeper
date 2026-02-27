#ifndef INCLUDE_GAME_ICHUNKBUILDER_H_
#define INCLUDE_GAME_ICHUNKBUILDER_H_

#include "game/ICell.h"
#include "game/IChunk.h"
#include "game/MinefieldPositions.h"
#include <memory>

class IChunkBuilder
{
public:
    ~IChunkBuilder() = default;

    virtual void Reset() = 0;
    virtual void AddCell(const CellInChunkPosition& cell_pos, std::unique_ptr<ICell> cell) = 0;
    virtual std::unique_ptr<IChunk> GetResult() = 0;
};

#endif // INCLUDE_GAME_ICHUNKBUILDER_H_