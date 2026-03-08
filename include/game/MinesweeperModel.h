#ifndef INCLUDE_GAME_GAMEMANAGER_H_
#define INCLUDE_GAME_GAMEMANAGER_H_

#include "game/GeometryConcept.h"
#include "game/IChunkGenerator.h"
#include "game/IChunkStorage.h"
#include "game/IMinesweeperModel.h"
#include <memory>

template<Geometry TGeometry>
class MinesweeperModel : public IMinesweeperModel
{
public:
    MinesweeperModel(std::unique_ptr<IChunkGenerator> chunk_generator, std::shared_ptr<IChunkStorage<TGeometry>> chunk_storage) :
        m_ChunkGenerator(std::move(chunk_generator)),
        m_ChunkStorage(chunk_storage)
        {
            m_IsStarted = false;
        }

    SweepResult Sweep(const PlainPosition& pos) override
    {
        typename TGeometry::MinefieldPosition minefield_pos = TGeometry::PlainToMinefield(pos);

        // Allow to sweep everywhere on first click
        if(!m_IsStarted)
        {
            std::vector<typename TGeometry::MinefieldPosition> safe_zone = TGeometry::GetNeighboursPositions(minefield_pos);
            safe_zone.push_back(minefield_pos);
            for(const auto& safe_pos : safe_zone)
            {
                std::shared_ptr<IChunk> chunk = GetOrGenerateChunk(safe_pos.chunk_pos);
                size_t index = TGeometry::MinefieldToIndex(safe_pos);
                ICell* cell = chunk->GetCell(index);
                if(cell->GetType() == CellType::MINE)
                {
                    cell->SetType(CellType::SAFE);
                }
            }
            SweepZeros(minefield_pos);
            m_IsStarted = true;
            return SweepResult::OK;
        }

        // Chech is cell accessible
        if(!IsAccessible(minefield_pos))
        {
            return SweepResult::INACCESSIBLE;
        }

        // Recursively sweep around zeros
        std::shared_ptr<IChunk> chunk = GetOrGenerateChunk(minefield_pos.chunk_pos);
        size_t index = TGeometry::MinefieldToIndex(minefield_pos);
        ICell* cell = chunk->GetCell(index);
        if(CountMinesAround(minefield_pos) == 0 && cell->GetType() != CellType::MINE && cell->GetState() == CellState::CLOSED)
        {
            SweepZeros(minefield_pos);
            return SweepResult::OK;
        }

        // Process sweep
        SweepResult result = chunk->Sweep(index);

        // Regenerate chunk if blown
        if(result == SweepResult::BLOWN)
        {
            chunk = m_ChunkGenerator->GenerateChunk(typename TGeometry::ChunkPositionHasher()(minefield_pos.chunk_pos), TGeometry::CellsAmount(minefield_pos.chunk_pos));
            m_ChunkStorage->PushChunk(minefield_pos.chunk_pos, chunk);
        }

        return result;
    }

    FlagResult Flag(const PlainPosition& pos) override
    {
        // Check is cell accessible
        typename TGeometry::MinefieldPosition minefield_pos = TGeometry::PlainToMinefield(pos);
        if(!IsAccessible(minefield_pos))
        {
            return FlagResult::INACCESSIBLE;
        }

        // Process flag
        std::shared_ptr<IChunk> chunk = GetOrGenerateChunk(minefield_pos.chunk_pos);
        size_t index = TGeometry::MinefieldToIndex(minefield_pos);
        return chunk->Flag(index);
    }

private:
    std::shared_ptr<IChunk> GetOrGenerateChunk(const typename TGeometry::ChunkPosition& pos)
    {
        std::shared_ptr<IChunk> chunk = m_ChunkStorage->GetChunk(pos);
        if(!chunk)
        {
            chunk = m_ChunkGenerator->GenerateChunk(typename TGeometry::ChunkPositionHasher()(pos), TGeometry::CellsAmount(pos));
            m_ChunkStorage->PushChunk(pos, chunk);
        }
        return chunk;
    }

    bool IsAccessible(const typename TGeometry::MinefieldPosition& pos)
    {
        std::vector<typename TGeometry::MinefieldPosition> neighbours_positions = TGeometry::GetNeighboursPositions(pos);
        for(const auto& neighbour_pos : neighbours_positions)
        {
            std::shared_ptr<IChunk> neighbour = m_ChunkStorage->GetChunk(neighbour_pos.chunk_pos);
            if(neighbour && neighbour->GetCell(TGeometry::MinefieldToIndex(neighbour_pos))->GetState() == CellState::OPENED)
            {
                return true;
            }
        }
        return false;
    }

    size_t CountMinesAround(const typename TGeometry::MinefieldPosition& pos)
    {
        std::vector<typename TGeometry::MinefieldPosition> neighbours_positions = TGeometry::GetNeighboursPositions(pos);
        size_t mines = 0;
        for(const auto& neighbour_pos : neighbours_positions)
        {
            std::shared_ptr<IChunk> neighbour = GetOrGenerateChunk(neighbour_pos.chunk_pos);
            size_t index = TGeometry::MinefieldToIndex(neighbour_pos);
            if(neighbour->GetCell(index)->GetType() == CellType::MINE)
            {
                mines += 1;
            }
        }
        return mines;
    }

    void SweepZeros(const typename TGeometry::MinefieldPosition& pos)
    {
        std::shared_ptr<IChunk> chunk = GetOrGenerateChunk(pos.chunk_pos);
        size_t index = TGeometry::MinefieldToIndex(pos);
        SweepResult result = chunk->Sweep(index);

        if(CountMinesAround(pos) != 0)
        {
            return;
        }

        if(result == SweepResult::ALREADY_OPENED || result == SweepResult::ALREADY_FLAGGED)
        {
            return;
        }

        for(const auto& neighbour_pos : TGeometry::GetNeighboursPositions(pos))
        {
            SweepZeros(neighbour_pos);
        }
    }

    std::unique_ptr<IChunkGenerator> m_ChunkGenerator;
    std::shared_ptr<IChunkStorage<TGeometry>> m_ChunkStorage;

    bool m_IsStarted;
};

#endif // INCLUDE_GAME_GAMEMANAGER_H_