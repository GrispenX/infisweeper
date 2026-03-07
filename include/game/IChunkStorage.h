#ifndef INCLUDE_GAME_ICHUNKSTORAGE_H_
#define INCLUDE_GAME_ICHUNKSTORAGE_H_

#include "game/GeometryConcept.h"
#include "game/IChunk.h"
#include <memory>

template<Geometry TGeometry>
class IChunkStorage
{
public:
    ~IChunkStorage() = default;

    virtual std::shared_ptr<IChunk> GetChunk(const TGeometry::ChunkPosition& chunk_pos) = 0;
    virtual void PushChunk(const TGeometry::ChunkPosition& chunk_pos, std::shared<IChunk> chunk) = 0;
};

#endif // INCLUDE_GAME_ICHUNKSTORAGE_H_