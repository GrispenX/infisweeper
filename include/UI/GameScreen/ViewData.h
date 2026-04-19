#ifndef INCLUDE_UI_VIEWDATA_H_
#define INCLUDE_UI_VIEWDATA_H_

#include "UI/GameScreen/PlainPosition.h"
#include "game/ICell.h"
#include "UI/AssetManager.h"
#include <vector>

struct CellViewData
{
    PlainPosition center_pos;
    double size;
    double rotation;
    TextureID texture_id;

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