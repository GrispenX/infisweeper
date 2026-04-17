#include <gtest/gtest.h>
#include "game/Cell.h"

TEST(CellTest, SweepClosedReturnsOkAndChangesState)
{
    Cell cell(CellType::SAFE, CellState::CLOSED);
    SweepResult result = cell.Sweep();
    EXPECT_EQ(result, SweepResult::OK);
    EXPECT_EQ(cell.GetState(), CellState::OPENED);
}

TEST(CellTest, FlagClosedReturnsOkAndChangesState)
{
    Cell cell(CellType::SAFE, CellState::CLOSED);
    FlagResult result = cell.Flag();
    EXPECT_EQ(result, FlagResult::OK);
    EXPECT_EQ(cell.GetState(), CellState::FLAGGED);
}

TEST(CellTest, SweepMineReturnsBlownAndChangesState)
{
    Cell cell(CellType::MINE, CellState::CLOSED);
    SweepResult result = cell.Sweep();
    EXPECT_EQ(result, SweepResult::BLOWN);
    EXPECT_EQ(cell.GetState(), CellState::OPENED);
}

TEST(CellTest, SweepFlaggedDoesntChangeState)
{
    Cell cell(CellType::SAFE, CellState::FLAGGED);
    SweepResult result = cell.Sweep();
    EXPECT_EQ(result, SweepResult::ALREADY_FLAGGED);
    EXPECT_EQ(cell.GetState(), CellState::FLAGGED);
}

TEST(CellTest, SweepOpenedReturnsAlreadyOpened)
{
    Cell cell(CellType::SAFE, CellState::OPENED);
    SweepResult result = cell.Sweep();
    EXPECT_EQ(result, SweepResult::ALREADY_OPENED);
    EXPECT_EQ(cell.GetState(), CellState::OPENED);
}

TEST(CellTest, FlagOpenedReturnsAlreadyOpened)
{
    Cell cell(CellType::SAFE, CellState::OPENED);
    FlagResult result = cell.Flag();
    EXPECT_EQ(result, FlagResult::ALREADY_OPENED);
    EXPECT_EQ(cell.GetState(), CellState::OPENED);
}

TEST(CellTest, FlagFlaggedReturnsToClosed)
{
    Cell cell(CellType::SAFE, CellState::FLAGGED);
    FlagResult result = cell.Flag();
    EXPECT_EQ(result, FlagResult::OK);
    EXPECT_EQ(cell.GetState(), CellState::CLOSED);
}