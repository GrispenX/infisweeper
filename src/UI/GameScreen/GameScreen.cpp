#include "UI/GameScreen/GameScreen.h"
#include "game/Geometries.h"
#include <cmath>


/*
    Square geometry
*/

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
TextureID GameScreen<SquareGeometry>::GetCellTexture(const MinefieldPosition& pos)
{
    return TextureID::SQUARE_CELL;
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

/*
    Square geometry
*/



/*
    TriHex geometry
*/

template<>
TriHexGeometry::MinefieldPosition GameScreen<TriHexGeometry>::PlainToMinefield(const PlainPosition& pos)
{
    const double rt3 = std::sqrt(3.0);
    const double chunk_side = (double)TriHexGeometry::size;
    
    const double chunk_af = -2.0 * pos.x / 3.0 / chunk_side;
    const double chunk_bf = pos.x / 3.0 / chunk_side - pos.y / rt3 / chunk_side;
    const double chunk_cf = pos.x / 3.0 / chunk_side + pos.y / rt3 / chunk_side;

    int chunk_a = (int)std::round(chunk_af);
    int chunk_b = (int)std::round(chunk_bf);
    int chunk_c = (int)std::round(chunk_cf);

    const double chunk_da = std::abs((double)chunk_a - chunk_af);
    const double chunk_db = std::abs((double)chunk_b - chunk_bf);
    const double chunk_dc = std::abs((double)chunk_c - chunk_cf);

    if(chunk_a + chunk_b + chunk_c != 0)
    {
        if(chunk_da >= chunk_db && chunk_da >= chunk_dc) chunk_a = -chunk_b - chunk_c;
        else if(chunk_db >= chunk_da && chunk_db >= chunk_dc) chunk_b = -chunk_a - chunk_c;
        else chunk_c = -chunk_a - chunk_b;
    }

    ChunkPosition chunk_pos {chunk_a, chunk_b, chunk_c};

    const PlainPosition chunk_a_step {-chunk_side, 0.0};
    const PlainPosition chunk_b_step {chunk_side / 2.0, -rt3 * chunk_side / 2.0};
    const PlainPosition chunk_c_step {chunk_side / 2.0, rt3 * chunk_side / 2.0};
    const PlainPosition chunk_center = chunk_a_step * chunk_pos.a + chunk_b_step * chunk_pos.b + chunk_c_step * chunk_pos.c;



    const PlainPosition rel_pos = pos - chunk_center;

    const CellPosition cell_pos {
        -(int)std::floor(rel_pos.x + rel_pos.y / rt3) ,
        (int)std::floor(rel_pos.y * 2.0 / rt3),
        (int)std::floor(rel_pos.x - rel_pos.y / rt3) + 1
    };

    return {chunk_pos, cell_pos};
}

template<>
PlainPosition GameScreen<TriHexGeometry>::GetCellCenterPos(const MinefieldPosition& pos)
{
    const double rt3 = std::sqrt(3.0);
    const double chunk_side = (double)TriHexGeometry::size;

    const PlainPosition chunk_a_step {-chunk_side, 0.0};
    const PlainPosition chunk_b_step {chunk_side / 2.0, -rt3 * chunk_side / 2.0};
    const PlainPosition chunk_c_step {chunk_side / 2.0, rt3 * chunk_side / 2.0};
    const PlainPosition chunk_center = chunk_a_step * pos.chunk_pos.a + chunk_b_step * pos.chunk_pos.b + chunk_c_step * pos.chunk_pos.c;

    const PlainPosition cell_a_step {-1.0 / 2.0, -rt3 / 6.0};
    const PlainPosition cell_b_step {0.0, rt3 / 3.0};
    const PlainPosition cell_c_step {1.0 / 2.0, -rt3 / 6.0};
    return cell_a_step * pos.cell_pos.a + cell_b_step * pos.cell_pos.b + cell_c_step * pos.cell_pos.c + chunk_center + PlainPosition {0.0, rt3 / 3.0};
}

template<>
double GameScreen<TriHexGeometry>::GetCellSize(const MinefieldPosition& pos)
{
    return 1.0;
}

template<>
double GameScreen<TriHexGeometry>::GetCellRotation(const MinefieldPosition& pos)
{
    return pos.cell_pos.a + pos.cell_pos.b + pos.cell_pos.c == 0 ? 0.0 : 180.0;
}

template<>
TextureID GameScreen<TriHexGeometry>::GetCellTexture(const MinefieldPosition& pos)
{
    return TextureID::EQUILATERAL_TRIANGLE;
}

template<>
std::vector<TriHexGeometry::ChunkPosition> GameScreen<TriHexGeometry>::GetChunksInRectangle(const PlainPosition& pos1, const PlainPosition& pos2)
{
    const double rt3 = std::sqrt(3.0);
    const double chunk_side = (double)TriHexGeometry::size;

    const double min_x = std::min(pos1.x, pos2.x) - chunk_side;
    const double max_x = std::max(pos1.x, pos2.x) + chunk_side;
    const double min_y = std::min(pos1.y, pos2.y) - rt3 * chunk_side / 2.0;
    const double max_y = std::max(pos1.y, pos2.y) + rt3 * chunk_side / 2.0;

    const long long int min_b = PlainToMinefield({min_x, max_y}).chunk_pos.b;
    const long long int max_b = PlainToMinefield({max_x, min_y}).chunk_pos.b;
    const long long int min_c = PlainToMinefield({min_x, min_y}).chunk_pos.c;
    const long long int max_c = PlainToMinefield({max_x, max_y}).chunk_pos.c;

    std::vector<ChunkPosition> chunks;
    for(long long int b = min_b; b <= max_b; b++)
    {
        for(long long int c = min_c; c < max_c; c++)
        {
            chunks.push_back({- b - c, b, c});
        }
    }
    return chunks;
}

template<>
std::vector<std::pair<PlainPosition, PlainPosition>> GameScreen<TriHexGeometry>::GetChunkBoundaries(const ChunkPosition& pos)
{
    const double rt3 = std::sqrt(3.0);
    const double chunk_side = (double)TriHexGeometry::size;
    const double h = rt3 * chunk_side / 2.0;

    const PlainPosition chunk_a_step {-chunk_side, 0.0};
    const PlainPosition chunk_b_step {chunk_side / 2.0, -rt3 * chunk_side / 2.0};
    const PlainPosition chunk_c_step {chunk_side / 2.0, rt3 * chunk_side / 2.0};
    const PlainPosition chunk_center = chunk_a_step * pos.a + chunk_b_step * pos.b + chunk_c_step * pos.c;

    PlainPosition v1 = chunk_center + PlainPosition {-chunk_side / 2.0, -h};
    PlainPosition v2 = chunk_center + PlainPosition {chunk_side / 2.0, -h};
    PlainPosition v3 = chunk_center + PlainPosition {chunk_side, 0.0};
    PlainPosition v4 = chunk_center + PlainPosition {chunk_side / 2.0, h};
    PlainPosition v5 = chunk_center + PlainPosition {-chunk_side / 2.0, h};
    PlainPosition v6 = chunk_center + PlainPosition {-chunk_side, 0.0};

    return {
        {v1, v2},
        {v2, v3},
        {v3, v4},
        {v4, v5},
        {v5, v6},
        {v6, v1}
    };
}

/*
    TriHex geometry
*/