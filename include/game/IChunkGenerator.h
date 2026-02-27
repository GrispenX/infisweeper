#ifndef INCLUDE_GAME_ICHUNKGENERATOR_H_
#define INCLUDE_GAME_ICHUNKGENERATOR_H_

#include "game/IChunk.h"
#include "MinefieldPositions.h"
#include <memory>

class IChunkGenerator
{
public:
    ~IChunkGenerator() = default;

    virtual std::unique_ptr<IChunk> GenerateChunk(const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKGENERATOR_H_