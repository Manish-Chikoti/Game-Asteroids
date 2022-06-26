#include "Bullet.h"
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif
#include <cmath>

Bullet::Bullet()
{
    setAlive(true);
}

void Bullet::kill()
{
    setAlive(false);
}

void Bullet::draw()
{
    drawDot(getPoint());

    if (lifeSpam == (BULLET_LIFE - 1))
    {
        kill();
    }

    lifeSpam++;
}

void Bullet::fire(Point shipPoint, float angle)
{
    setPoint(shipPoint);

    Velocity velocity;

    velocity.setdx(cos((float)(91 + angle) * M_PI / 180) * BULLET_SPEED);
    velocity.setdy(sin((float)(91 + angle) * M_PI / 180) * BULLET_SPEED);

    setVelocity(velocity);


}