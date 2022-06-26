#ifndef FlyingObject_h
#define FlyingObject_h

#include "Point.h"
#include "Velocity.h"
#include <stdio.h>

class FlyingObject
{
protected:
    Velocity velocity;
    Point point;
    bool alive;

public:
    Point getPoint() const;
    Velocity getVelocity() const;
    bool isAlive();

    void setPoint(Point);
    void setVelocity(Velocity velocity);
    void setAlive(bool);
    virtual void kill();
    void advance(int);
    virtual void draw() = 0;

};

#endif
