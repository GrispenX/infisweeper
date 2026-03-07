#ifndef INCLUDE_GAME_ICHUNK_H_
#define INCLUDE_GAME_ICHUNK_H_

#include <cstddef>
#include "ICell.h"

class IChunk
{
public:
    ~IChunk() = default;

    virtual SweepResult Sweep(size_t index) = 0;
    virtual FlagResult Flag(size_t index) = 0;
    virtual const ICell* GetCell(size_t index) const = 0;
    virtual size_t GetSize() const = 0;
};

#endif // INCLUDE_GAME_ICHUNK_H_