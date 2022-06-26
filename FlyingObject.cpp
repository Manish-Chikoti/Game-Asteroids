#include "FlyingObject.h"
#include "Velocity.h"
#include "Point.h"

Point FlyingObject::getPoint() const
{
    return point;
}

Velocity FlyingObject::getVelocity() const
{
    return velocity;
}

bool FlyingObject::isAlive()
{
    return alive;
}

void FlyingObject::setPoint(Point point)
{
    this->point = point;
}

void FlyingObject::setVelocity(Velocity velocity)
{
    this->velocity = velocity;
}

void FlyingObject::setAlive(bool alive)
{
    this->alive = alive;
}

void FlyingObject::kill()
{
    alive = false;
}

void FlyingObject::advance(int screenSize)
{
    point.addX(velocity.getdx());
    point.addY(velocity.getdy());
    if (point.getX() > screenSize / 2)point.addX(-screenSize);
    if (point.getX() < screenSize / 2)point.addX(screenSize);
    if (point.getY() > screenSize / 2)point.addY(-screenSize);
    if (point.getY() < screenSize / 2)point.addY(screenSize);
}
