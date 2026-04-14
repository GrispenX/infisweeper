#ifndef INCLUDE_UI_VIEWDATA_H_
#define INCLUDE_UI_VIEWDATA_H_

#include "UI/PlainPosition.h"
#include "game/ICell.h"
#include <vector>

enum class CellShape
{
    SQUARE,
    EQUILATERAL_TRIANGLE
};

struct CellViewData
{
    PlainPosition center_pos;
    double size;
    double rotation;
    CellShape shape;

    CellType type;
    CellState state;
    size_t mines_around;
};

struct ChunkViewData
{
    std::vector<CellViewData> cells;
    std::vector<std::pair<PlainPosition, PlainPosition>> boundaries;
};

#endif // INCLUDE_UI_VIEWDATA_H_