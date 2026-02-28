#ifndef INCLUDE_GAME_MINEFIELDPOSITIONS_H_
#define INCLUDE_GAME_MINEFIELDPOSITIONS_H_

#include <cstddef>
#include <functional>

struct CellInChunkPosition
{
    size_t Row;
    size_t Col;
};

struct ChunkPosition
{
    long long int Row;
    long long int Col;

    bool operator==(const ChunkPosition& other) const
    {
        return Row == other.Row && Col == other.Col;
    }
};

struct CellGlobalPosition
{
    long long int Row;
    long long int Col;
};

struct ChunkPositionHash
{
    size_t operator()(const ChunkPosition& chunk_pos) const
    {
        std::hash<long long int> hasher;
        size_t row_hash = hasher(chunk_pos.Row);
        size_t col_hash = hasher(chunk_pos.Col);
        return row_hash ^ (col_hash << 1);
    }
};

#endif // INCLUDE_GAME_MINEFIELDPOSITIONS_H_