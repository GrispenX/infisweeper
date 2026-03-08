#ifndef INCLUDE_GAME_IMINESWEEPERMODEL_H_
#define INCLUDE_GAME_IMINESWEEPERMODEL_H_

#include "game/PlainPosition.h"
#include "game/ICell.h"
#include "game/ViewportData.h"

class IMinesweeperModel
{
public:
    ~IMinesweeperModel() = default;

    virtual SweepResult Sweep(const PlainPosition& pos) = 0;
    virtual FlagResult Flag(const PlainPosition& pos) = 0;
    virtual ViewportData GetCellsInRectangle(const PlainPosition& pos1, const PlainPosition& pos2) = 0;
};

#endif // INCLUDE_GAME_IMINESWEEPERMODEL_H_