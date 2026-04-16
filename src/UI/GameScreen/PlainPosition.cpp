#include "UI/GameScreen/PlainPosition.h"

PlainPosition PlainPosition::operator+(const PlainPosition& other) const
{
    return {x + other.x, y + other.y};
}

PlainPosition PlainPosition::operator-(const PlainPosition& other) const
{
    return {x - other.x, y - other.y};
}

PlainPosition PlainPosition::operator*(const double m) const
{
    return {x * m, y * m};
}

PlainPosition PlainPosition::operator/(const double d) const
{
    return {x / d, y / d};
}