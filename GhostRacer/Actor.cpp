#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//Actor
/*
bool Actor::checkOverlap(Actor* cp)
{
    double delta_x = abs(getX() - cp->getX());
    double delta_y = abs(getY() - cp->getY());
    double radius_sum = getRadius() + cp->getRadius();
    if(delta_x < radius_sum*0.25 && delta_y < radius_sum*0.6)
        return true;
    return false;
}
*/
//GhostRacer
void GhostRacer::doSomething()
{
    if(!isLive())
        return;
    if(getX() <= ROAD_CENTER - ROAD_WIDTH/2){
        if(getDirection()>90)
            demageRacer(10);
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        moveAlgorithm();
    }
    if(getX() >= ROAD_CENTER + ROAD_WIDTH/2){
        if(getDirection()<90)
            //need to change
            demageRacer(10);
        setDirection(98);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        moveAlgorithm();
    }
    int ch;
    if(getWorld()->getKey(ch))
    {
        switch(ch)
        {
            case KEY_PRESS_LEFT:
                if(getDirection() < 114){
                    setDirection(getDirection()+10);
                    moveAlgorithm();
                }
                break;
            case KEY_PRESS_RIGHT:
                if(getDirection() > 66){
                    setDirection(getDirection()-8);
                    moveAlgorithm();
                }
                break;
            case KEY_PRESS_UP:
                if(m_speed < 5){
                    m_speed++;
                    moveAlgorithm();
                }
                break;
            case KEY_PRESS_DOWN:
                if(m_speed > -1){
                    m_speed--;
                    moveAlgorithm();
                }
        }
    }
}

void GhostRacer::moveAlgorithm()
{
    double max_shift_per_tick = 4.0;
    int direction = getDirection();
    double delta_x = cos(direction) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
}

void GhostRacer::demageRacer(int hitPoint)
{
    health = health-hitPoint;
    if(health <= 0){
        changeLive(false);
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
}
