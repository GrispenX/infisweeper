#ifndef INCLUDE_GAME_ICHUNKGENERATOR_H_
#define INCLUDE_GAME_ICHUNKGENERATOR_H_

#include "game/IChunk.h"
#include "game/GeometryConcept.h"
#include <memory>

class IChunkGenerator
{
public:
    ~IChunkGenerator() = default;

    virtual std::shared_ptr<IChunk> GenerateChunk(size_t chunk_pos_hash, size_t cells_amount) = 0;
};

#endif // INCLUDE_GAME_ICHUNKGENERATOR_H_