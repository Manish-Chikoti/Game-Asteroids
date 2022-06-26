#include "Velocity.h"
#include <stdio.h>

Velocity::Velocity()
{
    dx = 0;
    dy = 0;
}


Velocity::Velocity(float dx, float dy)
{
    this->dx = dx;
    this->dy = dy;
}

float Velocity::getdx() const
{
    return dx;
}

float Velocity::getdy() const
{
    return dy;
}

void Velocity::setdx(float dx)
{
    this->dx = dx;
}

void Velocity::setdy(float dy)
{
    this->dy = dy;
}