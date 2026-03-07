#ifndef INCLUDE_GAME_GEOMETRIES_H_
#define INCLUDE_GAME_GEOMETRIES_H_

#include <vector>
#include <cmath>


struct PlainPosition
{
    double x;
    double y;
};


template <typename T>
inline void HashCombine(std::size_t& seed, const T& v) {
    std::hash<T> hasher;
    seed ^= hasher(v) + 0x9e3779b9 + (seed<<6) + (seed>>2);
}


template<size_t TSize>
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

    static constexpr size_t Size = TSize;
    static constexpr size_t CellsAmount = Size * Size;

    static MinefieldPosition PlainToMinefield(const PlainPosition& pos)
    {
        ChunkPosition chunk_pos;
        chunk_pos.row = floor(pos.x / TSize);
        chunk_pos.col = floor(pos.y / TSize);

        CellPosition cell_pos;
        cell_pos.row = floor(pos.x - chunk_pos.row * TSize);
        cell_pos.col = floor(pos.y - chunk_pos.col * TSize);

        return MinefieldPosition{.chunk_pos = chunk_pos, .cell_pos = cell_pos};
    }

    static size_t MinefieldToIndex(const MinefieldPosition& pos)
    {
        return pos.cell_pos.row * 10 + pos.cell_pos.col;
    }

    static std::vector<MinefieldPosition> GetNeighboursPositions(const MinefieldPosition& pos)
    {   
        std::vector<MinefieldPosition> neighbours;
        for(const auto& offset : offsets)
        {
            MinefieldPosition neighbour = pos;
            neighbour.cell_pos.row += offset.row;
            neighbour.cell_pos.col += offset.col;

            if(neighbour.cell_pos.row < 0)
            {
                neighbour.cell_pos.row = TSize - 1;
                neighbour.chunk_pos.row -= 1;
            }
            else if(neighbour.cell_pos.row >= TSize)
            {
                neighbour.cell_pos.row = 0;
                neighbour.chunk_pos.row += 1;
            }

            if(neighbour.cell_pos.col < 0)
            {
                neighbour.cell_pos.col = TSize - 1;
                neighbour.chunk_pos.col -= 1;
            }
            else if(neighbour.cell_pos.col >= TSize)
            {
                neighbour.cell_pos.col = 0;
                neighbour.chunk_pos.col += 1;
            }

            neighbours.push_back(neighbour);
        }
        return neighbours;
    }

private:
    static constexpr std::array<CellPosition, 8> offsets = {
        CellPosition{.row = -1, .col = -1},
        CellPosition{.row = -1, .col = 0},
        CellPosition{.row = -1, .col = 1},
        CellPosition{.row = 0, .col = -1},
        CellPosition{.row = 0, .col = 1},
        CellPosition{.row = 1, .col = -1},
        CellPosition{.row = 1, .col = 0},
        CellPosition{.row = 1, .col = 1}
    };
};

#endif // INCLUDE_GAME_GEOMETRIES_H_