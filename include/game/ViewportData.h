#ifndef INCLUDE_GAME_VIEWPORTDATA_H_
#define INCLUDE_GAME_VIEWPORTDATA_H_

#include "game/PlainPosition.h"
#include "game/Cell.h"
#include <vector>

enum class CellShape
{
    SQUARE,
    EQUILATERAL_TRIANGLE
};

struct CellData
{
    CellShape shape;
    PlainPosition center;
    double scale;
    double rotation;
    CellType type;
    CellState state;
    size_t mines_around;
};

struct ViewportData
{
    std::vector<std::pair<PlainPosition, PlainPosition>> chunk_boundaries;
    std::vector<CellData> cell_data;
};

#endif // INCLUDE_GAME_VIEWPORTDATA_H_