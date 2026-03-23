#ifndef INCLUDE_GAME_ICHUNKSTORAGE_H_
#define INCLUDE_GAME_ICHUNKSTORAGE_H_

#include "game/GeometryConcept.h"
#include "game/IChunk.h"
#include <memory>
#include <vector>

template<Geometry T>
class IChunkStorage
{
public:
    using ChunkPosition = typename T::ChunkPosition;

    virtual ~IChunkStorage() = default;

    virtual std::shared_ptr<IChunk<T>> GetChunk(const ChunkPosition& chunk_pos) = 0;
    virtual std::vector<std::pair<ChunkPosition, std::shared_ptr<IChunk<T>>>> GetAllChunks() = 0;
    virtual void PushChunk(const ChunkPosition& chunk_pos, std::shared_ptr<IChunk<T>> chunk) = 0;
};

#endif // INCLUDE_GAME_ICHUNKSTORAGE_H_