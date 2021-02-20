#include "Actor.h"
#include "StudentWorld.h"
#include <cmath>
// Students:  Add code to this file, Actor.h, StudentWorld.h, and StudentWorld.cpp
//Actor
void Actor::moveSameHori()
{
    int vert_speed = vertSpeed - m_world->getPlayer()->getVerS();
    double new_y = getY() + vert_speed;
    double new_x = getX() + horiSpeed;
    moveTo(new_x, new_y);
}

bool Actor::offScreen()
{
    if(getY() < 0 || getX() < 0 || getY() > VIEW_HEIGHT || getX() > VIEW_WIDTH){
        notLive();
        return true;
    }
    return false;
}

bool Actor::checkOverlap(Actor* cp)
{
    double delta_x = abs(getX() - cp->getX());
    double delta_y = abs(getY() - cp->getY());
    double radius_sum = getRadius() + m_world->getPlayer()->getRadius();
    if(delta_x < radius_sum*0.25 && delta_y < radius_sum*0.6)
        return true;
    return false;
}

//GhostRacer
void GhostRacer::doSomething()
{
    if(!isLive())
        return;
    if(getX() <= ROAD_CENTER - ROAD_WIDTH/2){
        if(getDirection()>90){
            demageRacer(10);
        }
        setDirection(82);
        getWorld()->playSound(SOUND_VEHICLE_CRASH);
        moveAlgorithm();
    }
    if(getX() >= ROAD_CENTER + ROAD_WIDTH/2){
        if(getDirection()<90){
            demageRacer(10);
        }
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
                    setDirection(getDirection()+8);
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
                if(getVerS() < 5){
                    setVerS(1);
                    moveAlgorithm();
                }
                break;
            case KEY_PRESS_DOWN:
                if(getVerS() > -1){
                    setVerS(-1);
                    moveAlgorithm();
                }
                break;
            default:
                break;
        }
    }
    else{
        moveAlgorithm();
    }
}

void GhostRacer::moveAlgorithm()
{
    static const double PI = 4 * atan(1.0);
    double max_shift_per_tick = 4.0;
    int direction = getDirection();
    double delta_x = cos(direction*PI/180) * max_shift_per_tick;
    double cur_x = getX();
    double cur_y = getY();
    moveTo(cur_x + delta_x, cur_y);
}

void GhostRacer::demageRacer(int hitPoint)
{
    health = health-hitPoint;
    if(health <= 0){
        notLive();
        getWorld()->playSound(SOUND_PLAYER_DIE);
    }
}

void GhostRacer::spun()
{
    int nowDir = getDirection();
    bool changed = false;
    
    while(!changed){
        int changeDir = randInt(5, 20);
        if(nowDir-changeDir >=60){
            setDirection(nowDir-changeDir);
            return;
        }
        else if(nowDir + changeDir <=120){
            setDirection(nowDir+changeDir);
            return;
        }
        else
            changed = false;
    }
}

//BorderLine
void BorderLine::doSomething()
{
    if(!isLive())
        return;
    moveSameHori();
    offScreen();
}

//Goodies
void Goodies::doSomething()
{
    moveSameHori();
    if(offScreen()){
        notLive();
        return;
    }
    if(checkOverlap(getWorld()->getPlayer()))
    {
        if(!isOil)
            notLive();
        getWorld()->playSound(playSound);
        getWorld()->increaseScore(inScore);
        overDiff();
    }
    otherDiff();
}
//Soul
void Soul::overDiff()
{
    getWorld()->saveNewSoul();
}

void Soul::otherDiff()
{
    setDirection(getDirection()-10);
}

//Healing
void Healing::overDiff()
{
    getWorld()->getPlayer()->changeHealth(10);
}

//Holy Water
void HolyWater::overDiff()
{
    getWorld()->getPlayer()->changeWater(10);
}

//Oil slick
void OilSlick::overDiff()
{
    getWorld()->getPlayer()->spun();
}

//Human
void HumanPed::doSomething()
{
    if(!isLive())
        return;
    if(checkOverlap(getWorld()->getPlayer())){
        getWorld()->decLives();
        return;
    }
    moveSameHori();
    if(offScreen()){
        notLive();
        return;
    }
    planMove--;
    if(planMove>0)
        return;
    //pick new movement plan
    int newHori = randInt(-3, 3);
    while(newHori==0){
        newHori = randInt(-3, 3);
    }
    setHoriS(-getHoriS());//horispeed change to 0
    setHoriS(newHori);//set speed to the new speed
    planMove = randInt(4, 32);
    if(getHoriS()>0){
        setDirection(180);
    }
    else if(getHoriS()<0){
        setDirection(0);
    }
}
