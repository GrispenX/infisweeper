#ifndef INCLUDE_GAME_ICHUNKGENERATOR_H_
#define INCLUDE_GAME_ICHUNKGENERATOR_H_

#include "game/IChunk.h"
#include "game/GeometryConcept.h"
#include <memory>

template<Geometry TGeometry>
class IChunkGenerator
{
public:
    ~IChunkGenerator() = default;

    virtual std::shared_ptr<IChunk> GenerateChunk(const TGeometry::ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKGENERATOR_H_