#include "game/Chunk.h"

Chunk::Chunk(std::array<std::array<std::unique_ptr<ICell>, GameConf::CHUNK_WIDTH>, GameConf::CHUNK_HEIGHT> cells) :
    m_Cells(std::move(cells))
{

}

SweepResult Chunk::Sweep(const CellInChunkPosition& cell_pos)
{
    if(cell_pos.Row >= GameConf::CHUNK_HEIGHT || cell_pos.Col >= GameConf::CHUNK_WIDTH)
    {
        return SweepResult::INVALID_CELL_POSITION;
    }

    return m_Cells[cell_pos.Row][cell_pos.Col]->Sweep();
}

FlagResult Chunk::Flag(const CellInChunkPosition& cell_pos)
{
    if(cell_pos.Row >= GameConf::CHUNK_HEIGHT || cell_pos.Col >= GameConf::CHUNK_WIDTH)
    {
        return FlagResult::INVALID_CELL_POSITION;
    }

    return m_Cells[cell_pos.Row][cell_pos.Col]->Flag();
}

const ICell* Chunk::GetCell(const CellInChunkPosition& cell_pos) const
{
    return m_Cells[cell_pos.Row][cell_pos.Col].get();
}
