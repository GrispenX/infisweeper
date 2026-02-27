#ifndef INCLUDE_GAME_IMINEFIELDFILEMANAGER_H_
#define INCLUDE_GAME_IMINEFIELDFILEMANAGER_H_

#include "game/MinefieldPositions.h"
#include "game/IChunk.h"
#include <memory>

class IMinefieldFileManager
{
public:
    ~IMinefieldFileManager() = default;

    virtual void WriteChunk(const IChunk& chunk, const ChunkPosition& chunk_pos) = 0;
    virtual std::unique_ptr<IChunk> ReadChunk(const ChunkPosition& chunk_pos) = 0;
};

#endif // INCLUDE_GAME_IMINEFIELDFILEMANAGER_H_