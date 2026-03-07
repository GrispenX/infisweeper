#include "game/Chunk.h"

Chunk::Chunk(std::vector<std::unique_ptr<ICell>>& cells) :
    m_Cells(std::move(cells)) {}

SweepResult Chunk::Sweep(size_t index)
{
    return m_Cells[index]->Sweep();
}

FlagResult Chunk::Flag(size_t index)
{
    return m_Cells[index]->Flag();
}

const ICell* Chunk::GetCell(size_t index) const
{
    return m_Cells[index].get();
}

size_t Chunk::GetSize() const
{
    return m_Cells.size();
}