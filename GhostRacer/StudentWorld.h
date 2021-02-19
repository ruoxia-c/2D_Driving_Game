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
private:
    GhostRacer* player;
    list<Actor*> actors;
    double lastWhiteY;
    const double LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    const double RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    bool addGoodies(int maxChance);
};

#endif // STUDENTWORLD_H_
