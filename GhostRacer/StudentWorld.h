#ifndef STUDENTWORLD_H_
#define STUDENTWORLD_H_

#include "GameWorld.h"
#include "Actor.h"
#include <string>
#include <list>
using namespace std;

// Students:  Add code to this file, StudentWorld.cpp, Actor.h, and Actor.cpp

class StudentWorld : public GameWorld
{
public:
    StudentWorld(std::string assetPath);
    ~ StudentWorld();
    virtual int init();
    virtual int move();
    virtual void cleanUp();
    GhostRacer* getPlayer(){ return player;};
    void saveNewSoul(){ saveSoul++; };
    void addHealing(Actor* cp);
    void addOil(Actor* cp);
    void addSpray(Actor* cp);
    Actor* avoidActor(int lane,double Ycoord,bool front);
    Actor* waterOverlap(Actor* cp);
private:
    GhostRacer* player;
    list<Actor*> actors;
    double lastWhiteY;
    int saveSoul;
    int bonusPoint;
    const double LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    const double RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    bool addActor(int maxChance);
    void addCab();
    double centerOfLane(int lane);
};

#endif // STUDENTWORLD_H_
