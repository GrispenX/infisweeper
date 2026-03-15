#ifndef INCLUDE_APPLICATION_H_
#define INCLUDE_APPLICATION_H_

#include <UI/IScreen.h>
#include <memory>

class Application
{
public:
    Application(std::unique_ptr<IScreen> initial_scene);

    void Run();

private:
    std::unique_ptr<IScreen> m_Scene;
};

#endif // INCLUDE_APPLICATION_H_