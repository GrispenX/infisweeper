#ifndef INCLUDE_GAME_CELL_H_
#define INCLUDE_GAME_CELL_H_

#include "ICell.h"

class Cell : public ICell
{
public:
    Cell(CellType type, CellState state);

    SweepResult Sweep() override;
    FlagResult Flag() override;
    CellState GetState() const override;
    CellType GetType() const override;
    void SetState(CellState state) override;
    void SetType(CellType type) override;

private:
    CellState m_State;
    CellType m_Type;
};

#endif // INCLUDE_GAME_CELL_H_