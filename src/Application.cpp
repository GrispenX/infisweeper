#include "Application.h"

Application::Application(std::unique_ptr<IScreen> initial_scene) :
    m_Scene(std::move(initial_scene))
{}

void Application::Run()
{
    // Init window

    while(true) // !WindowShouldClose()
    {
        std::unique_ptr<IScreen> next_scene = m_Scene->Update();
        if(next_scene)
        {
            m_Scene = std::move(next_scene);
        }
    }
}