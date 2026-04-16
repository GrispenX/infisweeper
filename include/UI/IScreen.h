#ifndef INCLUDE_UI_ISCREEN_H_
#define INCLUDE_UI_ISCREEN_H_

#include <memory>

class IScreen
{
public:
    virtual ~IScreen() = default;

    virtual std::unique_ptr<IScreen> Update() = 0;
};

#endif // INCLUDE_UI_ISCREEN_H_