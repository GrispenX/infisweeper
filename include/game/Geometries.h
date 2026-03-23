#ifndef INCLUDE_GAME_GEOMETRIES_H_
#define INCLUDE_GAME_GEOMETRIES_H_

#include "game/PlainPosition.h"
#include <vector>
#include <array>
#include <cmath>


template <typename T>
inline void HashCombine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}


class SquareGeometry
{
public:
    struct ChunkPosition
    {
        long long int row;
        long long int col;

        bool operator==(const ChunkPosition& other) const
        {
            return (row == other.row && col == other.col);
        }
    };

    struct CellPosition
    {
        int row;
        int col;
    };
    
    struct MinefieldPosition
    {
        ChunkPosition chunk_pos;
        CellPosition cell_pos;
    };

    struct ChunkPositionHasher
    {
        size_t operator()(const ChunkPosition& chunk_pos) const noexcept
        {
            size_t seed = 0;
            HashCombine(seed, chunk_pos.row);
            HashCombine(seed, chunk_pos.col);
            return seed;
        }
    };
};

#endif // INCLUDE_GAME_GEOMETRIES_H_