#ifndef INCLUDE_GAME_ICHUNKPROVIDER_H_
#define INCLUDE_GAME_ICHUNKPROVIDER_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"
#include <memory>

class IChunkProvider
{
public:
    ~IChunkProvider() = default;

    virtual std::shared_ptr<IChunk> GetChunk(const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKPROVIDER_H_