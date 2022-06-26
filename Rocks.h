#ifndef rocks_h
#define rocks_h

#define BIG_ROCK_SPIN 2
#define MEDIUM_ROCK_SPIN 5
#define SMALL_ROCK_SPIN 10

#include "FlyingObject.h"
#include "UiDraw.h"

class Rock : public FlyingObject
{
    private:
	    int rockId;
	    int radius;

    public:
		Rock();
		int getRockId();

		void setRockId(int rockId);

		virtual void kill();
		virtual void hit();
		virtual void draw();
		int getRadius();
		void setRadius(int);
};

class BigRock : public Rock
{
private:
	int rotation;
	int angle;
public:
	BigRock();
	virtual void hit();
	virtual void draw();
	int hits;

};

class MediumRock : public Rock
{
private:
	int angle;
	int rotation;
public:
	MediumRock(Point,int);
	virtual void hit();
	virtual void draw();

};

class SmallRock : public Rock
{
private:
	int rotation;
public:
	SmallRock(Point, int);
	virtual void draw();
	virtual void hit();

};

class UltraShip : public Rock
{
private:
	int hits;
	int angle;
public:
	UltraShip();
	virtual void draw();
	virtual void hit();

};

#endif