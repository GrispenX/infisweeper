#include "UI/NewGameScreen/NewGameView.h"
#include <raylib.h>
#include "raygui.h"
#include <cstring>

void NewGameView::Update()
{
    ResolveUILayout();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiLabel(m_NameLabelBounds, "Name: ");

    int color = GuiGetStyle(DEFAULT, BORDER_COLOR_NORMAL);
    if(m_ShowNameTextBoxError) GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({255, 0, 0, 255}));
    if(GuiTextBox(m_NameTextBoxBounds, m_Name, GuiGetStyle(DEFAULT, TEXT_SIZE), m_NameTextBoxActive))
    {
        m_NameTextBoxActive = !m_NameTextBoxActive;
        m_ShowNameTextBoxError = false;
    }
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, color);

    if(GuiButton(m_ConfirmButtonBounds, "Start"))
    {
        if(strlen(m_Name) == 0) 
        {
            m_ShowNameTextBoxError = true;
        }
        else if(m_GeometryId == 0)
        {
            m_ShowGeometryDropdownError = true;
        }
        else for(auto observer : m_Observers)
        {
            observer->OnCreateGameButton(m_Name, m_GeometryId);
        }
    }

    if(GuiButton(m_BackButtonBounds, "Back"))
    {
        for(auto observer : m_Observers)
        {
            observer->OnBackButton();
        }
    }

    if(m_ShowGeometryDropdownError) GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, ColorToInt({255, 0, 0, 255}));
    if(GuiDropdownBox(m_GeometryDropdownBounds, "Select geometry;Square;Tri-Hex", &m_GeometryId, m_GeometryDropdownActive))
    {
        m_GeometryDropdownActive = !m_GeometryDropdownActive;
        if(m_GeometryId > 0) m_ShowGeometryDropdownError = false;
    }
    GuiSetStyle(DEFAULT, BORDER_COLOR_NORMAL, color);

    EndDrawing();
}

void NewGameView::Subscribe(INewGameViewObserver* observer)
{
    m_Observers.push_back(observer);
}

void NewGameView::ResolveUILayout()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int text_size = GuiGetStyle(DEFAULT, TEXT_SIZE);

    static constexpr int gap = 50;
    static constexpr int gap_between_buttons = 100;
    int y_start = (screen_height - 3 * text_size - 2 * gap) / 2;

    m_NameLabelBounds.height = text_size;
    m_NameLabelBounds.x = (screen_width - m_NameTextBoxBounds.width - m_NameLabelBounds.width) / 2;
    m_NameLabelBounds.y = y_start;

    m_NameTextBoxBounds.height = text_size;
    m_NameTextBoxBounds.x = m_NameLabelBounds.x + m_NameLabelBounds.width;
    m_NameTextBoxBounds.y = y_start;

    m_GeometryDropdownBounds.height = text_size;
    m_GeometryDropdownBounds.x = (screen_width - m_GeometryDropdownBounds.width) / 2;
    m_GeometryDropdownBounds.y = y_start + text_size + gap;

    m_ConfirmButtonBounds.height = text_size;
    m_ConfirmButtonBounds.x = screen_width / 2 + gap_between_buttons / 2;
    m_ConfirmButtonBounds.y = y_start + 2 * (text_size + gap);

    m_BackButtonBounds.height = text_size;
    m_BackButtonBounds.x = screen_width / 2 - m_BackButtonBounds.width - gap_between_buttons / 2;
    m_BackButtonBounds.y  = y_start + 2 * (text_size + gap);
}