#ifndef INCLUDE_GAMESCREEN_H_
#define INCLUDE_GAMESCREEN_H_

#include "game/GeometryConcept.h"
#include "UI/IScreen.h"
#include "UI/GameScreen/IGameView.h"
#include "UI/GameScreen/IGameViewObserver.h"
#include "game/IGameModel.h"

template<Geometry T>
class GameScreen : public IScreen, public IGameViewObserver
{
public:
    GameScreen(std::unique_ptr<IGameView> view, std::unique_ptr<IGameModel<T>> model) :
        m_View(std::move(view)),
        m_Model(std::move(model))
    {
        m_View->Subscribe(this);
    }

    std::unique_ptr<IScreen> Update() override
    {
        m_View->Update();
        std::pair<PlainPosition, PlainPosition> corners = m_View->GetVisibleMinefieldCorners();
        std::vector<ChunkPosition> chunk_positions = GetChunksInRectangle(corners.first, corners.second);
        std::vector<ChunkViewData> chunks_view_data;
        for(const ChunkPosition& chunk_pos : chunk_positions)
        {
            ChunkData<T> chunk_data = m_Model->GetChunkData(chunk_pos);
            ChunkViewData chunk_view_data;
            chunk_view_data.boundaries = GetChunkBoundaries(chunk_pos);
            for(const CellData<T>& cell : chunk_data.cells)
            {
                MinefieldPosition minefield_pos{.chunk_pos = chunk_pos, .cell_pos = cell.pos};
                CellViewData cell_view_data;

                cell_view_data.type = cell.type;
                cell_view_data.state = cell.state;
                cell_view_data.mines_around = cell.mines_around;
                cell_view_data.center_pos = GetCellCenterPos(minefield_pos);
                cell_view_data.size = GetCellSize(minefield_pos);
                cell_view_data.rotation = GetCellRotation(minefield_pos);
                cell_view_data.shape = GetCellShape(minefield_pos);

                chunk_view_data.cells.push_back(cell_view_data);
            }
            chunks_view_data.push_back(chunk_view_data);
        }
        m_View->Draw(chunks_view_data);
        return nullptr;
    }

    void OnMinefieldLeftClick(const PlainPosition& pos) override
    {
        m_Model->Sweep(PlainToMinefield(pos));
    }
    void OnMinefieldRightClick(const PlainPosition& pos) override
    {
        m_Model->Flag(PlainToMinefield(pos));
    }

private:
    std::unique_ptr<IGameView> m_View;
    std::unique_ptr<IGameModel<T>> m_Model;

    using CellPosition = typename T::CellPosition;
    using ChunkPosition = typename T::ChunkPosition;
    using MinefieldPosition = typename T::MinefieldPosition;

    MinefieldPosition PlainToMinefield(const PlainPosition& pos);
    PlainPosition GetCellCenterPos(const MinefieldPosition& pos);
    double GetCellSize(const MinefieldPosition& pos);
    double GetCellRotation(const MinefieldPosition& pos);
    CellShape GetCellShape(const MinefieldPosition& pos);
    std::vector<ChunkPosition> GetChunksInRectangle(const PlainPosition& pos1, const PlainPosition& pos2);
    std::vector<std::pair<PlainPosition, PlainPosition>> GetChunkBoundaries(const ChunkPosition& pos);
};

#endif // INCLUDE_GAMESCREEN_H_