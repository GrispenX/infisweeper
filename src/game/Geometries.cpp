#include "game/Geometries.h"

std::vector<SquareGeometry::CellPosition> SquareGeometry::GetAllCellPositions(const ChunkPosition& pos)
{
    std::vector<CellPosition> positions;
    for(int row = 0; row < size; row++)
    {
        for(int col = 0; col < size; col++)
        {
            positions.push_back(CellPosition{.row = row, .col = col});
        }
    }
    return positions;
}

std::vector<SquareGeometry::MinefieldPosition> SquareGeometry::GetNeighboursPositions(const MinefieldPosition& pos)
{
    static const std::vector<CellPosition> offsets = {
        CellPosition{.row = -1, .col = -1},
        CellPosition{.row = -1, .col = 0},
        CellPosition{.row = -1, .col = 1},
        CellPosition{.row = 0, .col = -1},
        CellPosition{.row = 0, .col = 1},
        CellPosition{.row = 1, .col = -1},
        CellPosition{.row = 1, .col = 0},
        CellPosition{.row = 1, .col = 1}
    };
    
    std::vector<MinefieldPosition> positions;
    for(const auto& offset : offsets)
    {
        MinefieldPosition neighbour = pos;
        neighbour.cell_pos.row += offset.row;
        neighbour.cell_pos.col += offset.col;

        if(neighbour.cell_pos.row >= size)
        {
            neighbour.chunk_pos.row += 1;
            neighbour.cell_pos.row = 0;
        }
        else if(neighbour.cell_pos.row < 0)
        {
            neighbour.chunk_pos.row -= 1;
            neighbour.cell_pos.row = size - 1;
        }

        if(neighbour.cell_pos.col >= size)
        {
            neighbour.chunk_pos.col += 1;
            neighbour.cell_pos.col = 0;
        }
        else if(neighbour.cell_pos.col < 0)
        {
            neighbour.chunk_pos.col -= 1;
            neighbour.cell_pos.col = size - 1;
        }

        positions.push_back(neighbour);
    }
    return positions;
}



TriHexGeometry::MinefieldPosition TriHexGeometry::Normilize(MinefieldPosition pos)
{
    MinefieldPosition orig = pos;

    if (pos.cell_pos.a > size)
    {
        pos.cell_pos.a -= 2 * size;
        pos.cell_pos.b += size;
        pos.cell_pos.c += size;

        pos.chunk_pos.a += 1;
        pos.chunk_pos.c -= 1;
    }

    if (pos.cell_pos.b > size - 1)
    {
        pos.cell_pos.a += size;
        pos.cell_pos.b -= 2 * size;
        pos.cell_pos.c += size;

        pos.chunk_pos.b -= 1;
        pos.chunk_pos.c += 1;
    }

    if (pos.cell_pos.c > size)
    {
        pos.cell_pos.a += size;
        pos.cell_pos.b += size;
        pos.cell_pos.c -= 2 * size;

        pos.chunk_pos.a -= 1;
        pos.chunk_pos.b += 1;
    }

    if (pos.cell_pos.a < -size + 1)
    {
        pos.cell_pos.a += 2 * size;
        pos.cell_pos.b -= size;
        pos.cell_pos.c -= size;

        pos.chunk_pos.a -= 1;
        pos.chunk_pos.c += 1;
    }

    if (pos.cell_pos.b < -size)
    {
        pos.cell_pos.a -= size;
        pos.cell_pos.b += 2 * size;
        pos.cell_pos.c -= size;

        pos.chunk_pos.b += 1;
        pos.chunk_pos.c -= 1;
    }

    if(pos.cell_pos.c < -size + 1)
    {
        pos.cell_pos.a -= size;
        pos.cell_pos.b -= size;
        pos.cell_pos.c += 2 * size;

        pos.chunk_pos.a += 1;
        pos.chunk_pos.b -= 1;
    }

    if(pos != orig) return Normilize(pos);

    return pos;
}

std::vector<TriHexGeometry::CellPosition> TriHexGeometry::GetAllCellPositions(const ChunkPosition& pos)
{
    std::vector<CellPosition> cells;
    {
        for(int a = -size + 1; a <= size; a++)
        {
            for(int b = -size; b < size; b++)
            {
                for(int c = -size + 1; c <= size; c++)
                {
                    if(a + b + c == 0 || a + b + c == 1) cells.push_back({a, b, c});
                }
            }
        }
    }
    return cells;
}

std::vector<TriHexGeometry::MinefieldPosition> TriHexGeometry::GetNeighboursPositions(const MinefieldPosition& pos)
{
    auto add_cell_pos = [](MinefieldPosition pos, const CellPosition& offset) {
        pos.cell_pos.a += offset.a;
        pos.cell_pos.b += offset.b;
        pos.cell_pos.c += offset.c;
        return Normilize(pos);
    };

    if(pos.cell_pos.a + pos.cell_pos.b + pos.cell_pos.c == 0)
    {
        return {
            add_cell_pos(pos, {  0,  1,  0 }),
            add_cell_pos(pos, {  0,  1, -1 }),
            add_cell_pos(pos, {  1,  1, -1 }),
            add_cell_pos(pos, {  1,  0, -1 }),
            add_cell_pos(pos, {  1,  0,  0 }),
            add_cell_pos(pos, {  1, -1,  0 }),
            add_cell_pos(pos, {  1, -1,  1 }),
            add_cell_pos(pos, {  0, -1,  1 }),
            add_cell_pos(pos, {  0,  0,  1 }),
            add_cell_pos(pos, { -1,  0,  1 }),
            add_cell_pos(pos, { -1,  1,  1 }),
            add_cell_pos(pos, { -1,  1,  0 })
        };
    }
    else
    {
        return {
            add_cell_pos(pos, {  0, -1,  0 }),
            add_cell_pos(pos, {  0, -1,  1 }),
            add_cell_pos(pos, { -1, -1,  1 }),
            add_cell_pos(pos, { -1,  0,  1 }),
            add_cell_pos(pos, { -1,  0,  0 }),
            add_cell_pos(pos, { -1,  1,  0 }),
            add_cell_pos(pos, { -1,  1, -1 }),
            add_cell_pos(pos, {  0,  1, -1 }),
            add_cell_pos(pos, {  0,  0, -1 }),
            add_cell_pos(pos, {  1,  0, -1 }),
            add_cell_pos(pos, {  1, -1, -1 }),
            add_cell_pos(pos, {  1, -1,  0 })
        };
    }
}