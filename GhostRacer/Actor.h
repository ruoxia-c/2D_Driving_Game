#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor:public GraphObject
{
public:
    Actor(int imageID, double startX, double startY,int startDirection, double size, int depth, int vertSpeed, int horiSpeed, StudentWorld* cp,bool liveState):
    GraphObject(imageID, startX, startY, startDirection, size, depth),m_world(cp)
    {
        liveState = liveState;
        vertSpeed = vertSpeed;
        horiSpeed = horiSpeed;
    }; //constructor
    virtual void doSomething(){};
    bool isLive(){
        return liveState;
    }
protected:
    StudentWorld* getWorld(){
        return m_world;
    }
    void changeLive(bool live){
        liveState = live;
    }
    //bool checkOverlap(Actor* cp);
private:
    StudentWorld* m_world;
    bool liveState;
    int vertSpeed;
    int horiSpeed;
};

class GhostRacer: public Actor
{
public:
    GhostRacer(StudentWorld* cp):
    Actor(IID_GHOST_RACER,128,32,90,4.0,0,0,0,cp,true)
    {
        holyWater = 10;
        health = 100;
        m_speed = 0;
    };
    virtual void doSomething();
    void demageRacer(int hitPoint);
    int getHealth(){ return health;};
    int getSprays(){ return holyWater;};
private:
    void moveAlgorithm();
    int holyWater;
    int health;
    double m_speed;
};

class BorderLine: public Actor
{
public:
    BorderLine(int imageID, double startX, double startY,StudentWorld* cp):
    Actor(imageID, startX, startY,0,2.0,1,-4,0,cp,true)
    {};
    virtual void doSomething() {};
private:
    
};

#endif // ACTOR_H_
