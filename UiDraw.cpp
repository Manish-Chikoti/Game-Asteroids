#include <string>
#include <sstream>
#include <cassert>
#include <time.h>

#ifdef __APPLE__
#include <openGL/gl.h>
#include <GLUT/glut.h>
#endif

#ifdef __linux__
#include <GL/gl.h>
#include <Gl/glut.h>
#endif

#ifdef _WIN32
#include <windows.h>
#include <GL/glut.h>
#include <GL/gl.h>
#include <stdio.h>
#include <stdlib.h>
#define _USE_MATH_DEFINES
#include <math.h>
#endif 

#include "Point.h"
#include "UiDraw.h"

using namespace std;

#define deg2rad(value) ((M_PI / 180 ) * value )

const char NUMBER_OUTLINES[10][20] =
{
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   0,10,  0, 0,  -1,-1, -1,-1},//0
  {7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//1
  {0, 0,  7, 0,   7, 0,  7, 5,   7, 5,  0, 5,   0, 5,  0,10,   0,10,  7,10},//2
  {0, 0,  7, 0,   7, 0,  7,10,   7,10,  0,10,   4, 5,  7, 5,  -1,-1, -1,-1},//3
  {0, 0,  0, 5,   0, 5,  7, 5,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1},//4
  {7, 0,  0, 0,   0, 0,  0, 5,   0, 5,  7, 5,   7, 5,  7,10,   7,10,  0,10},//5
  {7, 0,  0, 0,   0, 0,  0,10,   0,10,  7,10,   7,10,  7, 5,   7, 5,  0, 5},//6
  {0, 0,  7, 0,   7, 0,  7,10,  -1,-1, -1,-1,  -1,-1, -1,-1,  -1,-1, -1,-1},//7
  {0, 0,  7, 0,   0, 5,  7, 5,   0,10,  7,10,   0, 0,  0,10,   7, 0,  7,10},//8
  {0, 0,  7, 0,   7, 0,  7,10,   0, 0,  0, 5,   0, 5,  7, 5,  -1,-1, -1,-1} //9
};

void drawDigit(const Point& topLeft, char digit)
{
    
    assert(isdigit(digit));
    if (!isdigit(digit))
        return;

   
    int r = digit - '0';
    assert(r >= 0 && r <= 9);

    
    for (int c = 0; c < 20 && NUMBER_OUTLINES[r][c] != -1; c += 4)
    {
        assert(NUMBER_OUTLINES[r][c] != -1 &&
            NUMBER_OUTLINES[r][c + 1] != -1 &&
            NUMBER_OUTLINES[r][c + 2] != -1 &&
            NUMBER_OUTLINES[r][c + 3] != -1);

       
        Point start;
        start.setX(topLeft.getX() + NUMBER_OUTLINES[r][c]);
        start.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 1]);
        Point end;
        end.setX(topLeft.getX() + NUMBER_OUTLINES[r][c + 2]);
        end.setY(topLeft.getY() - NUMBER_OUTLINES[r][c + 3]);

        drawLine(start, end);
    }
}

void drawNumber(const Point& topLeft, int number)
{
    // our cursor, if you will. It will advance as we output digits
    Point point = topLeft;

    // is this negative
    bool isNegative = (number < 0);
    number *= (isNegative ? -1 : 1);

    // render the number as text
    ostringstream sout;
    sout << number;
    string text = sout.str();

    // handle the negative
    if (isNegative)
    {
        glBegin(GL_LINES);
        glVertex2f(point.getX() + 1, point.getY() - 5);
        glVertex2f(point.getX() + 5, point.getY() - 5);
        glEnd();
        point.addX(11);
    }

    // walk through the text one digit at a time
    for (const char* p = text.c_str(); *p; p++)
    {
        assert(isdigit(*p));
        drawDigit(point, *p);
        point.addX(11);
    }
}

