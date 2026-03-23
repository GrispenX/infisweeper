#ifndef INCLUDE_GAME_CHUNKFACTORY_H_
#define INCLUDE_GAME_CHUNKFACTORY_H_

#include "game/GeometryConcept.h"
#include "game/IChunkFactory.h"
#include "game/Chunk.h"

template<Geometry T>
class ChunkFactory : public IChunkFactory<T>
{
public:
    using CellPosition = typename T::CellPosition;

    std::unique_ptr<IChunk<T>> CreateChunk(std::vector<std::pair<CellPosition, std::unique_ptr<ICell>>> cells) override
    {
        return std::make_unique<Chunk<T>>(std::move(cells));
    }
};

#endif // INCLUDE_GAME_CHUNKFACTORY_H_