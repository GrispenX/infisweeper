#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include "game/ChunkFileStorage/ChunkFileStorage.h"
#include "game/Geometries.h"
#include "game/Chunk.h"

template<Geometry T>
class MockChunkFactory : public IChunkFactory<T>
{
public:
    MOCK_METHOD(std::unique_ptr<IChunk<T>>, CreateChunk, ((std::unordered_map<typename T::CellPosition, std::unique_ptr<ICell>> cells)), (override));
};

using ::testing::Return;

TEST(ChunkFileStorageTest, InitializesWithValidHeader)
{
    using G = SquareGeometry;

    std::ofstream file("test_file", std::ios::binary);
    Header h;
    h.geometry_id = G::ID;
    file.write(reinterpret_cast<char*>(&h), sizeof(h));
    file.close();

    EXPECT_NO_THROW({
        ChunkFileStorage<G> storage("test_file", nullptr);
    });

    std::filesystem::remove("test_file");
}

TEST(ChunkFileStorageTest, InitializationWithInvalidMagicThrowsException)
{
    using G = SquareGeometry;

    std::ofstream file("test_file", std::ios::binary);
    Header h;
    h.geometry_id = G::ID;
    h.magic[0] = 'X';
    file.write(reinterpret_cast<char*>(&h), sizeof(h));
    file.close();

    EXPECT_THROW({
        ChunkFileStorage<G> storage("test_file", nullptr);
    }, std::runtime_error);

    std::filesystem::remove("test_file");
}

TEST(ChunkFileStorageTest, InitializationWithInvalidGeometryThrowsExpection)
{
    using G = SquareGeometry;

    std::ofstream file("test_file", std::ios::binary);
    Header h;
    h.geometry_id = -1;
    file.write(reinterpret_cast<char*>(&h), sizeof(h));
    file.close();

    EXPECT_THROW({
        ChunkFileStorage<G> storage("test_file", nullptr);
    }, std::runtime_error);

    std::filesystem::remove("test_file");
}

TEST(ChunkFileStorageTest, WriteAndRead)
{
    using G = SquareGeometry;

    std::ofstream file("test_file", std::ios::binary);
    Header h;
    h.geometry_id = G::ID;
    file.write(reinterpret_cast<char*>(&h), sizeof(h));
    file.close();

    std::unique_ptr<MockChunkFactory<G>> factory = std::make_unique<MockChunkFactory<G>>();

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells;
    int t_count = 0, s_count = 0;
    for(auto cell_pos : G::GetAllCellPositions({42, 69}))
    {
        CellType type = t_count % 2 == 0 ? CellType::MINE : CellType::SAFE;
        CellState state = s_count % 3 == 0 ? CellState::CLOSED : s_count % 3 == 1 ? CellState::FLAGGED : CellState::OPENED;
        cells[cell_pos] = std::make_unique<Cell>(type, state);
        t_count++;
        s_count++;
    }

    std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> cells_clone;
    for(auto& [pos, cell] : cells)
    {
        cells_clone[pos] = std::make_unique<Cell>(cell->GetType(), cell->GetState());
    }
    std::shared_ptr<IChunk<G>> chunk = std::make_shared<Chunk<G>>(std::move(cells_clone));

    EXPECT_CALL(*factory, CreateChunk(::testing::_)).WillOnce([&](std::unordered_map<typename G::CellPosition, std::unique_ptr<ICell>> loaded_cells) {
        for(auto& [pos, cell] : loaded_cells)
        {
            EXPECT_EQ(cell->GetType(), cells[pos]->GetType());
            EXPECT_EQ(cell->GetState(), cells[pos]->GetState());
        }
        return std::make_unique<Chunk<G>>(std::move(loaded_cells));
    });

    ChunkFileStorage<G> storage("test_file", std::move(factory));
    storage.PushChunk({42, 69}, chunk);
    storage.GetChunk({42, 69});

    std::filesystem::remove("test_file");
}