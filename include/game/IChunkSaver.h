#ifndef INCLUDE_GAME_ICHUNKSAVER_H_
#define INCLUDE_GAME_ICHUNKSAVER_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"

class IChunkSaver
{
public:
    ~IChunkSaver() = default;

    virtual void SaveChunk(const IChunk* chunk, const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKSAVER_H_