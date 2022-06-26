#ifndef UI_INTERACT_H
#define UI_INTERACT_H

#include "Point.h"

class Interface
{
    private:
        void initialize(int argc, char** argv, const char *title, Point topleft, Point bottomright);

        static bool initialized;
        static double timePeriod;
        static unsigned int nextTick;

        static int isDownPressed;
        static int isUpPressed;
        static int isRightPressed;
        static int isLeftPressed;
        static bool isSpacePressed;
        static bool isKPressed;
       

    public:

        Interface() { initialize(0, 0x0000, "Window", Point(-50, 50), Point(50, -50)); }

        Interface(int argc, char** argv, const char* title, Point topLeft, Point bottomRight)
        {
            initialize(argc, argv, title, topLeft, bottomRight);
        }

        ~Interface();

        void run(void (*callBack)(const Interface*, void*), void* p);

        bool isTimeToDraw();

        void setNextDrawTime();

        unsigned int getNextTick() {
            return nextTick;
        };

        void setFramesPerSecond(double value);

        void keyEvent(int key, bool fdown);
        void keyEvent();

        double frameRate() const { return timePeriod; };

        int isDown() const { return isDownPressed; };
        int isUp() const { return isUpPressed; };
        int isRight() const { return isRightPressed; };
        int isLeft() const { return isLeftPressed; };
        int isSpace() const { return isSpacePressed; };
        int isK() const { return isKPressed; };

        static void *p;

        static void (*callBack)(const Interface*, void*);
};

void drawCallback();

void keyDownCallback(int key,int x,int y);

void keyUpCallback(int key , int x, int y);

void keyBoardCallback(unsigned char key, int x, int y);

void run();

#endif

