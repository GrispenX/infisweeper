#ifndef INCLUDE_GAME_ICHUNKPROVIDER_H_
#define INCLUDE_GAME_ICHUNKPROVIDER_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"

class IChunkProvider
{
public:
    ~IChunkProvider() = default;

    virtual std::unique_ptr<IChunk> GetChunk(const ChunkPosition& chunk_pos) = 0;
    virtual std::unique_ptr<IChunk> GetRegeneratedChunk(const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKPROVIDER_H_