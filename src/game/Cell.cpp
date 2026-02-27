#include "game/Cell.h"

Cell::Cell(CellType type, CellState state) :
    m_Type(type),
    m_State(state)
{

}

SweepResult Cell::Sweep()
{
    if(m_State == CellState::OPENED)
    {
        return SweepResult::ALREADY_OPENED;
    }

    if(m_State == CellState::FLAGGED)
    {
        return SweepResult::ALREADY_FLAGGED;
    }

    m_State = CellState::OPENED;

    return m_Type == CellType::MINE ? SweepResult::BLOWN : SweepResult::OK;
}

FlagResult Cell::Flag()
{
    if(m_State == CellState::OPENED)
    {
        return FlagResult::ALREADY_OPENED;
    }

    m_State = m_State == CellState::CLOSED ? CellState::FLAGGED : CellState::CLOSED;

    return FlagResult::OK;
}

CellState Cell::GetState() const
{
    return m_State;
}

CellType Cell::GetType() const
{
    return m_Type;
}
