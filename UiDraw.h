#ifndef UI_DRAW_H
#define UI_DRAW_H


#include <cmath>
#include <string>
using std::string;
#include "point.h"

void drawDigit(const Point& topleft, char digit);

void drawNumber(const Point& topleft, int number);

void drawText(const Point& topleft, const char* text);

void rotate(Point& point, const Point& origin, int rotation = 0);

void drawRectangle(const Point& center, int width, int height, int rotation);

void drawCircle(const Point& center, int radius);

void drawPolygon(const Point& center, int radius = 20, int point = 4, int rotation = 0);

void drawLine(const Point& begin, const Point& end, float red = 1.0, float green = 1.0, float blue = 1.0);

void drawLander(const Point& point);

void drawLanderFlames(const Point& point, bool bottom, bool left, bool right);

void drawDot(const Point& point);

void drawSacredBird(const Point& center, float radius);

void drawToughBird(const Point& center, float radius, int hits);

void drawShip(const Point& point, int rotation, bool thrust = false);

void drawSmallAsteroid(const Point& point, int rotation);
void drawMediumAsteroid(const Point& point, int rotation);
void drawLargeAsteroid(const Point& point, int rotation);
void drawUltraAsteroid(const Point& center, int rotation);


int random(int min, int max);
double random(double min, double max);

#endif 


