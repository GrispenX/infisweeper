#ifndef INCLUDE_GAME_ICELL_H_
#define INCLUDE_GAME_ICELL_H_

enum class SweepResult
{
    OK,
    BLOWN,
    ALREADY_OPENED,
    ALREADY_FLAGGED,
    INVALID_CELL_POSITION,
    INACCESSIBLE
};

enum class FlagResult
{
    OK,
    ALREADY_OPENED,
    INVALID_CELL_POSITION,
    INACCESSIBLE
};

enum class CellState
{
    OPENED,
    CLOSED,
    FLAGGED
};

enum class CellType
{
    MINE,
    SAFE
};

class ICell
{
public:
    ~ICell() = default;

    virtual SweepResult Sweep() = 0;
    virtual FlagResult Flag() = 0;
    virtual CellState GetState() const = 0;
    virtual CellType GetType() const = 0;
    virtual void SetState(CellState state) = 0;
    virtual void SetType(CellType type) = 0;
};

#endif // INCLUDE_GAME_ICELL_H_