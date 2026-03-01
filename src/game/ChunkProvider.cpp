#include "game/ChunkProvider.h"

ChunkProvider::ChunkProvider(IChunkLoader* chunk_loader, IChunkLoader* chunk_cache, IChunkGenerator* chunk_generator) :
    m_ChunkLoader(chunk_loader),
    m_ChunkCahce(chunk_cache),
    m_ChunkGenerator(chunk_generator)
{

}

std::unique_ptr<IChunk> ChunkProvider::GetChunk(const ChunkPosition& chunk_pos)
{
    std::unique_ptr<IChunk> chunk = m_ChunkLoader->LoadChunk(chunk_pos);
    if(!chunk)
    {
        chunk = m_ChunkGenerator->GenerateChunk(chunk_pos);
    }
    return chunk;
}

std::unique_ptr<IChunk> ChunkProvider::GetRegeneratedChunk(const ChunkPosition& chunk_pos)
{
    return m_ChunkGenerator->GenerateChunk(chunk_pos);
}