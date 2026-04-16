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

    static constexpr int ID = 1;

    static std::vector<CellPosition> GetAllCellPositions(const ChunkPosition& pos);

    static std::vector<MinefieldPosition> GetNeighboursPositions(const MinefieldPosition& pos);

    static constexpr int size = 10;
};

template<>
struct std::hash<SquareGeometry::ChunkPosition>
{
    size_t operator()(const SquareGeometry::ChunkPosition& pos) const
    {
        size_t seed = 0;
        HashCombine(seed, pos.row);
        HashCombine(seed, pos.col);
        return seed;
    }
};

template<>
struct std::hash<SquareGeometry::CellPosition>
{
    size_t operator()(const SquareGeometry::CellPosition& pos) const
    {
        size_t seed = 0;
        HashCombine(seed, pos.row);
        HashCombine(seed, pos.col);
        return seed;
    }
};



class TriHexGeometry
{
public:
    struct ChunkPosition
    {
        long long int a;
        long long int b;
        long long int c;

        auto operator<=>(const ChunkPosition& other) const = default;
    };

    struct CellPosition
    {
        int a;
        int b;
        int c;

        auto operator<=>(const CellPosition& other) const = default;
    };

    struct MinefieldPosition
    {
        ChunkPosition chunk_pos;
        CellPosition cell_pos;

        auto operator<=>(const MinefieldPosition& other) const = default;
    };

    static std::vector<CellPosition> GetAllCellPositions(const ChunkPosition& pos);
    
    static std::vector<MinefieldPosition> GetNeighboursPositions(const MinefieldPosition& pos);

    static constexpr int ID = 2;
    
    static constexpr int size = 5;

private:
    static MinefieldPosition Normilize(MinefieldPosition pos);
};

template<>
struct std::hash<TriHexGeometry::ChunkPosition>
{
    size_t operator()(const TriHexGeometry::ChunkPosition& pos) const
    {
        size_t seed = 0;
        HashCombine(seed, pos.a);
        HashCombine(seed, pos.b);
        HashCombine(seed, pos.c);
        return seed;
    }
};

template<>
struct std::hash<TriHexGeometry::CellPosition>
{
    size_t operator()(const TriHexGeometry::CellPosition& pos) const
    {
        size_t seed = 0;
        HashCombine(seed, pos.a);
        HashCombine(seed, pos.b);
        HashCombine(seed, pos.c);
        return seed;
    }
};

#endif // INCLUDE_GAME_GEOMETRIES_H_