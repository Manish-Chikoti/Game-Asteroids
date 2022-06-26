#ifndef SHIP_H
#define SHIP_H

#include "FlyingObject.h"
#include "UiInteract.h"
#include "UiDraw.h"

#define SHIP_SPEED 0.1
#define SHIP_MOVE_AMOUNT 3
#define ROTATE_AMOUNT 6

class Ship : public FlyingObject
{
private:
	int bottom;
	float angle;

public:
	Ship();
    float getAngle() const { return angle; }
    Point getPoint() const { return point; }

    void draw();
    void kill();

    void moveLeft();
    void moveRight();
    void applyThrustBottom();
    bool thrust;

};

#endif