void drawText(const Point & topLeft, const char * text)
{
   void *pFont = GLUT_BITMAP_HELVETICA_12;  // also try _18

   // prepare to draw the text from the top-left corner
   glRasterPos2f(topLeft.getX(), topLeft.getY());

   // loop through the text
   for (const char *p = text; *p; p++)
      glutBitmapCharacter(pFont, *p);
}

void drawPolygon(const Point& center, int radius, int points, int rotation)
{
    // begin drawing
    glBegin(GL_LINE_LOOP);

    //loop around a circle the given number of times drawing a line from
    //one point to the next
    for (double i = 0; i < 2 * M_PI; i += (2 * M_PI) / points)
    {
        Point temp(false /*check*/);
        temp.setX(center.getX() + (radius * cos(i)));
        temp.setY(center.getY() + (radius * sin(i)));
        rotate(temp, center, rotation);
        glVertex2f(temp.getX(), temp.getY());
    }

    // complete drawing
    glEnd();

}

void rotate(Point& point, const Point& origin, int rotation)
{
    // because sine and cosine are expensive, we want to call them only once , we dont want the game to lag;)
    double cosA = cos(deg2rad(rotation));
    double sinA = sin(deg2rad(rotation));

    // remember our original point
    Point tmp(false /*checking*/);
    tmp.setX(point.getX() - origin.getX());
    tmp.setY(point.getY() - origin.getY());

    // find the new values
    point.setX(static_cast<int> (tmp.getX() * cosA -
        tmp.getY() * sinA) +
        origin.getX());
    point.setY(static_cast<int> (tmp.getX() * sinA +
        tmp.getY() * cosA) +
        origin.getY());
}

void drawLine(const Point& begin, const Point& end,
    float red, float green, float blue)
{
    // starting the drawing
    glBegin(GL_LINES);
    glColor3f(red, green, blue);

    // Drawing the actual line
    glVertex2f(begin.getX(), begin.getY());
    glVertex2f(end.getX(), end.getY());

    // Continuing to complete
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    glEnd();
}

void drawLander(const Point& point)
{
    //simple point
    struct PT
    {
        int x;
        int y;
    } points[] =
    {
       {-6, 0}, {-10,0}, {-8, 0}, {-8, 3},  // left foot
       {-5, 4}, {-5, 7}, {-8, 3}, {-5, 4},  // left leg
       {-1, 4}, {-3, 2}, { 3, 2}, { 1, 4}, {-1, 4}, // bottom
       { 5, 4}, { 5, 7}, {-5, 7}, {-3, 7},  // Main engine square
       {-6,10}, {-6,13}, {-3,16}, { 3,16},   // left bottom of habitat
       { 6,13}, { 6,10}, { 3, 7}, { 5, 7},   // right bottom of habitat
       { 5, 4}, { 8, 3}, { 5, 7}, { 5, 4},  // right leg
       { 8, 3}, { 8, 0}, {10, 0}, { 6, 0}   // right foot
    };

    // drawing the lander for real 
    glBegin(GL_LINE_STRIP);
    for (int i = 0; i < sizeof(points) / sizeof(points[0]); i++)
        glVertex2f(point.getX() + points[i].x,
            point.getY() + points[i].y);

    // complete drawing
    glEnd();


}

