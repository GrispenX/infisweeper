#include <gtest/gtest.h>

#include <algorithm>
#include <unordered_set>

#include "game/Geometries.h"

namespace
{
bool ContainsSquarePosition(
    const std::vector<SquareGeometry::MinefieldPosition>& positions,
    const SquareGeometry::MinefieldPosition& expected)
{
    return std::any_of(positions.begin(), positions.end(), [&expected](const auto& current) {
        return current.chunk_pos == expected.chunk_pos && current.cell_pos == expected.cell_pos;
    });
}

bool ContainsTriHexPosition(
    const std::vector<TriHexGeometry::MinefieldPosition>& positions,
    const TriHexGeometry::MinefieldPosition& expected)
{
    return std::any_of(positions.begin(), positions.end(), [&expected](const auto& current) {
        return current.chunk_pos == expected.chunk_pos && current.cell_pos == expected.cell_pos;
    });
}

bool IsTriHexCellInNormalizedBounds(const TriHexGeometry::CellPosition& cell)
{
    return cell.a >= -TriHexGeometry::size + 1 && cell.a <= TriHexGeometry::size &&
           cell.b >= -TriHexGeometry::size && cell.b <= TriHexGeometry::size - 1 &&
           cell.c >= -TriHexGeometry::size + 1 && cell.c <= TriHexGeometry::size;
}

bool IsTriHexCellValid(const TriHexGeometry::CellPosition& cell)
{
    const int sum = cell.a + cell.b + cell.c;
    return (sum == 0 || sum == 1) && IsTriHexCellInNormalizedBounds(cell);
}
} // namespace

TEST(GeometriesTest, SquareGetAllCellPositionsReturnsFullUniqueGrid)
{
    auto positions = SquareGeometry::GetAllCellPositions(SquareGeometry::ChunkPosition{0, 0});

    EXPECT_EQ(positions.size(), static_cast<size_t>(SquareGeometry::size * SquareGeometry::size));

    std::unordered_set<SquareGeometry::CellPosition> unique_positions(positions.begin(), positions.end());
    EXPECT_EQ(unique_positions.size(), positions.size());

    EXPECT_TRUE(unique_positions.contains(SquareGeometry::CellPosition{0, 0}));
    EXPECT_TRUE(unique_positions.contains(SquareGeometry::CellPosition{SquareGeometry::size - 1, SquareGeometry::size - 1}));
}

TEST(GeometriesTest, SquareNeighboursWrapAcrossChunkBoundaries)
{
    SquareGeometry::MinefieldPosition origin{
        SquareGeometry::ChunkPosition{0, 0},
        SquareGeometry::CellPosition{0, 0}
    };

    auto neighbours = SquareGeometry::GetNeighboursPositions(origin);

    EXPECT_EQ(neighbours.size(), 8U);

    EXPECT_TRUE(ContainsSquarePosition(neighbours, {
        SquareGeometry::ChunkPosition{-1, -1},
        SquareGeometry::CellPosition{SquareGeometry::size - 1, SquareGeometry::size - 1}
    }));
    EXPECT_TRUE(ContainsSquarePosition(neighbours, {
        SquareGeometry::ChunkPosition{-1, 0},
        SquareGeometry::CellPosition{SquareGeometry::size - 1, 0}
    }));
    EXPECT_TRUE(ContainsSquarePosition(neighbours, {
        SquareGeometry::ChunkPosition{0, -1},
        SquareGeometry::CellPosition{0, SquareGeometry::size - 1}
    }));
    EXPECT_TRUE(ContainsSquarePosition(neighbours, {
        SquareGeometry::ChunkPosition{0, 0},
        SquareGeometry::CellPosition{1, 1}
    }));
}

TEST(GeometriesTest, TriHexGetAllCellPositionsReturnsOnlyValidCells)
{
    auto positions = TriHexGeometry::GetAllCellPositions(TriHexGeometry::ChunkPosition{0, 0, 0});

    ASSERT_FALSE(positions.empty());

    for(const auto& cell : positions)
    {
        EXPECT_TRUE(IsTriHexCellValid(cell));
    }
}

TEST(GeometriesTest, TriHexNeighboursAreNormalizedAndValid)
{
    TriHexGeometry::MinefieldPosition origin{
        TriHexGeometry::ChunkPosition{0, 0, 0},
        TriHexGeometry::CellPosition{TriHexGeometry::size, 0, -TriHexGeometry::size + 1}
    };

    auto neighbours = TriHexGeometry::GetNeighboursPositions(origin);

    EXPECT_EQ(neighbours.size(), 12U);

    bool crossed_chunk_boundary = false;
    for(const auto& pos : neighbours)
    {
        EXPECT_TRUE(IsTriHexCellValid(pos.cell_pos));
        if(pos.chunk_pos != origin.chunk_pos)
        {
            crossed_chunk_boundary = true;
        }
    }

    EXPECT_TRUE(crossed_chunk_boundary);
}

TEST(GeometriesTest, TriHexNeighboursWrapAcrossChunkBoundaries)
{
    TriHexGeometry::MinefieldPosition origin{
        TriHexGeometry::ChunkPosition{0, 0, 0},
        TriHexGeometry::CellPosition{TriHexGeometry::size, -TriHexGeometry::size, 0}
    };

    auto neighbours = TriHexGeometry::GetNeighboursPositions(origin);

    EXPECT_EQ(neighbours.size(), 12U);

    EXPECT_TRUE(ContainsTriHexPosition(neighbours, {
        TriHexGeometry::ChunkPosition{0, 1, -1},
        TriHexGeometry::CellPosition{0, TriHexGeometry::size - 1, -TriHexGeometry::size + 1}
    }));
    EXPECT_TRUE(ContainsTriHexPosition(neighbours, {
        TriHexGeometry::ChunkPosition{1, 0, -1},
        TriHexGeometry::CellPosition{-TriHexGeometry::size + 1, 0, TriHexGeometry::size}
    }));
    EXPECT_TRUE(ContainsTriHexPosition(neighbours, {
        TriHexGeometry::ChunkPosition{1, 0, -1},
        TriHexGeometry::CellPosition{-TriHexGeometry::size + 1, -1, TriHexGeometry::size}
    }));
    EXPECT_TRUE(ContainsTriHexPosition(neighbours, {
        TriHexGeometry::ChunkPosition{1, 0, -1},
        TriHexGeometry::CellPosition{-TriHexGeometry::size + 1, 0, TriHexGeometry::size - 1}
    }));
}