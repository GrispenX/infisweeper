#include "UI/GameScreen.h"
#include "game/Geometries.h"

template<>
SquareGeometry::MinefieldPosition GameScreen<SquareGeometry>::PlainToMinefield(const PlainPosition& pos)
{
    ChunkPosition chunk;
    chunk.row = floor(pos.x / (double)SquareGeometry::size);
    chunk.col = floor(pos.y / (double)SquareGeometry::size);

    CellPosition cell;
    cell.row = floor(pos.x - chunk.row * (double)SquareGeometry::size);
    cell.col = floor(pos.y - chunk.col * (double)SquareGeometry::size);

    return MinefieldPosition{.chunk_pos = chunk, .cell_pos = cell};
}

template<>
PlainPosition GameScreen<SquareGeometry>::GetCellCenterPos(const MinefieldPosition& pos)
{
    double x = pos.chunk_pos.row * SquareGeometry::size + pos.cell_pos.row + 0.5;
    double y = pos.chunk_pos.col * SquareGeometry::size + pos.cell_pos.col + 0.5;
    return PlainPosition{.x = x, .y = y};
}

template<>
double GameScreen<SquareGeometry>::GetCellSize(const MinefieldPosition& pos)
{
    return 1.0;
}

template<>
double GameScreen<SquareGeometry>::GetCellRotation(const MinefieldPosition& pos)
{
    return 0.0;
}

template<>
CellShape GameScreen<SquareGeometry>::GetCellShape(const MinefieldPosition& pos)
{
    return CellShape::SQUARE;
}

template<>
std::vector<SquareGeometry::ChunkPosition> GameScreen<SquareGeometry>::GetChunksInRectangle(const PlainPosition& pos1, const PlainPosition& pos2)
{
    double min_x = std::min(pos1.x, pos2.x);
    double min_y = std::min(pos1.y, pos2.y);
    double max_x = std::max(pos1.x, pos2.x);
    double max_y = std::max(pos1.y, pos2.y);

    long long int min_row = std::floor(min_x / (double)SquareGeometry::size);
    long long int min_col = std::floor(min_y / (double)SquareGeometry::size);
    long long int max_row = std::floor(max_x / (double)SquareGeometry::size);
    long long int max_col = std::floor(max_y / (double)SquareGeometry::size);

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

template<>
std::vector<std::pair<PlainPosition, PlainPosition>> GameScreen<SquareGeometry>::GetChunkBoundaries(const ChunkPosition& pos)
{
    double x1 = pos.row * SquareGeometry::size;
    double x2 = x1 + SquareGeometry::size;
    double y1 = pos.col * SquareGeometry::size;
    double y2 = y1 + SquareGeometry::size;

    std::vector<std::pair<PlainPosition, PlainPosition>> boundaries = {
        {PlainPosition{.x = x1, .y = y2}, PlainPosition{.x = x2, .y = y2}},
        {PlainPosition{.x = x1, .y = y1}, PlainPosition{.x = x2, .y = y1}},
        {PlainPosition{.x = x1, .y = y2}, PlainPosition{.x = x1, .y = y1}},
        {PlainPosition{.x = x2, .y = y2}, PlainPosition{.x = x2, .y = y1}}
    };
    
    return boundaries;
}