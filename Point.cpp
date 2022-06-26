#include "Point.h"

Point::Point(float x, float y) : x(0.0), y(0.0)
{
    setX(x);
    setY(y);
}

void Point::setX(float x)
{
    this->x = x;
}
void Point::setY(float y)
{
    this->y = y;
}

std::ostream& operator <<(std::ostream& out, Point& pt)
{
    out << "(" << pt.getX() << "," << pt.getY() << ")";
    return out;
}

std::istream& operator >> (std::istream& in, Point& pt)
{
    float x;
    float y;
    in >> x >> y;

    pt.setX(x);
    pt.setY(y);

    return in;
}