#include "UI/GameView.h"
#include <iostream>

GameView::GameView(Texture2D cell) :
    m_Position({0, 0}),
    m_Zoom(1.0),
    m_CellTexture(cell) // TEMP
{}

std::pair<PlainPosition, PlainPosition> GameView::GetVisibleMinefieldCorners()
{
    Vector2 top_left_screen = {0, 0};
    Vector2 bottom_right_screen = {(float)GetScreenWidth(), (float)GetScreenHeight()};
    
    PlainPosition top_left_plain = ScreenToPlain(top_left_screen);
    PlainPosition bottom_right_plain = ScreenToPlain(bottom_right_screen);

    return std::make_pair(top_left_plain, bottom_right_plain);
}

void GameView::Update()
{
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
    {
        PlainPosition mouse_pos = ScreenToPlain(GetMousePosition());
        for(auto& observer : m_Observers)
        {
            observer->OnMinefieldLeftClick(mouse_pos);
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        PlainPosition mouse_pos = ScreenToPlain(GetMousePosition());
        for(auto& observer : m_Observers)
        {
            observer->OnMinefieldRightClick(mouse_pos);
        }
    }

    // Movement
    if(IsMouseButtonDown(MOUSE_BUTTON_MIDDLE))
    {
        Vector2 delta = GetMouseDelta();
        m_Position.x -= delta.x / m_Zoom;
        m_Position.y -= delta.y / m_Zoom;
    }

    // Zoom
    float wheel = GetMouseWheelMove();
    if(wheel != 0)
    {
        PlainPosition mouse_plain_before = ScreenToPlain(GetMousePosition());

        if (wheel > 0) m_Zoom += 5; 
        else m_Zoom -= 5;

        if (m_Zoom < 5) m_Zoom = 5;
        if (m_Zoom > 1000.0) m_Zoom = 1000.0;

        PlainPosition mouse_world_after = ScreenToPlain(GetMousePosition());

        m_Position.x += (mouse_plain_before.x - mouse_world_after.x);
        m_Position.y += (mouse_plain_before.y - mouse_world_after.y);
    }
}

void GameView::Draw(const std::vector<ChunkViewData>& data)
{
    BeginDrawing();
    ClearBackground(DARKGREEN);

    std::cout << "FPS:      " << GetFPS() << "\n";
    std::cout << "Zoom:     " << m_Zoom << "\n";
    std::cout << "Position: " << m_Position.x << "\t" << m_Position.y << "\n\n";

    for(const auto& chunk : data)
    {
        for(const auto& cell : chunk.cells)
        {
            Rectangle source;
            source.x = 0;
            source.y = 0;
            source.width = m_CellTexture.width;
            source.height = m_CellTexture.height;
            Vector2 center = PlainToScreen(cell.center_pos);
            Rectangle dest;
            dest.x = center.x;
            dest.y = center.y;
            dest.width = cell.size * m_Zoom;
            dest.height = cell.size * m_Zoom;
            Vector2 origin;
            origin.x = dest.width / 2;
            origin.y = dest.height / 2;

            Color tint = cell.state == CellState::CLOSED ? DARKGRAY : WHITE;
            
            DrawTexturePro(m_CellTexture, source, dest, origin, cell.rotation, tint);

            if(cell.state == CellState::FLAGGED) DrawText("F", (int)dest.x, (int)dest.y, 14, LIME);
            else if(cell.state == CellState::OPENED && cell.mines_around > 0) DrawText(std::to_string(cell.mines_around).c_str(), (int)dest.x, (int)dest.y, 14, BLACK);
        }

        for(const auto& boundary : chunk.boundaries)
        {
            DrawLineEx(PlainToScreen(boundary.first), PlainToScreen(boundary.second), 5, RED);
        }
    }

    EndDrawing();
}

void GameView::Subscribe(IGameViewObserver* observer)
{
    m_Observers.push_back(observer);
}

Vector2 GameView::PlainToScreen(const PlainPosition& pos)
{
    float screen_width = (float)GetScreenWidth();
    float screen_height = (float)GetScreenHeight();

    float x = (float)((pos.x - m_Position.x) * m_Zoom + screen_width / 2.0f);
    float y = (float)((pos.y - m_Position.y) * m_Zoom + screen_height / 2.0f);

    return Vector2{x, y};
}

PlainPosition GameView::ScreenToPlain(const Vector2& pos)
{
    float screen_width = (float)GetScreenWidth();
    float screen_height = (float)GetScreenHeight();

    double x = (double)((pos.x - screen_width / 2.0f) / m_Zoom + m_Position.x);
    double y = (double)((pos.y - screen_height / 2.0f) / m_Zoom + m_Position.y);

    return PlainPosition{x, y};
}