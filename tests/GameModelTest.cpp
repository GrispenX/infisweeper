#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "game/GameModel.h"
#include "game/IChunkStorage.h"
#include "game/IChunkGenerator.h"
#include "game/Chunk.h"
#include "game/Cell.h"

#include "game/Geometries.h"

using ::testing::Return;
using ::testing::ByMove;

template<Geometry T>
class MockChunkStorage : public IChunkStorage<T>
{
public:
    MOCK_METHOD(std::shared_ptr<IChunk<T>>, GetChunk, (const typename T::ChunkPosition& chunk_pos), (override));
    MOCK_METHOD((std::unordered_map<typename T::ChunkPosition, std::shared_ptr<IChunk<T>>>), GetAllChunks, (), (override));
    MOCK_METHOD(void, PushChunk, (const typename T::ChunkPosition& chunk_pos, std::shared_ptr<IChunk<T>> chunk), (override));
};

template<Geometry T>
class MockChunkGenerator : public IChunkGenerator<T>
{
public:
    MOCK_METHOD(std::unique_ptr<IChunk<T>>, GenerateChunk, (const typename T::ChunkPosition& chunk_pos), (override));
};



TEST(GameModelTest, SweepOnUngeneratedAreaReturnsInaccessible)
{
    using G = SquareGeometry;
    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).Times(3).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{-1, -1})).Times(1).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{-1, 0})).Times(2).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, -1})).Times(2).WillRepeatedly(Return(nullptr));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Sweep(G::MinefieldPosition{{0, 0}, {0, 0}}), SweepResult::INACCESSIBLE);
}

TEST(GameModelTest, SweepOnMineRegeneratesChunkAndReturnsBlown)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(CellType::SAFE, CellState::OPENED);
    }
    cells[{5, 5}] = std::make_unique<Cell>(CellType::MINE, CellState::CLOSED);
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));
    std::unique_ptr<IChunk<G>> new_chunk = std::make_unique<Chunk<G>>(std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>>{});
    IChunk<G>* new_chunk_ptr = new_chunk.get();

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));
    EXPECT_CALL(*gen, GenerateChunk(G::ChunkPosition{0, 0})).WillOnce(Return(ByMove(std::move(new_chunk))));
    EXPECT_CALL(*storage, PushChunk(G::ChunkPosition{0, 0}, ::testing::_)).WillOnce(
        [new_chunk_ptr](const typename G::ChunkPosition& pos, std::shared_ptr<IChunk<G>> ptr) {
            EXPECT_EQ(ptr.get(), new_chunk_ptr);
        }
    );

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Sweep(G::MinefieldPosition{{0, 0}, {5, 5}}), SweepResult::BLOWN);
}

TEST(GameModelTest, SweepOnSafePlaceReturnsOK)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();
    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(CellType::MINE, CellState::CLOSED);
    }
    cells[{5, 5}] = std::make_unique<Cell>(CellType::SAFE, CellState::CLOSED);
    cells[{5, 4}] = std::make_unique<Cell>(CellType::SAFE, CellState::OPENED);
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Sweep(G::MinefieldPosition{{0, 0}, {5, 5}}), SweepResult::OK);
}

TEST(GameModelTest, SweepOnZerosOpensAllAreaAndReturnsOK)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    CellType type_mask[10][10] {
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::SAFE, CellType::SAFE, CellType::SAFE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE },
        { CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE, CellType::MINE }
    };

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(type_mask[cell_pos.row][cell_pos.col], CellState::CLOSED);
    }
    cells[{6, 5}] = std::make_unique<Cell>(CellType::SAFE, CellState::OPENED);
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Sweep(G::MinefieldPosition{{0, 0}, {5, 5}}), SweepResult::OK);

    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        CellState state = chunk->GetCell(cell_pos)->GetState();
        if(type_mask[cell_pos.row][cell_pos.col] == CellType::MINE) EXPECT_EQ(state, CellState::CLOSED);
        else EXPECT_EQ(state, CellState::OPENED);
    }
}

TEST(GameModelTest, FirstSweepCreatesSafeAreaAndReturnsOK)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(CellType::MINE, CellState::CLOSED);
    }
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));
    IChunk<G>* chunk_ptr;

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));

    GameModel<G> model(std::move(gen), std::move(storage), false);

    EXPECT_EQ(model.Sweep(G::MinefieldPosition{{0, 0}, {5, 5}}), SweepResult::OK);

    ICell* cell = chunk->GetCell({5, 5});
    EXPECT_EQ(cell->GetState(), CellState::OPENED);
    EXPECT_NE(cell->GetType(), CellType::MINE);

    auto neighbours = G::GetNeighboursPositions({{0, 0}, {5, 5}});
    
    for(const auto& n : neighbours)
    {
        ICell* ncell = chunk->GetCell(n.cell_pos);
        EXPECT_EQ(ncell->GetState(), CellState::OPENED);
        EXPECT_NE(ncell->GetType(), CellType::MINE);
    }
}

TEST(GameModelTest, FlagOnUngeneratedAreaReturnsInaccessible)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{-1, 0})).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, -1})).WillRepeatedly(Return(nullptr));
    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{-1, -1})).WillRepeatedly(Return(nullptr));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Flag({{0, 0}, {0, 0}}), FlagResult::INACCESSIBLE);
}

TEST(GameModelTest, FlagOnInaccessibleAreaReturnsInaccessible)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(CellType::SAFE, CellState::CLOSED);
    }
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Flag({{0, 0}, {5, 5}}), FlagResult::INACCESSIBLE);
}

TEST(GameModelTest, FlagOnAccessibleAreaReturnsOK)
{
    using G = SquareGeometry;

    std::unique_ptr<MockChunkStorage<G>> storage = std::make_unique<MockChunkStorage<G>>();
    std::unique_ptr<MockChunkGenerator<G>> gen = std::make_unique<MockChunkGenerator<G>>();

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    for(auto cell_pos : G::GetAllCellPositions({0, 0}))
    {
        cells[cell_pos] = std::make_unique<Cell>(CellType::SAFE, CellState::CLOSED);
    }
    cells[{4, 5}] = std::make_unique<Cell>(CellType::SAFE, CellState::OPENED);
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells));

    EXPECT_CALL(*storage, GetChunk(G::ChunkPosition{0, 0})).WillRepeatedly(Return(chunk));

    GameModel<G> model(std::move(gen), std::move(storage), true);

    EXPECT_EQ(model.Flag({{0, 0}, {5, 5}}), FlagResult::OK);
}