#ifndef INCLUDE_GAME_ICHUNKLOADER_H_
#define INCLUDE_GAME_ICHUNKLOADER_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"
#include <memory>

class IChunkLoader
{
public:
    ~IChunkLoader() = default;

    virtual std::unique_ptr<IChunk> LoadChunk(const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKLOADER_H_