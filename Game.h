#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <vector>
#include "Point.h"
#include "UiDraw.h"
#include "UiInteract.h"
#include "Bullet.h"
#include "Ship.h"
#include "Rocks.h"

class Game
{
private:
	Point topLeft;
	Point bottomRight;
	int score;
	int level;
	std::vector<Bullet*> bullets;
	Ship * ship;
	std::vector<Rock*> rocks;

	bool isOnScreen(const Point& point);
	void advanceBullets();
	void advanceRocks();
	void handleCollisions();
	void cleanUpZombies();
	void createBigRock();
	void createMediumRock(Point, int);
	void createSmallRock(Point, int);
	void createUltraShip();
	float getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const;

public:
	Game();
	Game(Point topLeft, Point bottomRight);
	void advance();
	void advanceShip();
	void handleInput(const Interface& ui);
	void draw(Interface something);
};

#endif