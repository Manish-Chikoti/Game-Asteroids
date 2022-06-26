#ifndef bullet_h
#define bullet_h

#define BULLET_SPEED 10
#define BULLET_LIFE 25

#include "FlyingObject.h"
#include "UiDraw.h"
#include "Ship.h"
#include <stdio.h>
#include <cmath>

class Bullet : public FlyingObject
{
public:
    Bullet();
    void kill();
    void draw();
    void fire(Point, float);
    int lifeSpam = 0;
};

#endif