#include "Rocks.h"

Rock::Rock()
{
	setAlive(true);
	setRockId(0);
}

int Rock::getRockId()
{
	return rockId;
}

void Rock::setRockId(int rockId)
{
	this->rockId = rockId;
}

void Rock :: kill()
{
	setAlive(false);
}

int Rock::getRadius()
{
	return radius;
}

void Rock::setRadius(int radius)
{
	this->radius = radius;
}

void Rock::hit()
{
}

void Rock::draw()
{
}

BigRock::BigRock()
{
    int rand = random(1, 3);
    int dx = 0;
    int dy = 0;
    int x = 0;
    int y = 0;

    if (rand == 2)
    {
        x = -200;
        dx = 1;
        y = random(-200, 200);
        dy = 1;
    }
    else
    {
        x = 200;
        dx = -1;
        y = random(-200, 200);
        dy = -1;
    }

    if (y >= 0)
    {
        Velocity velocity(dx, -dy);
        setVelocity(velocity);
    }

    if (y < 0)
    {
        Velocity velocity(dx, dy);
        setVelocity(velocity);
    }

    Point point(x, y);
    setPoint(point);
    setAlive(true);
    setRockId(1);
    setRadius(17);
    rotation = 2;
}

void BigRock::hit()
{
    kill();
}

void BigRock::draw()
{
    drawLargeAsteroid(point, rotation);

    for (int i = 0; i < 2; i++)
        ++rotation;
}



MediumRock::MediumRock(Point bPoint, int mRock)
{

    int dx = 2;
    int dy = 2;

    if (mRock == 2)
    {
        dx = -2;
        dy = -2;
    }

    Velocity velocity(dx, dy);
    setVelocity(velocity);

    Point point(bPoint.getX(), bPoint.getY());
    setPoint(point);

    setAlive(true);
    setRockId(2);
    setRadius(9);
    rotation = 0;

}

void MediumRock::draw()
{
    drawMediumAsteroid(point, rotation);

    for (int i = 0; i < 5; i++)
        ++rotation;

}

void MediumRock::hit()
{
    kill();
}

SmallRock::SmallRock(Point sPoint, int sRock)
{

    int dx = 3;
    int dy = 3;

    if (sRock == 2)
    {
        dx = -3;
        dy = -3;
    }

    Velocity velocity(dx, dy);
    setVelocity(velocity);

    Point point(sPoint.getX(), sPoint.getY());
    setPoint(point);

    setAlive(true);
    setRockId(3);
    setRadius(5);
    rotation = 0;

}

void SmallRock::draw()
{
    drawSmallAsteroid(point, rotation);

    for (int i = 0; i < 10; i++)
        rotation++;
}

void SmallRock::hit()
{
    kill();
}

UltraShip::UltraShip()
{
    int rand = random(1, 3);
    int dx = 0;
    int dy = 0;
    int x = 0;
    int y = 0;

    if (rand == 2)
    {
        x = -200;
        dx = 1;
        y = random(-200, 200);
        dy = 1;
    }
    else
    {
        x = 200;
        dx = -1;
        y = random(-200, 200);
        dy = -1;
    }

    if (y >= 0)
    {
        Velocity velocity(dx, -dy);
        setVelocity(velocity);
    }

    if (y < 0)
    {
        Velocity velocity(dx, dy);
        setVelocity(velocity);
    }

    Point point(x, y);
    setPoint(point);
    setAlive(true);
    setRockId(4);
    setRadius(35);
    hits = 49;
}

void UltraShip::draw()
{
    drawUltraAsteroid(point, hits);
}

void UltraShip::hit()
{

    if (hits == 0)
        kill();

    --hits;
}
