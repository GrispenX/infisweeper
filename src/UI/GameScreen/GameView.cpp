#include "UI/GameScreen/GameView.h"
#include "UI/AssetManager.h"
#include <iostream>

GameView::GameView() :
    m_Position({0, 0}),
    m_Zoom(100.0)
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
        for(auto observer : m_Observers)
        {
            observer->OnSweep(mouse_pos);
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_RIGHT))
    {
        PlainPosition mouse_pos = ScreenToPlain(GetMousePosition());
        for(auto observer : m_Observers)
        {
            observer->OnFlag(mouse_pos);
        }
    }
    if(IsMouseButtonPressed(MOUSE_BUTTON_SIDE))
    {
        for(auto observer : m_Observers)
        {
            observer->OnBackButton();
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

        if (wheel > 0) m_Zoom *= 1.1; 
        else m_Zoom /= 1.1;

        if (m_Zoom < 10) m_Zoom = 10;
        if (m_Zoom > 1000.0) m_Zoom = 1000.0;

        PlainPosition mouse_world_after = ScreenToPlain(GetMousePosition());

        m_Position.x += (mouse_plain_before.x - mouse_world_after.x);
        m_Position.y += (mouse_plain_before.y - mouse_world_after.y);
    }
}

void GameView::DrawCell(const CellViewData& cell_data)
{
    Texture cell_texture = AssetManager::Instance().GetTexture(cell_data.texture_id);
    Font cell_font = AssetManager::Instance().GetFont(FontID::DEFAULT, 100);
    Vector2 screen_pos = PlainToScreen(cell_data.center_pos);

    Rectangle source {
        .x = 0,
        .y = 0,
        .width = (float)cell_texture.width,
        .height = (float)cell_texture.height
    };

    Rectangle dest {
        .x = screen_pos.x,
        .y = screen_pos.y,
        .width = (float)(cell_data.size * m_Zoom),
        .height = (float)(cell_data.size * m_Zoom)
    };

    Vector2 origin {
        .x = dest.width / 2.0f,
        .y = dest.height / 2.0f
    };

    Color tint = cell_data.state == CellState::OPENED ? Color{200, 200, 200, 255} : Color{100, 100, 100, 255};

    DrawTexturePro(cell_texture, source, dest, origin, cell_data.rotation, tint);

    if(cell_data.state == CellState::OPENED && cell_data.mines_around > 0)
    {
        std::string text = std::to_string(cell_data.mines_around);
        float font_size = 0.5f * (float)m_Zoom;
        Vector2 text_size = MeasureTextEx(cell_font, text.c_str(), font_size, 0.5f);
        DrawTextPro(cell_font, std::to_string(cell_data.mines_around).c_str(), screen_pos, {text_size.x / 2.0f, text_size.y / 2.0f}, 0.0f, font_size, 0.5f, BLACK);
    }

    if(cell_data.state == CellState::FLAGGED)
    {
        Texture flag_texture = AssetManager::Instance().GetTexture(TextureID::FLAG);
        source.width = flag_texture.width;
        source.height = flag_texture.height;
        DrawTexturePro(flag_texture, source, dest, origin, 0, {200, 0, 0, 255});
    }
}

void GameView::DrawChunk(const ChunkViewData& chunk_data)
{
    for(const auto& cell_data : chunk_data.cells)
    {
        DrawCell(cell_data);
    }

    for(const auto& boundary : chunk_data.boundaries)
    {
        DrawLineEx(PlainToScreen(boundary.first), PlainToScreen(boundary.second), 0.06 * m_Zoom, RED);
    }
}

void GameView::Draw(const std::vector<ChunkViewData>& data)
{
    BeginDrawing();
    ClearBackground(DARKGRAY);

    for(const auto& chunk : data)
    {
        DrawChunk(chunk);
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