#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor:public GraphObject
{
public:
    Actor(int imageID, double startX, double startY,int startDirection, double size, int depth, int vertSpeed, int horiSpeed):
    GraphObject(imageID, startX, startY, startDirection, size, depth)
    {
        vertSpeed = vertSpeed;
        horiSpeed = horiSpeed;
    }; //constructor
    virtual void doSomething(){};
    virtual bool isAlive()
    {return (0);};
    bool checkOverlap();
private:
    Actor* other;
    int vertSpeed;
    int horiSpeed;
};

class GhostRacer: public Actor
{
public:
    GhostRacer():
    Actor(IID_GHOST_RACER,128,32,90,4.0,0,0,0)
    {
        holy_water = 10;
        health = 100;
    };
    virtual bool isAlive();
    virtual void doSomething(){};
private:
    int holy_water;
    int health;
};

class BorderLine: public Actor
{
public:
    BorderLine(int imageID, double startX, double startY):
    Actor(imageID, startX, startY,0,2.0,1,-4,0)
    {};
    virtual bool isAlive(){ return false;};
    virtual void doSomething() {};
private:
    
};

#endif // ACTOR_H_
