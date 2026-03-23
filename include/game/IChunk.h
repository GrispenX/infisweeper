#ifndef INCLUDE_GAME_ICHUNK_H_
#define INCLUDE_GAME_ICHUNK_H_

#include <cstddef>
#include "ICell.h"
#include "game/GeometryConcept.h"

template<Geometry T>
class IChunk
{
public:
    using CellPosition = typename T::CellPosition;
    virtual ~IChunk() = default;

    virtual SweepResult Sweep(const CellPosition& pos) = 0;
    virtual FlagResult Flag(const CellPosition& pos) = 0;
    virtual ICell* GetCell(const CellPosition& pos) = 0;
    virtual size_t GetSize() const = 0;
};

#endif // INCLUDE_GAME_ICHUNK_H_