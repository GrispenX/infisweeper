#ifndef INCLUDE_GAME_ICHUNKGENERATOR_H_
#define INCLUDE_GAME_ICHUNKGENERATOR_H_

#include "game/IChunk.h"
#include "game/GeometryConcept.h"
#include <memory>

template<Geometry T>
class IChunkGenerator
{
public:
    using ChunkPosition = typename T::ChunkPosition;

    virtual ~IChunkGenerator() = default;

    virtual std::unique_ptr<IChunk<T>> GenerateChunk(const ChunkPosition& pos) = 0;
};

#endif // INCLUDE_GAME_ICHUNKGENERATOR_H_