#ifndef INCLUDE_GAME_IGAMEMODEL_H_
#define INCLUDE_GAME_IGAMEMODEL_H_

#include "game/GeometryConcept.h"
#include "game/ICell.h"
#include "game/IChunk.h"
#include "game/ChunkData.h"

template<Geometry T>
class IGameModel
{
public:
    using ChunkPosition = typename T::ChunkPosition;
    using MinefieldPosition = typename T::MinefieldPosition;

    virtual ~IGameModel() = default;

    virtual SweepResult Sweep(const MinefieldPosition& pos) = 0;
    virtual FlagResult Flag(const MinefieldPosition& pos) = 0;
    virtual ChunkData GetChunkData(const ChunkPosition& pos) = 0;
};

#endif // INCLUDE_GAME_IGAMEMODEL_H_