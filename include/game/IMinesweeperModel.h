#ifndef INCLUDE_GAME_IMINESWEEPERMODEL_H_
#define INCLUDE_GAME_IMINESWEEPERMODEL_H_

#include "game/PlainPosition.h"
#include "game/ICell.h"

class IMinesweeperModel
{
public:
    ~IMinesweeperModel() = default;

    virtual SweepResult Sweep(const PlainPosition& pos) = 0;
    virtual FlagResult Flag(const PlainPosition& pos) = 0;
};

#endif // INCLUDE_GAME_IMINESWEEPERMODEL_H_