void drawLanderFlames(const Point& point,bool bottom,bool left,bool right)
{
    //simple point
    struct PT
    {
        int x;
        int y;
    };

    int iFlame = random(0, 3);  // to make the thrust look like it flickers

    // drawing  it
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);//flames of trust (only red in colour)

    // bottom thrust
    if (bottom)
    {
        PT points[3][3] =
        {
           { {-5,  -6}, { 0, -1}, { 3, -10} },
           { {-3,  -6}, {-1, -2}, { 0, -15} },
           { { 2, -12}, { 1,  0}, { 6,  -4} }
        };

        glVertex2f(point.getX() - 2, point.getY() + 2);
        for (int i = 0; i < 3; i++)
            glVertex2f(point.getX() + points[iFlame][i].x,
                point.getY() + points[iFlame][i].y);
        glVertex2f(point.getX() + 2, point.getY() + 2);
    }

    // right thrust
    if (right)
    {
        PT points[3][3] =
        {
           { {10, 14}, { 8, 12}, {12, 12} },
           { {12, 10}, { 8, 10}, {10,  8} },
           { {14, 11}, {14, 11}, {14, 11} }
        };

        glVertex2f(point.getX() + 6, point.getY() + 12);
        for (int i = 0; i < 3; i++)
            glVertex2f(point.getX() + points[iFlame][i].x,
                point.getY() + points[iFlame][i].y);
        glVertex2f(point.getX() + 6, point.getY() + 10);
    }

    // left thrust
    if (left)
    {
        PT points[3][3] =
        {
           { {-10, 14}, { -8, 12}, {-12, 12} },
           { {-12, 10}, { -8, 10}, {-10,  8} },
           { {-14, 11}, {-14, 11}, {-14, 11} }
        };

        glVertex2f(point.getX() - 6, point.getY() + 12);
        for (int i = 0; i < 3; i++)
            glVertex2f(point.getX() + points[iFlame][i].x,
                point.getY() + points[iFlame][i].y);
        glVertex2f(point.getX() - 6, point.getY() + 10);
    }

    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    glEnd();
}

int random(int min, int max)
{
    assert(min < max);
    int num = (rand() % (max - min)) + min;
    assert(min <= num && num <= max);

    return num;
}

double random(double min, double max)
{
    assert(min <= max);
    double num = min + ((double)rand() / (double)RAND_MAX * (max - min));
    assert(min <= num && num <= max);

    return num;
}

void drawRect(const Point& center, int width, int height, int rotation)
{
    Point tl(false /*checking*/); // top left
    Point tr(false /*checking*/); // top right 
    Point bl(false /*checking*/); // bottom left
    Point br(false /*checking*/); // bottom right

    //Top Left point
    tl.setX(center.getX() - (width / 2));
    tl.setY(center.getY() + (height / 2));

    //Top right point
    tr.setX(center.getX() + (width / 2));
    tr.setY(center.getY() + (height / 2));

    //Bottom left point
    bl.setX(center.getX() - (width / 2));
    bl.setY(center.getY() - (height / 2));

    //Bottom right point
    br.setX(center.getX() + (width / 2));
    br.setY(center.getY() - (height / 2));

    //To rotate all points by the given degrees
    rotate(tl, center, rotation);
    rotate(tr, center, rotation);
    rotate(bl, center, rotation);
    rotate(br, center, rotation);

    //Now drawing the rectangle
    glBegin(GL_LINE_STRIP);
    glVertex2f(tl.getX(), tl.getY());
    glVertex2f(tr.getX(), tr.getY());
    glVertex2f(br.getX(), br.getY());
    glVertex2f(bl.getX(), bl.getY());
    glVertex2f(tl.getX(), tl.getY());
    glEnd();
}

void drawCircle(const Point& center, int radius)
{
    assert(radius > 1.0);
    const double increment = 1.0 / (double)radius;

    // begin drawing
    glBegin(GL_LINE_LOOP);

    // go around the circle
    for (double radians = 0; radians < M_PI * 2.0; radians += increment)
        glVertex2f(center.getX() + (radius * cos(radians)),
            center.getY() + (radius * sin(radians)));

    // complete drawing
    glEnd();
}

void drawDot(const Point& point)
{
    // Starting...
    glBegin(GL_POINTS);
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 1.0 /* blue % */);
    // Drawing...
    glVertex2f(point.getX(), point.getY());
    glVertex2f(point.getX() + 1, point.getY());
    glVertex2f(point.getX() + 1, point.getY() + 1);
    glVertex2f(point.getX(), point.getY() + 1);

    
    glEnd();
}

