#ifndef INCLUDE_GAME_ICHUNKFACTORY_H_
#define INCLUDE_GAME_ICHUNKFACTORY_H_

#include "game/GeometryConcept.h"
#include "game/IChunk.h"
#include <memory>
#include <vector>

template<Geometry T>
class IChunkFactory
{
public:
    using CellPosition = typename T::CellPosition;

    virtual ~IChunkFactory() = default;

    virtual std::unique_ptr<IChunk<T>> CreateChunk(std::vector<std::pair<CellPosition, std::unique_ptr<ICell>>> cells) = 0;
};

#endif // INCLUDE_GAME_ICHUNKFACTORY_H_