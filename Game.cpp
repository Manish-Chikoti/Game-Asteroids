#include "Game.h"
#include "UiInteract.h"
#include "UiDraw.h"
#include <limits>
#include <algorithm>

#define OFF_SCREEN_BORDER_AMOUNT 5
#define SCREEN_SIZE 400

using namespace std;

Game::Game(Point topLeft, Point bottomRight)
{
    ship = NULL;
    score = 0;
    level = 1;
    createBigRock();
}

void Game::advance()
{
    advanceBullets();
    advanceShip();
    advanceRocks();
    handleCollisions();
    cleanUpZombies();

}


void Game::advanceShip()
{
    if (ship == NULL)
    {
        // there is no ship right now, possibly create one
        ship = new Ship;
    }
    else
    {
        // move it forward
        ship->advance(SCREEN_SIZE);
    }
}

/**********************************************************
 * HANDLE INPUT
 **********************************************************/
void Game::handleInput(const Interface& ui)
{
    // Change the direction of the ship
    if (ui.isLeft())
    {
        ship->moveRight();
    }

    if (ui.isRight())
    {
        ship->moveLeft();
    }

    if (ui.isUp())
    {
        ship->applyThrustBottom();
    }
    else
        ship->thrust = false;

    // check for "Spacebar
    if (ui.isSpace())
    {
        Bullet* newBullet = new Bullet;
        newBullet->fire(ship->getPoint(), ship->getAngle());

        bullets.push_back(newBullet);
    }

    // if "k" is pressed kills all rocks and advances to level 2
    if (ui.isK())
    {
        vector<Rock*> ::iterator rit = rocks.begin();
        while (rit < rocks.end())
        {
            delete* rit;
            *rit = NULL;
            rit = rocks.erase(rit);
            score = 40;
        }
    }

}

void Game::draw(Interface something)
{

    //check if you have a valid rock and if it's alive
    // then call it's draw method
    vector<Rock*> ::iterator rit;
    for (rit = rocks.begin(); rit < rocks.end(); ++rit)
    {
        if ((*rit)->isAlive())
            (*rit)->draw();
    }

    //check if you have a valid ship and if it's alive
    // then call it's draw method
    if (ship != NULL)
        if (ship->isAlive())
            ship->draw();

    // draw the bullets, if they are alive
    vector<Bullet*> ::iterator bit;
    for (bit = bullets.begin(); bit < bullets.end(); ++bit)
    {
        if ((*bit)->isAlive())
            (*bit)->draw();
    }

    if (score == 40 && level == 1)
    {
        for (int i = 0; i < 4; i++)
            createUltraShip();

        level = 2;
    }

    // Put the score on the screen
    Point scoreLocation;
    scoreLocation.setX( - 195);
    scoreLocation.setY(195);

    drawNumber(scoreLocation, score);

}   

bool Game::isOnScreen(const Point& point)
{
    return (point.getX() >= topLeft.getX() - OFF_SCREEN_BORDER_AMOUNT
        && point.getX() <= bottomRight.getX() + OFF_SCREEN_BORDER_AMOUNT
        && point.getY() >= bottomRight.getY() - OFF_SCREEN_BORDER_AMOUNT
        && point.getY() <= topLeft.getY() + OFF_SCREEN_BORDER_AMOUNT);
}

void Game::advanceBullets()
{

    // Move each of the bullets forward if it is alive
    vector<Bullet*> ::iterator bit;
    for (bit = bullets.begin(); bit < bullets.end(); ++bit)
    {
        if ((*bit)->isAlive())
            (*bit)->advance(SCREEN_SIZE);
    }
}

void Game::advanceRocks()
{
    vector<Rock*> ::iterator rit;
    for (rit = rocks.begin(); rit < rocks.end(); ++rit)
    {
        if ((*rit)->isAlive())
            (*rit)->advance(SCREEN_SIZE);
    }
}

void Game::createBigRock()
{
    for (int i = 0; i < 5; i++)
    {
        rocks.push_back(new BigRock);
    }
}

void Game::createMediumRock(Point bPoint, int mRock)
{
    rocks.push_back(new MediumRock(bPoint, mRock));

}

void Game::createSmallRock(Point bPoint, int sRock)
{
    rocks.push_back(new SmallRock(bPoint, sRock));
}

void Game::handleCollisions()
{

    vector<Rock*> ::iterator rit;
    for (rit = rocks.begin(); rit != rocks.end(); rit++)
    {
        if (ship->isAlive() && getClosestDistance(*ship, (**rit)) < (*rit)->getRadius())
        {
            ship->kill();
            (*rit)->hit();


        }
    }

    vector<Bullet*> ::iterator bit;
    for (bit = bullets.begin(); bit != bullets.end(); bit++)
    {
        vector<Rock*> ::iterator rit = rocks.begin();
        for (rit = rocks.begin(); rit != rocks.end(); rit++)
        {
            if ((*bit)->isAlive() && getClosestDistance((**bit), (**rit)) < (*rit)->getRadius())
            {
                //rock got hit
                (*rit)->hit();

                //increase the score
                ++score;


                //create two medium rocks and a small rock
                if ((*rit)->getRockId() == 1)
                {
                    createMediumRock((*rit)->getPoint(), 1);
                    createMediumRock((*rit)->getPoint(), 2);
                    createSmallRock((*rit)->getPoint(), 1);
                }

                //create a small rock
                if ((*rit)->getRockId() == 2)
                {
                    createSmallRock((*rit)->getPoint(), 1);
                    createSmallRock((*rit)->getPoint(), 2);
                }

                // the bullet is dead as well
                (*bit)->kill();
                break;
            }
        }
    }
}

void Game::cleanUpZombies()
{

    vector<Rock*> ::iterator rit;
    for (rit = rocks.begin(); rit != rocks.end();)
        if ((*rit)->isAlive() == false)
        {
            delete* rit;
            *rit = NULL;
            rit = rocks.erase(rit);
        }
        else rit++;


    if (ship != NULL && !ship->isAlive())
    {
        delete ship;
    }

    vector<Bullet*> ::iterator bit;
    for (bit = bullets.begin(); bit != bullets.end();)
        if ((*bit)->isAlive() == false)
        {
            delete* bit;
            *bit = NULL;
            bit = bullets.erase(bit);
        }
        else bit++;
}

float Game::getClosestDistance(const FlyingObject& obj1, const FlyingObject& obj2) const
{
    // find the maximum distance traveled
    float dMax = max(abs(obj1.getVelocity().getdx()), abs(obj1.getVelocity().getdy()));
    dMax = max(dMax, abs(obj2.getVelocity().getdx()));
    dMax = max(dMax, abs(obj2.getVelocity().getdy()));
    dMax = max(dMax, 0.1f); // when dx and dy are 0.0. Go through the loop once.

    float distMin = std::numeric_limits<float>::max();
    for (float i = 0.0; i <= dMax; i++)
    {
        Point point1(obj1.getPoint().getX() + (obj1.getVelocity().getdx() * i / dMax),
            obj1.getPoint().getY() + (obj1.getVelocity().getdy() * i / dMax));
        Point point2(obj2.getPoint().getX() + (obj2.getVelocity().getdx() * i / dMax),
            obj2.getPoint().getY() + (obj2.getVelocity().getdy() * i / dMax));

        float xDiff = point1.getX() - point2.getX();
        float yDiff = point1.getY() - point2.getY();

        float distSquared = (xDiff * xDiff) + (yDiff * yDiff);

        distMin = min(distMin, distSquared);
    }

    return sqrt(distMin);
}


