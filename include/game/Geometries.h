#ifndef INCLUDE_GAME_GEOMETRIES_H_
#define INCLUDE_GAME_GEOMETRIES_H_

#include <vector>
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

        auto operator<=>(const ChunkPosition& other) const = default;
    };

    struct CellPosition
    {
        int row;
        int col;

        auto operator<=>(const CellPosition& other) const = default;
    };
    
    struct MinefieldPosition
    {
        ChunkPosition chunk_pos;
        CellPosition cell_pos;
    };

    static std::vector<CellPosition> GetAllCellPositions(const ChunkPosition& pos);

    static std::vector<MinefieldPosition> GetNeighboursPositions(const MinefieldPosition& pos);

    static constexpr int size = 10;
};

#endif // INCLUDE_GAME_GEOMETRIES_H_