#ifndef INCLUDE_GAME_GAMEMODEL_H_
#define INCLUDE_GAME_GAMEMODEL_H_

#include "game/GeometryConcept.h"
#include "game/IChunkGenerator.h"
#include "game/IChunkStorage.h"
#include "game/IGameModel.h"
#include <memory>

template<Geometry T>
class GameModel : public IGameModel<T>
{
public:
    using CellPosition = typename T::CellPosition;
    using ChunkPosition = typename T::ChunkPosition;
    using MinefieldPosition = typename T::MinefieldPosition;

    GameModel(std::unique_ptr<IChunkGenerator<T>> chunk_generator, std::unique_ptr<IChunkStorage<T>> chunk_storage) :
        m_ChunkGenerator(std::move(chunk_generator)),
        m_ChunkStorage(std::move(chunk_storage))
        {
            m_IsStarted = false;
        }

    SweepResult Sweep(const MinefieldPosition& pos) override
    {
        // Allow to sweep everywhere on first click
        if(!m_IsStarted)
        {
            std::vector<MinefieldPosition> safe_zone = T::GetNeighboursPositions(pos);
            safe_zone.push_back(pos);
            for(const MinefieldPosition& safe_pos : safe_zone)
            {
                std::shared_ptr<IChunk<T>> chunk = GetOrGenerateChunk(safe_pos.chunk_pos);
                ICell* cell = chunk->GetCell(safe_pos.cell_pos);
                if(cell->GetType() == CellType::MINE)
                {
                    cell->SetType(CellType::SAFE);
                }
            }
            SweepZeros(pos);
            m_IsStarted = true;
            return SweepResult::OK;
        }

        // Chech is cell accessible
        if(!IsAccessible(minefield_pos))
        {
            return SweepResult::INACCESSIBLE;
        }

        // Recursively sweep around zeros
        std::shared_ptr<IChunk<T>> chunk = GetOrGenerateChunk(pos.chunk_pos);
        ICell* cell = chunk->GetCell(pos.cell_pos);
        if(CountMinesAround(pos) == 0 && cell->GetType() != CellType::MINE && cell->GetState() == CellState::CLOSED)
        {
            SweepZeros(pos);
            return SweepResult::OK;
        }

        // Process sweep
        SweepResult result = chunk->Sweep(pos.cell_pos);

        // Regenerate chunk if blown
        if(result == SweepResult::BLOWN)
        {
            chunk = m_ChunkGenerator->GenerateChunk(pos.chunk_pos);
            m_ChunkStorage->PushChunk(minefield_pos.chunk_pos, chunk);
        }

        return result;
    }

    FlagResult Flag(const MinefieldPosition& pos) override
    {
        // Check is cell accessible
        if(!IsAccessible(pos))
        {
            return FlagResult::INACCESSIBLE;
        }

        // Process flag
        std::shared_ptr<IChunk<T>> chunk = GetOrGenerateChunk(pos.chunk_pos);
        return chunk->Flag(pos.cell_pos);
    }

    ChunkData GetChunkData(const ChunkPosition& pos) override
    {
        ChunkData<T> data;
        std::shared_ptr<IChunk<T>> chunk = m_ChunkStorage->GetChunk(pos);
        if(!chunk)
        {
            for(const CellPosition& cell_pos : T::GetAllCellPositions(pos))
            {
                CellData<T> cell_data;
                cell_data.pos = MinefieldPosition{.chunk_pos = pos, .cell_pos = cell_pos};
                cell_data.state = CellState::CLOSED;
                cell_data.type = CellType::SAFE;
                cell_data.mines_around = 0;
                data.cells.push_back(cell_data);
            }
        }
        else
        {
            for(const CellPosition& cell_pos : T::GetAllCellPositions(pos))
            {
                CellData<T> cell_data;
                ICell* cell = chunk->GetCell(cell_pos);
                cell_data.pos = MinefieldPosition{.chunk_pos = pos, .cell_pos = cell_pos};
                cell_data.state = cell->SetState();
                cell_data.type = cell->GetType();
                cell_data.mines_around = cell_data.state == CellState::OPENED ? CountMinesAround(cell_data.pos) : 0;
                data.cells.push_back(cell_data);
            }
        }
    }

private:
    std::shared_ptr<IChunk<T>> GetOrGenerateChunk(const ChunkPosition& pos)
    {
        std::shared_ptr<IChunk<T>> chunk = m_ChunkStorage->GetChunk(pos);
        if(!chunk)
        {
            chunk = m_ChunkGenerator->GenerateChunk(pos);
            m_ChunkStorage->PushChunk(pos, chunk);
        }
        return chunk;
    }

    bool IsAccessible(const MinefieldPosition& pos)
    {
        std::vector<MinefieldPosition> neighbours_positions = T::GetNeighboursPositions(pos);
        for(const auto& neighbour_pos : neighbours_positions)
        {
            std::shared_ptr<IChunk<T>> neighbour = m_ChunkStorage->GetChunk(neighbour_pos.chunk_pos);
            if(neighbour && neighbour->GetCell(neighbour_pos.cell_pos)->GetState() == CellState::OPENED)
            {
                return true;
            }
        }
        return false;
    }

    size_t CountMinesAround(const MinefieldPosition& pos)
    {
        std::vector<MinefieldPosition> neighbours_positions = T::GetNeighboursPositions(pos);
        size_t mines = 0;
        for(const auto& neighbour_pos : neighbours_positions)
        {
            std::shared_ptr<IChunk<T>> neighbour = GetOrGenerateChunk(neighbour_pos.chunk_pos);
            if(neighbour->GetCell(neighbour_pos.cell_pos)->GetType() == CellType::MINE)
            {
                mines += 1;
            }
        }
        return mines;
    }

    void SweepZeros(const MinefieldPosition& pos)
    {
        std::shared_ptr<IChunk<T>> chunk = GetOrGenerateChunk(pos.chunk_pos);
        SweepResult result = chunk->Sweep(pos.cell_pos);

        if(CountMinesAround(pos) != 0)
        {
            return;
        }

        if(result == SweepResult::ALREADY_OPENED || result == SweepResult::ALREADY_FLAGGED)
        {
            return;
        }

        for(const auto& neighbour_pos : T::GetNeighboursPositions(pos))
        {
            SweepZeros(neighbour_pos);
        }
    }

    std::unique_ptr<IChunkGenerator<T>> m_ChunkGenerator;
    std::unique_ptr<IChunkStorage<T>> m_ChunkStorage;

    bool m_IsStarted;
};

#endif // INCLUDE_GAME_GAMEMODEL_H_