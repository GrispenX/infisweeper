#include "game/Minefield.h"

SweepResult Minefield::Sweep(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos)
{
    if(!m_LoadedChunks.contains(chunk_pos))
    {
        return SweepResult::INACCESSIBLE;
    }
}

FlagResult Minefield::Flag(const ChunkPosition& chunk_pos, const CellInChunkPosition cell_pos)
{
    if(!m_LoadedChunks.contains(chunk_pos))
    {
        return FlagResult::INACCESSIBLE;
    }
}

const IChunk* Minefield::GetChunk(const ChunkPosition& chunk_pos) const
{
    if(!m_LoadedChunks.contains(chunk_pos))
    {
        return nullptr;
    }

    return m_LoadedChunks.at(chunk_pos).get();
}

void Minefield::AddChunk(std::unique_ptr<IChunk> chunk, const ChunkPosition& chunk_pos)
{
    m_LoadedChunks[chunk_pos] = std::move(chunk);
}