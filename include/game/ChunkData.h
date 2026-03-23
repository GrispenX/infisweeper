#ifndef INCLUDE_GAME_CHUNKDATA_H_
#define INCLUDE_GAME_CHUNKDATA_H_

#include "game/ICell.h"
#include "GeometryConcept.h"
#include <vector>

template<Geometry T>
struct CellData
{
    T::CellPosition pos;
    CellType type;
    CellState state;
    size_t mines_around;
};

template<Geometry T>
struct ChunkData
{
    std::vector<CellData<T>> cells;
};

#endif // INCLUDE_GAME_CHUNKDATA_H_