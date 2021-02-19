#ifndef ACTOR_H_
#define ACTOR_H_

#include "GraphObject.h"
class StudentWorld;

// Students:  Add code to this file, Actor.cpp, StudentWorld.h, and StudentWorld.cpp
class Actor:public GraphObject
{
public:
    Actor(int imageID, double startX, double startY,int startDirection, double size, int depth, double vertSpeed, double horiSpeed, StudentWorld* cp):
    GraphObject(imageID, startX, startY, startDirection, size, depth),m_world(cp)
    {
        liveState = true;
        vertSpeed = vertSpeed;
        horiSpeed = horiSpeed;
    }; //constructor
    virtual void doSomething(){};
    virtual bool isWhiteLine(){ return false;};
    bool isLive(){
        return liveState;
    }
    double getHoriS(){ return horiSpeed;}
    double getVerS(){ return vertSpeed;}
protected:
    StudentWorld* getWorld(){return m_world;}
    void desHoriS(double chan){ horiSpeed = horiSpeed - chan;}
    void insHoriS(double chan){ horiSpeed = horiSpeed + chan;}
    void desVerS(double chan){ vertSpeed = vertSpeed - chan;}
    void insVerS(double chan){ vertSpeed = vertSpeed + chan;}
    
    void notLive(){ liveState = false;};
    //bool checkOverlap(Actor* cp);
private:
    StudentWorld* m_world;
    bool liveState;
    double vertSpeed;
    double horiSpeed;
};

class GhostRacer: public Actor
{
public:
    GhostRacer(StudentWorld* cp):
    Actor(IID_GHOST_RACER,128,32,90,4.0,0,0,0,cp)
    {
        holyWater = 10;
        health = 100;
    };
    virtual void doSomething();
    void demageRacer(int hitPoint);
    int getHealth(){ return health;};
    int getSprays(){ return holyWater;};
private:
    void moveAlgorithm();
    int holyWater;
    int health;
};

class BorderLine: public Actor
{
public:
    BorderLine(int imageID, double startX, double startY,StudentWorld* cp, bool isWhite):
    Actor(imageID, startX, startY,0,2.0,2,-4,0,cp)
    { isWhite = isWhite;};
    virtual void doSomething();
    virtual bool isWhiteLine(){ return isWhite;}
private:
    bool isWhite;
};

#endif // ACTOR_H_
