#include "game/ChunkBuilder.h"

void ChunkBuilder::Reset()
{
    for(auto& row : m_Cells)
    {
        for(auto& cell : row)
        {
            cell.reset();
        }
    }
}

void ChunkBuilder::AddCell(const CellInChunkPosition &cell_pos, std::unique_ptr<ICell> cell)
{
    m_Cells[cell_pos.Row][cell_pos.Col] = std::move(cell);
}

std::unique_ptr<IChunk> ChunkBuilder::GetResult()
{
    return std::make_unique<Chunk>(std::move(m_Cells));
}