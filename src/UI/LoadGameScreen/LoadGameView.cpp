#include "UI/LoadGameScreen/LoadGameView.h"
#include <raylib.h>
#include "raygui.h"

void LoadGameView::Update()
{
    ResolveUILayout();

    BeginDrawing();
    ClearBackground(GetColor(GuiGetStyle(DEFAULT, BACKGROUND_COLOR)));

    GuiScrollPanel(m_FileSelectorBounds, "Select save", m_FileSelectorContent, &m_FileSelectorScroll, &m_FileSelectorView);

    BeginScissorMode(m_FileSelectorView.x, m_FileSelectorView.y, m_FileSelectorView.width, m_FileSelectorView.height);
    int i = 0;
    int text_size = GuiGetStyle(DEFAULT, TEXT_SIZE);
    for(const auto& [path, header] : m_SaveFiles)
    {
        std::string geom = header.geometry_id == 1 ? "Square" : "Tri-Hex";
        Rectangle button_bounds {
            .x = m_FileSelectorView.x + m_FileSelectorScroll.x + 0.25f * m_FileSelectorEntrySize,
            .y = m_FileSelectorView.y + i * m_FileSelectorEntrySize + m_FileSelectorScroll.y + 0.25f * m_FileSelectorEntrySize,
            .width = 0.5f * m_FileSelectorEntrySize,
            .height = 0.5f * m_FileSelectorEntrySize
        };
        bool checked = path == m_SelectedPath;
        if(GuiCheckBox(button_bounds, (path.filename().string() + " (" + geom + ")").c_str(), &checked)) m_SelectedPath = path;
        i++;
    }
    EndScissorMode();

    if(GuiButton(m_ConfirmButtonBounds, "Load"))
    {
        for(auto observer : m_Observers)
        {
            observer->OnLoadButton(m_SelectedPath);
        }
    }
    if(GuiButton(m_BackButtonBounds, "Back"))
    {
        for(auto observer : m_Observers)
        {
            observer->OnBackButton();
        }
    }

    EndDrawing();
}

void LoadGameView::Subscribe(ILoadGameViewObserver* observer)
{
    m_Observers.push_back(observer);
}

void LoadGameView::SetSaveFiles(std::unordered_map<std::filesystem::path, Header>& files)
{
    m_SaveFiles = files;
    m_SelectedPath = files.begin()->first;
}


void LoadGameView::ResolveUILayout()
{
    int screen_width = GetScreenWidth();
    int screen_height = GetScreenHeight();
    int text_size = GuiGetStyle(DEFAULT, TEXT_SIZE);

    m_FileSelectorEntrySize = text_size;

    static constexpr int gap_from_screen_edge = 100;
    static constexpr int gap_betwween_buttons = 100;
    static constexpr int gap_between_panel_and_buttons = 50;

    m_FileSelectorBounds.height = screen_height - gap_from_screen_edge * 2 - gap_between_panel_and_buttons - text_size;
    m_FileSelectorBounds.x = (screen_width - m_FileSelectorBounds.width) / 2;
    m_FileSelectorBounds.y = gap_from_screen_edge;

    m_FileSelectorContent.height = m_SaveFiles.size() * m_FileSelectorEntrySize;

    m_ConfirmButtonBounds.x = screen_width / 2 - m_ConfirmButtonBounds.width - gap_betwween_buttons / 2;
    m_ConfirmButtonBounds.y = screen_height - gap_from_screen_edge - text_size;

    m_BackButtonBounds.x = screen_width / 2 + gap_betwween_buttons / 2;
    m_BackButtonBounds.y = screen_height - gap_from_screen_edge - text_size;
}