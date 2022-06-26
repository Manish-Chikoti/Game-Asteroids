#include <sstream>
#include <cassert>
#include <string>
#include <time.h>
#include <cstdlib>

#include "UiInteract.h"
#include "Point.h"

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
#include <ctime>
#endif 

using namespace std;

void sleep(unsigned long msSleep)
{
    #ifdef _WIN32
	    ::Sleep(msSleep + 35);

    #else
    timespec req = {};
    time_t sec = (int)(msSleep / 1000);
    msSleep -= (sec * 1000);

    req.tv_sec = sec;
    req.tv_nsec = msSleep * 1000000L;

    while (nanosleep(&req, &req) == -1);

    #endif
    return;
}

void drawCallback()
{
    // Please note :all the members are static
    Interface ui;
    // Preparing the background buffer for drawing
    glClear(GL_COLOR_BUFFER_BIT); //clearing the screen
    glColor3f(1, 1, 1);

    //calling the client's display function
    assert(ui.callBack != NULL);
    ui.callBack(&ui, ui.p);

    //loop until the timer runs out
    if (!ui.isTimeToDraw())
        sleep((unsigned long)((ui.getNextTick() - clock()) / 1000));

    // from this point, set the next draw time
    ui.setNextDrawTime();

    // bring forth the background buffer
    glutSwapBuffers();

    // clear the space at the end
    ui.keyEvent();
}

void keyDownCallback(int key, int x, int y)
{
    //  Please note :all the members are static
    // so we are actually getting the same version as in the constructor.
    Interface ui;
    ui.keyEvent(key, true /*fDown*/);
}

void keyboardCallback(unsigned char key, int x, int y)
{
    // Please note  all the members are static
    // so we are actually getting the same version as in the constructor.
    Interface ui;
    ui.keyEvent(key, true /*fDown*/);
}

void Interface::keyEvent(int key, bool fDown)
{
    switch (key)
    {
    case GLUT_KEY_DOWN:
        isDownPressed = fDown;
        break;
    case GLUT_KEY_UP:
        isUpPressed = fDown;
        break;
    case GLUT_KEY_RIGHT:
        isRightPressed = fDown;
        break;
    case GLUT_KEY_LEFT:
        isLeftPressed = fDown;
        break;
    case GLUT_KEY_HOME:
    case ' ':
        isSpacePressed = fDown;
        break;
    case 'k':
        isKPressed = fDown;
    }
}

void Interface::keyEvent()
{
    if (isDownPressed)
        isDownPressed++;
    if (isUpPressed)
        isUpPressed++;
    if (isLeftPressed)
        isLeftPressed++;
    if (isRightPressed)
        isRightPressed++;
    isSpacePressed = false;
    isKPressed = false;
}

bool Interface::isTimeToDraw()
{
    return ((unsigned int)clock() >= nextTick);
}

void Interface::setNextDrawTime()
{
    nextTick = clock() + static_cast<int> (timePeriod * CLOCKS_PER_SEC);
}

void Interface::setFramesPerSecond(double value)
{
    timePeriod = (1 / value);
}

int          Interface::isDownPressed = 0;
int          Interface::isUpPressed = 0;
int          Interface::isLeftPressed = 0;
int          Interface::isRightPressed = 0;
bool         Interface::isSpacePressed = false;
bool         Interface::isKPressed = false;
bool         Interface::initialized = false;
double       Interface::timePeriod = 1.0 / 30; // default to 30 frames/second
unsigned int Interface::nextTick = 0;        // redraw now please
void* Interface::p = NULL;
void (*Interface::callBack)(const Interface*, void*) = NULL;

Interface::~Interface()
{
}

void Interface::initialize(int argc, char** argv, const char* title, Point topLeft, Point bottomRight)
{
    if (initialized)
        return;

    // set up the random number generator
    srand((unsigned int)time(NULL));

    // create the window
    glutInit(&argc, argv);
    Point point;
    glutInitWindowSize(   // size of the window
        (int)(bottomRight.getX() - topLeft.getX()),
        (int)(topLeft.getY() - bottomRight.getY()));

    glutInitWindowPosition(10, 10);                // initial position 
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);  // double buffering
    glutCreateWindow(title);              // text on titlebar
    glutIgnoreKeyRepeat(true);

    // set up the drawing style: B/W and 2D
    glClearColor(0, 0, 0, 0);          // Black is the background color
    gluOrtho2D((int)topLeft.getX(), (int)bottomRight.getX(),
        (int)bottomRight.getY(), (int)topLeft.getY()); // 2D environment

// register the callbacks so OpenGL knows how to call us
    glutDisplayFunc(drawCallback);
    glutIdleFunc(drawCallback);
    glutKeyboardFunc(keyboardCallback);
    glutSpecialFunc(keyDownCallback);
    glutSpecialUpFunc(keyUpCallback);
    initialized = true;

    // done
    return;
}


void Interface::run(void (*callBack)(const Interface*, void*), void* p)
{
    // setup the callbacks
    this->p = p;
    this->callBack = callBack;

    glutMainLoop();

    return;
}



