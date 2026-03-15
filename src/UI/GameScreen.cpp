#include "UI/GameScreen.h"

GameScreen::GameScreen(std::unique_ptr<IGameView> view, std::unique_ptr<IGameModel> model) :
    m_View(std::move(view)),
    m_Model(std::move(model))
{
    m_View->Subscribe(this);
}

std::unique_ptr<IScreen> GameScreen::Update()
{
    m_View->Update();
    
    std::pair<PlainPosition, PlainPosition> corners = m_View->GetVisibleMinefieldCorners();
    ViewportData data = m_Model->GetCellsInRectangle(corners.first, corners.second);
    m_View->Draw(data);
    return nullptr;
}

void GameScreen::OnMinefieldLeftClick(const PlainPosition& pos)
{
    m_Model->Sweep(pos);
}

void GameScreen::OnMinefieldRightClick(const PlainPosition& pos)
{
    m_Model->Flag(pos);
}