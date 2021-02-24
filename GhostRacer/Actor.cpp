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

int Actor::onWhichLean()
{
    double LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    double RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    if(getX()>=LEFT_EDGE && getX()<LEFT_EDGE + ROAD_WIDTH/3)
        return 1;
    else if(getX()>=LEFT_EDGE + ROAD_WIDTH/3 && getX()< RIGHT_EDGE - ROAD_WIDTH/3)
        return 2;
    else
        return 3;
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

//Pedestrain
void Pedestrain::doSomething()
{
    if(!isLive())
        return;
    if(checkOverlap(getWorld()->getPlayer())){
        overDiff();
        return;
    }
    zombiePedDiff();
    moveSameHori();
    if(offScreen()){
        notLive();
        return;
    }
    cabDiff();
    planMove--;
    if(planMove>0)
        return;
    if(isCab)
        CabPlan();
    else
        PedPlan();
}

void Pedestrain::PedPlan(){
    //pick new movement plan
    int newHori = randInt(-3, 3);
    while(newHori==0){
        newHori = randInt(-3, 3);
    }
    setHoriS(-getHoriS());//horispeed change to 0
    setHoriS(newHori);//set speed to the new speed
    planMove = randInt(4, 32);
    if(getHoriS()<0){
        setDirection(180);
    }
    else if(getHoriS()>0){
        setDirection(0);
    }
}

void Pedestrain::CabPlan(){
    planMove = randInt(4, 32);
    setVerS(randInt(-2, 2));
}

void Pedestrain::demageZombie(int hit, bool racer, int sound_hurt, int sound_died,bool ped, int points)
{
    hitPoint = hitPoint-hit;
    if(getPoint()<=0){
        notLive();
        getWorld()->playSound(sound_died);
        if(!racer && randInt(1, 5)==1){
            if(ped)
                getWorld()->addHealing(this);
            else
                getWorld()->addOil(this);
        }
        getWorld()->increaseScore(points);
        return;
    }
    getWorld()->playSound(sound_hurt);
}

//Human
void HumanPed::overDiff()
{
    getWorld()->decLives();
}

void HumanPed::damageByWater()
{
    setHoriS(-getHoriS()+(-1*getHoriS()));
    //need to double check
    setDirection(getDirection()+180);
    getWorld()->playSound(SOUND_PED_HURT);
}

//zombie
void ZombiePed::overDiff()
{
    getWorld()->getPlayer()->demageRacer(5);
    demageZombie(5, true, SOUND_PED_HURT, SOUND_PED_DIE, true, 150);
}
void ZombiePed::zombiePedDiff()
{
    double racerX = getWorld()->getPlayer()->getX();
    double racerY = getWorld()->getPlayer()->getY();
    if(getX()>=racerX-30 && getX()<=racerX+30 && getY()>racerY){
        setDirection(270);
        if(getX()<racerX){
            setHoriS(-getHoriS()+1);
        }
        else if(getX()>racerX){
            setHoriS(-getHoriS()-1);
        }
        else{
            setHoriS(-getHoriS());
        }
        if(tickGrunt<=0){
            getWorld()->playSound(SOUND_ZOMBIE_ATTACK);
            tickGrunt=20;
        }
    }
}

void ZombiePed::damageByWater()
{
    demageZombie(1, false, SOUND_PED_HURT, SOUND_PED_DIE, true, 150);
}

//zombie cab
void ZombieCab::overDiff()
{
    if(damagedRacer)
        return;
    getWorld()->playSound(SOUND_VEHICLE_CRASH);
    getWorld()->getPlayer()->demageRacer(20);
    double racerX = getWorld()->getPlayer()->getX();
    if(getX()<= racerX){
        setHoriS(-getHoriS()-5);
        setDirection(120 + randInt(0, 19));
    }
    else{
        setHoriS(-getHoriS()+5);
        setDirection(60 - randInt(0, 19));
    }
    damagedRacer = true;
}

void ZombieCab::cabDiff()
{
    double Ycoord = getY();
    int lane = onWhichLean();
    Actor* frontCloest = getWorld()->avoidActor(lane,Ycoord,true);
    Actor* behindCloest = getWorld()->avoidActor(lane,Ycoord,false);
    if((getVerS()>getWorld()->getPlayer()->getVerS()) && (frontCloest!=nullptr)&&(frontCloest->getY()<(getY()+96))){
        setVerS(-0.5);
        return;
    }
    if((getVerS()<=getWorld()->getPlayer()->getVerS()) && (behindCloest!=nullptr)&&(behindCloest->getY()>(getY()-96))&&(behindCloest!=getWorld()->getPlayer())){
        setVerS(0.5);
        return;
    }
}

void ZombieCab::damageByWater()
{
    demageZombie(1, false, SOUND_VEHICLE_HURT, SOUND_VEHICLE_DIE, false, 200);
}

//Projectile
void Projectile::doSomething()
{
    if(!isLive())
        return;
    //Check active
    if(getWorld()->waterOverlap(this)!=nullptr){
        getWorld()->waterOverlap(this)->damageByWater();
        notLive();
        return;
    }
    moveForward(SPRITE_HEIGHT);
    moved = moved + SPRITE_HEIGHT;
    if(offScreen()){
        notLive();
        return;
    }
    if(moved >= maxDis){
        notLive();
        return;
    }
}
