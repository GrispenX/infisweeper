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
        m_Cells(cells.size())
    {
        for(auto& [pos, cell] : cells)
        {
            size_t index = CellPosToIndex(pos);
            if(m_Cells.capacity() <= index) m_Cells.resize(index + 1);
            m_Cells.at(CellPosToIndex(pos)) = std::move(cell);
        }
    }

    SweepResult Sweep(const CellPosition& pos) override
    {
        size_t index = CellPosToIndex(pos);
        return m_Cells[index]->Sweep();
    }
    FlagResult Flag(const CellPosition& pos) override
    {
        size_t index = CellPosToIndex(pos);
        return m_Cells[index]->Flag();
    }
    ICell* GetCell(const CellPosition& pos) override
    {
        size_t index = CellPosToIndex(pos);
        return m_Cells[index].get();
    }
    size_t GetSize() const override
    {
        return m_Cells.size();
    }

private:
    size_t CellPosToIndex(const CellPosition& pos);

    std::vector<std::unique_ptr<ICell>> m_Cells;
};

#endif // INCLUDE_GAME_CHUNK_H_