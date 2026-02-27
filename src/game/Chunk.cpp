#include "game/Chunk.h"

Chunk::Chunk(std::array<std::array<std::unique_ptr<ICell>, GameConf::CHUNK_WIDTH>, GameConf::CHUNK_HEIGHT> cells) :
    m_Cells(std::move(cells))
{

}

SweepResult Chunk::Sweep(const CellInChunkPosition& cell_pos)
{
    return m_Cells[cell_pos.Row][cell_pos.Col]->Sweep();
}

FlagResult Chunk::Flag(const CellInChunkPosition& cell_pos)
{
    return m_Cells[cell_pos.Row][cell_pos.Col]->Flag();
}

const ICell* Chunk::GetCell(const CellInChunkPosition& cell_pos) const
{
    return m_Cells[cell_pos.Row][cell_pos.Col].get();
}