void drawSuperDot(const Point& point)
{
    // Starting...
    glBegin(GL_POINTS);
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);//Totally red in colour
    // Drawing...
    glVertex2f(point.getX(), point.getY());
    glVertex2f(point.getX() + 1, point.getY());
    glVertex2f(point.getX() + 1, point.getY() + 1);
    glVertex2f(point.getX(), point.getY() + 1);

    
    glEnd();
}

void drawSacredBird(const Point& center, float radius)
{
    // handling auto-rotation
    static float rotation = 0.0;
    rotation += 5.0;


    // begining drawing
    glBegin(GL_LINE_LOOP);
    glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);


    //loop around a circle the given number of times drawing a line from one point to the next
    for (int i = 0; i < 5; i++)
    {
        Point temp(false /*checking*/);
        float radian = (float)i * (M_PI * 2.0) * 0.4;
        temp.setX(center.getX() + (radius * cos(radian)));
        temp.setY(center.getY() + (radius * sin(radian)));
        rotate(temp, center, rotation);
        glVertex2f(temp.getX(), temp.getY());
    }

    // complete drawing
    glColor3f(1.0, 1.0, 1.0); // reset to white
    glEnd();
}

void drawToughBird(const Point& center, float radius, int hits)
{
    assert(radius > 1.0);
    const double increment = M_PI / 6.0;

    // begin drawing
    glBegin(GL_TRIANGLES);

    // three points: center, pt1, pt2
    Point pt1(false /*checking*/);
    pt1.setX(center.getX() + (radius * cos(0.0)));
    pt1.setY(center.getY() + (radius * sin(0.0)));
    Point pt2(pt1);

    // go around the circle
    for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment)
    {
        pt2.setX(center.getX() + (radius * cos(radians)));
        pt2.setY(center.getY() + (radius * sin(radians)));

        glVertex2f(center.getX(), center.getY());
        glVertex2f(pt1.getX(), pt1.getY());
        glVertex2f(pt2.getX(), pt2.getY());

        pt1 = pt2;
    }

    // complete drawing
    glEnd();

    // draw the score in the center
    if (hits > 0 && hits < 10)
    {
        glColor3f(0.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
        glRasterPos2f(center.getX() - 4, center.getY() - 3);
        glutBitmapCharacter(GLUT_BITMAP_8_BY_13, (char)(hits + '0'));
        glColor3f(1.0, 1.0, 1.0); // reset to white
    }
}

