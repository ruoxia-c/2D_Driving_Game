#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor:public GraphObject
{
public:
    Actor(int imageID, double startX, double startY,int startDirection, double size, int depth, int vertSpeed, int horiSpeed, StudentWorld* cp,bool alive,bool worthAviod):
    GraphObject(imageID, startX, startY, startDirection, size, depth),m_world(cp),vertSpeed(vertSpeed),horiSpeed(horiSpeed),liveState(alive),worthAvoid(worthAviod)
    { }; //constructor
    virtual void doSomething()=0;
    virtual bool isWhiteLine(){ return false;};
    bool isLive(){
        return liveState;
    }
    int onWhichLean();
    int getHoriS(){ return horiSpeed;}
    int getVerS(){ return vertSpeed;}
    bool needAvoid(){return worthAvoid;};
protected:
    StudentWorld* getWorld(){return m_world;}
    void setHoriS(int chan){ horiSpeed = horiSpeed + chan;}
    void setVerS(int chan){ vertSpeed = vertSpeed + chan;}
    void notLive(){ liveState = false;};
    
    void moveSameHori(); //only vertical speed change
    bool offScreen();
    bool checkOverlap(Actor* cp);
private:
    StudentWorld* m_world;
    bool liveState;
    int vertSpeed;
    int horiSpeed;
    bool worthAvoid;
};

class GhostRacer: public Actor
{
public:
    GhostRacer(StudentWorld* cp):
    Actor(IID_GHOST_RACER,128,32,90,4.0,0,0,0,cp,true,true)
    {
        holyWater = 10;
        health = 100;
    };
    virtual void doSomething();
    void demageRacer(int hitPoint);
    int getHealth(){ return health;};
    int getSprays(){ return holyWater;};
    void spun();
    void changeHealth(int val){ health = health + val;};
    void changeWater(int val){ holyWater = holyWater+val;};
private:
    void moveAlgorithm();
    int holyWater;
    int health;
};

class BorderLine: public Actor
{
public:
    BorderLine(int imageID, double startX, double startY,StudentWorld* cp, bool isWhite):
    Actor(imageID, startX, startY,0,2.0,2,-4,0,cp,true,false)
    { isWhite = isWhite;};
    virtual void doSomething();
    virtual bool isWhiteLine(){ return isWhite;}
private:
    bool isWhite;
};

class Goodies: public Actor
{
public:
    Goodies(int imageID, double startX, double startY,int startDirection, double size, int depth, int vertSpeed, int horiSpeed, StudentWorld* cp,int playSound,int increaseScor,bool isOil):
    Actor(imageID, startX, startY, startDirection, size, depth, vertSpeed, horiSpeed,cp,true,false),playSound(playSound),inScore(increaseScor),isOil(isOil)
    {};
    virtual void doSomething();
private:
    bool isOil;
    int playSound;
    int inScore;
    virtual void overDiff()=0; //different thing when overlap with player
    virtual void otherDiff()=0; //other different thing
};

class Soul: public Goodies
{
public:
    Soul(double startX, double startY,StudentWorld* cp):
    Goodies(IID_SOUL_GOODIE,startX, startY,0,4.0,2,-4,0,cp,SOUND_GOT_SOUL,100,false)
    {}
private:
    virtual void overDiff();
    virtual void otherDiff();
};

class Healing: public Goodies
{
public:
    Healing(double startX, double startY,StudentWorld* cp):
    Goodies(IID_HEAL_GOODIE,startX, startY,0,1.0,2,-4,0,cp,SOUND_GOT_GOODIE,250,false)
    {};
private:
    virtual void overDiff();
    virtual void otherDiff(){};
};

class HolyWater: public Goodies
{
public:
    HolyWater(double startX, double startY,StudentWorld* cp):
    Goodies(IID_HOLY_WATER_GOODIE,startX, startY,90,2.0,2,-4,0,cp,SOUND_GOT_GOODIE,50,false)
    {};
private:
    virtual void overDiff();
    virtual void otherDiff(){};
};

class OilSlick: public Goodies
{
public:
    OilSlick(double startX, double startY,StudentWorld* cp):
    Goodies(IID_OIL_SLICK, startX, startY, 0,randInt(2,5),2,-4,0,cp,SOUND_OIL_SLICK,0,true)
    {};
private:
    virtual void overDiff();
    virtual void otherDiff(){};
};

//pedestrians
class Pedestrain: public Actor
{
public:
    Pedestrain(int imageID, double startX, double startY,int startDirection, double size, int depth, int vertSpeed, int horiSpeed, StudentWorld* cp,int planMove,int hitPoint,bool isCab):
    Actor(imageID, startX, startY, startDirection, size, depth, vertSpeed, horiSpeed,cp,true,true),planMove(planMove),hitPoint(hitPoint),isCab(isCab)
    {};
    virtual void doSomething();
    void demage(int hit){ hitPoint = hitPoint-hit;};
    int getPoint(){ return hitPoint;};
private:
    virtual void overDiff()=0;
    virtual void zombiePedDiff()=0;
    virtual void cabDiff()=0;
    void PedPlan();
    void CabPlan();
    int planMove;
    int hitPoint;
    bool isCab;
};

class HumanPed: public Pedestrain
{
public:
    HumanPed(double startX, double startY,StudentWorld* cp):
    Pedestrain(IID_HUMAN_PED, startX, startY, 0, 2.0, 0, -4, 0, cp, 0, 2,false)
    {}
private:
    virtual void overDiff();
    virtual void zombiePedDiff(){};
    virtual void cabDiff(){};
};

class ZombiePed:public Pedestrain
{
public:
    ZombiePed(double startX, double startY,StudentWorld* cp):
    Pedestrain(IID_ZOMBIE_PED,startX, startY,0,3.0,0,-4,0,cp,0,2,false)
    { tickGrunt = 0;}
private:
    int tickGrunt;
    virtual void overDiff();
    virtual void zombiePedDiff();
    virtual void cabDiff(){};
    
    void demagePed(int hit,bool racer);
};

class ZombieCab: public Pedestrain
{
public:
    ZombieCab(double startX, double startY,StudentWorld* cp):
    Pedestrain(IID_ZOMBIE_CAB,startX, startY,90,4.0,0,0,0,cp,0,3,true)
    { damagedRacer = false;}
private:
    virtual void overDiff();
    virtual void zombiePedDiff(){};
    virtual void cabDiff();
    
    bool damagedRacer;
};

#endif // ACTOR_H_
