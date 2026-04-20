#ifndef INCLUDE_APPLICATION_H_
#define INCLUDE_APPLICATION_H_

#include <UI/IScreen.h>
#include <memory>

class Application
{
public:
    Application(std::unique_ptr<IScreen> initial_screen);

    void Run();

private:
    std::unique_ptr<IScreen> m_Screen;
};

#endif // INCLUDE_APPLICATION_H_