void drawSmallAsteroid(const Point& center, int rotation)
{
    // simple point
    struct PT
    {
        int x;
        int y;
    } points[] =
    {
       {-5, 9},  {4, 8},   {8, 4},
       {8, -5},  {-2, -8}, {-2, -3},
       {-8, -4}, {-8, 4},  {-5, 10}
    };

    glBegin(GL_LINE_STRIP);
    glColor3f(0.5 /* red % */, 0.2 /* green % */, 0.1 /* blue % */);
    for (int i = 0; i < sizeof(points) / sizeof(PT); i++)
    {
        Point pt(center.getX() + points[i].x,
            center.getY() + points[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}

void drawMediumAsteroid(const Point& center, int rotation)
{
    // Simple point
    struct PT
    {
        int x;
        int y;
    } points[] =
    {
       {2, 8},    {8, 15},    {12, 8},
       {6, 2},    {12, -6},   {2, -15},
       {-6, -15}, {-14, -10}, {-15, 0},
       {-4, 15},  {2, 8}
    };

    glBegin(GL_LINE_STRIP);
    glColor3f(0.5 /* red % */, 0.2 /* green % */, 0.1 /* blue % */);
    for (int i = 0; i < sizeof(points) / sizeof(PT); i++)
    {
        Point pt(center.getX() + points[i].x,
            center.getY() + points[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}

void drawLargeAsteroid(const Point& center, int rotation)
{
    // Simple point
    struct PT
    {
        int x;
        int y;
    } points[] =
    {
       {0, 12},    {8, 20}, {16, 14},
       {10, 12},   {20, 0}, {0, -20},
       {-18, -10}, {-20, -2}, {-20, 14},
       {-10, 20},  {0, 12}
    };

    glBegin(GL_LINE_STRIP);
    glColor3f(0.5 /* red % */, 0.2 /* green % */, 0.1 /* blue % */);
    for (int i = 0; i < sizeof(points) / sizeof(PT); i++)
    {
        Point pt(center.getX() + points[i].x,
            center.getY() + points[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();
}

void drawShip(const Point& center, int rotation, bool thrust)
{
    // Simple point
    struct PT
    {
        int x;
        int y;
    };

    // Drawing the ship                                                 
    const PT pointsShip[] =
    { // top   r.wing   r.engine l.engine  l.wing    top
       {0, 6}, {6, -6}, {2, -3}, {-2, -3}, {-6, -6}, {0, 6}
    };

    glBegin(GL_LINE_STRIP);
    glColor3f(1.0 /* red % */, 1.0 /* green % */, 0.0 /* blue % */);
    for (int i = 0; i < sizeof(pointsShip) / sizeof(PT); i++)
    {
        Point pt(center.getX() + pointsShip[i].x,
            center.getY() + pointsShip[i].y);
        rotate(pt, center, rotation);
        glVertex2f(pt.getX(), pt.getY());
    }
    glEnd();

    // drawing the flame if necessary
    if (thrust)
    {
        const PT pointsFlame[3][5] =
        {
           { {-2, -3}, {-2, -13}, { 0, -6}, { 2, -13}, {2, -3} },
           { {-2, -3}, {-4,  -9}, {-1, -7}, { 1, -14}, {2, -3} },
           { {-2, -3}, {-1, -14}, { 1, -7}, { 4,  -9}, {2, -3} }
        };

        glBegin(GL_LINE_STRIP);
        glColor3f(1.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);
        int iFlame = random(0, 3);
        for (int i = 0; i < 5; i++)
        {
            Point pt(center.getX() + pointsFlame[iFlame][i].x,
                center.getY() + pointsFlame[iFlame][i].y);
            rotate(pt, center, rotation);
            glVertex2f(pt.getX(), pt.getY());
        }
        glColor3f(1.0, 1.0, 1.0); // reset to white                                  
        glEnd();
    }
}

void drawUltraAsteroid(const Point& center, int hits)
{
    assert(30 > 1.0);
    const double increment = M_PI / 6.0;

    // Starting...
    glBegin(GL_TRIANGLES);

    if (hits > 40 && hits <= 50)
        glColor3f(0.6 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

    if (hits > 30 && hits <= 39)
        glColor3f(0.7 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

    if (hits > 20 && hits <= 29)
        glColor3f(0.8 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

    if (hits > 10 && hits <= 19)
        glColor3f(0.9 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

    if (hits > 0 && hits <= 9)
        glColor3f(2.0 /* red % */, 0.0 /* green % */, 0.0 /* blue % */);

    // three points: center, pt1, pt2
    Point pt1(false /*check*/);
    pt1.setX(center.getX() + (40 * cos(0.0)));
    pt1.setY(center.getY() + (40 * sin(0.0)));
    Point pt2(pt1);

    // going around the circle
    for (double radians = increment;
        radians <= M_PI * 2.0 + .5;
        radians += increment)
    {
        pt2.setX(center.getX() + (40 * cos(radians)));
        pt2.setY(center.getY() + (40 * sin(radians)));

        glVertex2f(center.getX(), center.getY());
        glVertex2f(pt1.getX(), pt1.getY());
        glVertex2f(pt2.getX(), pt2.getY());

        pt1 = pt2;
    }
    // completing drawing
    glEnd();

}




