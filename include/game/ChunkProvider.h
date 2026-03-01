#ifndef INCLUDE_GAME_CHUNKPROVIDER_H_
#define INCLUDE_GAME_CHUNKPROVIDER_H_

#include "game/IChunkProvider.h"
#include "game/IChunkLoader.h"
#include "game/IChunkGenerator.h"

class ChunkProvider : public IChunkProvider
{
public:
    ChunkProvider(IChunkLoader* chunk_loader, IChunkLoader* chunk_cache, IChunkGenerator* chunk_generator);

    std::unique_ptr<IChunk> GetChunk(const ChunkPosition& chunk_pos) override;
    std::unique_ptr<IChunk> GetRegeneratedChunk(const ChunkPosition& chunk_pos) override;

private:
    IChunkLoader* m_ChunkLoader;
    IChunkLoader* m_ChunkCahce;
    IChunkGenerator* m_ChunkGenerator;
};

#endif // INCLUDE_GAME_CHUNKPROVIDER_H_