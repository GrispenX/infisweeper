#ifndef INCLUDE_ISCREEN_H_
#define INCLUDE_ISCREEN_H_

#include <memory>

class IScreen
{
public:
    ~IScreen() = default;

    virtual std::unique_ptr<IScreen> Update() = 0;
};

#endif // INCLUDE_ISCREEN_H_