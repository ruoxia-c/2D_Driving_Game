#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
using namespace std;

GameWorld* createStudentWorld(string assetPath)
{
	return new StudentWorld(assetPath);
}

// Students:  Add code to this file, StudentWorld.h, Actor.h, and Actor.cpp

StudentWorld::StudentWorld(string assetPath)
: GameWorld(assetPath)
{
}

int StudentWorld::init()
{
    player = new GhostRacer(this);
    //add borderlines
    int N = VIEW_HEIGHT / SPRITE_HEIGHT;
    double LEFT_EDGE = ROAD_CENTER - ROAD_WIDTH/2;
    double RIGHT_EDGE = ROAD_CENTER + ROAD_WIDTH/2;
    for (int j=0; j<N;j++){
        BorderLine* pr = new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE,j * SPRITE_HEIGHT,this);
        actors.push_back(pr);
    }
    for (int j=0; j<N;j++){
        BorderLine* pr = new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE,j * SPRITE_HEIGHT,this);
        actors.push_back(pr);
    }
    int M = VIEW_HEIGHT / (4*SPRITE_HEIGHT);
    for (int j=0; j<M;j++){
        BorderLine* pr = new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3,j * (4*SPRITE_HEIGHT),this);
        actors.push_back(pr);
    }
    for (int j=0; j<M;j++){
        BorderLine* pr = new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3,j * (4*SPRITE_HEIGHT),this);
        actors.push_back(pr);
    }
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    player->doSomething();
    decLives();
    return GWSTATUS_CONTINUE_GAME;
}

void StudentWorld::cleanUp()
{
    delete player;
    list<Actor*>:: iterator it;
    for(it = actors.begin(); it!=actors.end();){
        delete *it;
        it = actors.erase(it);
    }
}

StudentWorld::~StudentWorld()
{
    cleanUp();
}


