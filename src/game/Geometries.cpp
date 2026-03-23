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