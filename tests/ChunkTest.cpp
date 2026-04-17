#include <gtest/gtest.h>

#include <memory>
#include <unordered_map>

#include "game/Cell.h"
#include "game/Chunk.h"
#include "game/Geometries.h"

TEST(ChunkTest, SweepDelegatesToUnderlyingCell)
{
    std::unordered_map<SquareGeometry::CellPosition, std::unique_ptr<ICell>> cells;
    cells.emplace(SquareGeometry::CellPosition{0, 0}, std::make_unique<Cell>(CellType::SAFE, CellState::CLOSED));

    Chunk<SquareGeometry> chunk(std::move(cells));

    SweepResult result = chunk.Sweep(SquareGeometry::CellPosition{0, 0});

    EXPECT_EQ(result, SweepResult::OK);
    ASSERT_NE(chunk.GetCell(SquareGeometry::CellPosition{0, 0}), nullptr);
    EXPECT_EQ(chunk.GetCell(SquareGeometry::CellPosition{0, 0})->GetState(), CellState::OPENED);
}

TEST(ChunkTest, FlagDelegatesToUnderlyingCell)
{
    std::unordered_map<SquareGeometry::CellPosition, std::unique_ptr<ICell>> cells;
    cells.emplace(SquareGeometry::CellPosition{2, 3}, std::make_unique<Cell>(CellType::SAFE, CellState::CLOSED));

    Chunk<SquareGeometry> chunk(std::move(cells));

    FlagResult result = chunk.Flag(SquareGeometry::CellPosition{2, 3});

    EXPECT_EQ(result, FlagResult::OK);
    ASSERT_NE(chunk.GetCell(SquareGeometry::CellPosition{2, 3}), nullptr);
    EXPECT_EQ(chunk.GetCell(SquareGeometry::CellPosition{2, 3})->GetState(), CellState::FLAGGED);
}

TEST(ChunkTest, GetCellReturnsStoredCell)
{
    std::unordered_map<SquareGeometry::CellPosition, std::unique_ptr<ICell>> cells;
    cells.emplace(SquareGeometry::CellPosition{4, 4}, std::make_unique<Cell>(CellType::MINE, CellState::CLOSED));

    Chunk<SquareGeometry> chunk(std::move(cells));

    ICell* cell = chunk.GetCell(SquareGeometry::CellPosition{4, 4});

    ASSERT_NE(cell, nullptr);
    EXPECT_EQ(cell->GetType(), CellType::MINE);
    EXPECT_EQ(cell->GetState(), CellState::CLOSED);
}
