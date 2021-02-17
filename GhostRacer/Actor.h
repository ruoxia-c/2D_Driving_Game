#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor:public GraphObject
{
public:
    Actor(int imageID, double startX, double startY,int startDirection, double size, int depth):
    GraphObject(imageID, startX, startY, startDirection, size, depth)
    {}; //constructor
    virtual void doSomething(){};
    virtual bool isAlive()
    {return (0);};
    bool checkOverlap();
private:
    Actor* other;
};

class BorderLine: public Actor
{
public:
    BorderLine();
private:
    
};

class GhostRacer: public Actor
{
public:
    GhostRacer();
    virtual void doSomething();
private:
};
#endif // ACTOR_H_
