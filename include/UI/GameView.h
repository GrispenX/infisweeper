#ifndef INCLUDE_GAMEVIEW_H_
#define INCLUDE_GAMEVIEW_H_

#include "UI/IGameView.h"
#include "UI/IAssetManager.h"
#include <vector>
#include <raylib.h>

class GameView : public IGameView
{
public:
    GameView(std::shared_ptr<IAssetManager> asset_manager);

    std::pair<PlainPosition, PlainPosition> GetVisibleMinefieldCorners() override;
    void Update() override;
    void Draw(const std::vector<ChunkViewData>& data) override;
    void Subscribe(IGameViewObserver* observer) override;

private:
    void DrawCell(const CellViewData& cell_data);
    void DrawChunk(const ChunkViewData& chunk_data);
    
    std::vector<IGameViewObserver*> m_Observers;
    PlainPosition m_Position;
    double m_Zoom;

    std::shared_ptr<IAssetManager> m_AssetManager;

    Vector2 PlainToScreen(const PlainPosition& pos);
    PlainPosition ScreenToPlain(const Vector2& pos);
};

#endif // INCLUDE_GAMEVIEW_H_