#ifndef INCLUDE_GAME_CHUNK_H_
#define INCLUDE_GAME_CHUNK_H_

#include "IChunk.h"
#include "ICell.h"
#include <memory>
#include <unordered_map>

template<Geometry T>
class Chunk : public IChunk<T>
{
public:
    using CellPosition = typename T::CellPosition;

    Chunk(std::unordered_map<CellPosition, std::unique_ptr<ICell>> cells) :
        m_Cells(std::move(cells)) {}

    SweepResult Sweep(const CellPosition& pos) override
    {
        return m_Cells[pos]->Sweep();
    }
    FlagResult Flag(const CellPosition& pos) override
    {
        return m_Cells[pos]->Flag();
    }
    ICell* GetCell(const CellPosition& pos) override
    {
        return m_Cells[pos].get();
    }
    size_t GetSize() const override
    {
        return m_Cells.size();
    }

private:
    std::unordered_map<CellPosition, std::unique_ptr<ICell>> m_Cells;
};

#endif // INCLUDE_GAME_CHUNK_H_