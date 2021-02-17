#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//Actor
bool Actor::checkOverlap()
{
    double delta_x = abs(this->getX() - other->getX());
    double delta_y = abs(this->getY() - other->getY());
    double radius_sum = this->getRadius() + other->getRadius();
    if(delta_x < radius_sum*0.25 && delta_y < radius_sum*0.6)
        return true;
    return false;
}

//GhostRacer
bool GhostRacer::isAlive()
{
    if (health <= 0)
        return false;
    else
        return true;
}

