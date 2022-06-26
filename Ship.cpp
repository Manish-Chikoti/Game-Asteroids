#include "Ship.h"

#include <cassert>
#define _USE_MATH_DEFINES // for C++
#include <math.h>

Ship::Ship()
{
    alive = true;
    thrust = false;
    angle = 0;

}

void Ship::draw()
{
    drawShip(point, angle, thrust);
}

void Ship::kill()
{
    setAlive(false);
}

void Ship::moveLeft()
{
    angle -= SHIP_MOVE_AMOUNT;
}

void Ship::moveRight()
{
    angle += SHIP_MOVE_AMOUNT;
}

void Ship::applyThrustBottom()
{
    thrust = true;
    velocity.setdx(velocity.getdx() + cos((float)(91 + angle) * M_PI / 180) * SHIP_SPEED);
    velocity.setdy(velocity.getdy() + sin((float)(91 + angle) * M_PI / 180) * SHIP_SPEED);

}