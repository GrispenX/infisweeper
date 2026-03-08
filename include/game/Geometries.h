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

    static size_t CellsAmount(const ChunkPosition& pos)
    {
        return TSize * TSize;
    }

    static MinefieldPosition PlainToMinefield(const PlainPosition& pos)
    {
        ChunkPosition chunk_pos;
        chunk_pos.row = floor(pos.x / (double)TSize);
        chunk_pos.col = floor(pos.y / (double)TSize);

        CellPosition cell_pos;
        cell_pos.row = floor(pos.x - chunk_pos.row * (double)TSize);
        cell_pos.col = floor(pos.y - chunk_pos.col * (double)TSize);

        return MinefieldPosition{.chunk_pos = chunk_pos, .cell_pos = cell_pos};
    }

    static size_t MinefieldToIndex(const MinefieldPosition& pos)
    {
        return pos.cell_pos.row * TSize + pos.cell_pos.col;
    }

    static std::vector<MinefieldPosition> GetNeighboursPositions(const MinefieldPosition& pos)
    {   
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

    static std::vector<ChunkPosition> GetChunksInRectangle(const PlainPosition& pos1, const PlainPosition& pos2)
    {
        double min_x = std::min(pos1.x, pos2.x);
        double min_y = std::min(pos1.y, pos2.y);
        double max_x = std::max(pos1.x, pos2.x);
        double max_y = std::max(pos1.y, pos2.y);

        long long int min_row = std::floor(min_x / (double)TSize);
        long long int min_col = std::floor(min_y / (double)TSize);
        long long int max_row = std::floor(max_x / (double)TSize);
        long long int max_col = std::floor(max_y / (double)TSize);

        std::vector<ChunkPosition> positions;
        for(long long int row = min_row; row <= max_row; row++)
        {
            for(long long int col = min_col; col <= max_col; col++)
            {
                positions.push_back(ChunkPosition{.row = row, .col = col});
            }
        }
        return positions;
    }

    static std::vector<MinefieldPosition> GetCellsInRectangle(const PlainPosition& pos1, const PlainPosition& pos2)
    {
        double min_x = std::min(pos1.x, pos2.x);
        double min_y = std::min(pos1.y, pos2.y);
        double max_x = std::max(pos1.x, pos2.x);
        double max_y = std::max(pos1.y, pos2.y);

        long long int min_row = std::floor(min_x);
        long long int min_col = std::floor(min_y);
        long long int max_row = std::floor(max_x);
        long long int max_col = std::floor(max_y);

        std::vector<MinefieldPosition> positions;
        for(long long int row = min_row; row <= max_row; row++)
        {
            for(long long int col = min_col; col <= max_col; col++)
            {
                ChunkPosition chunk_pos = {
                    .row = static_cast<long long int>(std::floor((double)row / (double)TSize)),
                    .col = static_cast<long long int>(std::floor((double)col / (double)TSize))
                };

                CellPosition cell_pos = {
                    .row = static_cast<int>(row - chunk_pos.row * TSize),
                    .col = static_cast<int>(col - chunk_pos.col * TSize)
                };

                positions.push_back(MinefieldPosition{.chunk_pos = chunk_pos, .cell_pos = cell_pos});
            }
        }
        return positions;
    }

    static std::vector<std::pair<PlainPosition, PlainPosition>> GetChunkBoundaries(const ChunkPosition& pos)
    {
        double x1 = pos.row * (double)TSize;
        double x2 = x1 + (double)TSize;
        double y1 = pos.col * (double)TSize;
        double y2 = y1 + (double)TSize;

        std::vector<std::pair<PlainPosition, PlainPosition>> boundaries = {
            {PlainPosition{.x = x1, .y = y2}, PlainPosition{.x = x2, .y = y2}},
            {PlainPosition{.x = x1, .y = y1}, PlainPosition{.x = x2, .y = y1}},
            {PlainPosition{.x = x1, .y = y2}, PlainPosition{.x = x1, .y = y1}},
            {PlainPosition{.x = x2, .y = y2}, PlainPosition{.x = x2, .y = y1}}
        };
        
        return boundaries;
    }

    static CellShape GetCellShape(const MinefieldPosition& pos)
    {
        return CellShape::SQUARE;
    }

    static PlainPosition GetCellCenter(const MinefieldPosition& pos)
    {
        double x = pos.chunk_pos.row * (double)TSize + pos.cell_pos.row + 0.5;
        double y = pos.chunk_pos.col * (double)TSize + pos.cell_pos.col + 0.5;
        return PlainPosition{.x = x, .y = y};
    }

    static double GetCellScale(const MinefieldPosition& pos)
    {
        return 1.0;
    }

    static double GetCellRotation(const MinefieldPosition& pos)
    {
        return 0.0;
    }
};

#endif // INCLUDE_GAME_GEOMETRIES_H_