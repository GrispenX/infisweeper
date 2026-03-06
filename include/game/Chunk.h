#ifndef INCLUDE_GAME_CHUNK_H_
#define INCLUDE_GAME_CHUNK_H_

#include "IChunk.h"
#include "ICell.h"
#include <array>
#include <memory>

template<size_t TSize>
class Chunk : public IChunk
{
public:
    Chunk(std::array<std::unique_ptr<ICell>, TSize> cells) :
        m_Cells(cells) {}

    SweepResult Sweep(size_t index) override
    {
        return m_Cells[index]->Sweep();
    }
    FlagResult Flag(size_t index) override
    {
        return m_Cells[index]->Flag();
    }
    const ICell* GetCell(size_t index) const override
    {
        return m_Cells[index].get();
    }

private:
    std::array<std::unique_ptr<ICell>, TSize> m_Cells;
};

#endif // INCLUDE_GAME_CHUNK_H_