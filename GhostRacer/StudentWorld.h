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
private:
    GhostRacer* player;
    list<Actor*> actors;
    double lastWhiteY;
    int saveSoul;
    const double LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    const double RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    bool addActor(int maxChance);
};

#endif // STUDENTWORLD_H_
