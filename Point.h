#ifndef point_h
#define point_h

#include <iostream>

class Point
{
private:
    float x;
    float y;
public:
    Point() :x(0.0), y(0.0) {}
    Point(bool check) :x(0.0), y(0.0) {}
    Point(float x, float y);

    //Accessors
    float getX() const { return x; }
    float getY() const { return y; }

    //setters 
    void setX(float x);
    void setY(float y);

    void addX(float dx)
    {
        setX(getX() + dx);
    }

    void addY(float dy)
    {
        setX(getY() + dy);
    }

};

std::ostream& operator << (std::ostream& out, const Point& pt);
std::istream& operator >> (std::istream& in, Point& pt);

#endif 
