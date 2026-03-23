#include "game/Chunk.h"
#include <game/Geometries.h>

template<>
size_t Chunk<SquareGeometry>::CellPosToIndex(const SquareGeometry::CellPosition& pos)
{
    return pos.row * 10 + pos.col;
}