#ifndef INCLUDE_UI_PLAINPOSITION_H_
#define INCLUDE_UI_PLAINPOSITION_H_

struct PlainPosition
{
    double x;
    double y;

    PlainPosition operator+(const PlainPosition& other) const;
    PlainPosition operator-(const PlainPosition& other) const;
    PlainPosition operator*(const double m) const;
    PlainPosition operator/(const double d) const;
};

#endif // INCLUDE_UI_PLAINPOSITION_H_