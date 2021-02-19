#include "StudentWorld.h"
#include "GameConstants.h"
#include <string>
#include <iostream>
#include <sstream>

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
        BorderLine* pr = new BorderLine(IID_YELLOW_BORDER_LINE, LEFT_EDGE,j * SPRITE_HEIGHT,this,false);
        actors.push_back(pr);
    }
    for (int j=0; j<N;j++){
        BorderLine* pr = new BorderLine(IID_YELLOW_BORDER_LINE, RIGHT_EDGE,j * SPRITE_HEIGHT,this,false);
        actors.push_back(pr);
    }
    int M = VIEW_HEIGHT / (4*SPRITE_HEIGHT);
    for (int j=0; j<M;j++){
        BorderLine* pr = new BorderLine(IID_WHITE_BORDER_LINE, LEFT_EDGE + ROAD_WIDTH/3,j * (4*SPRITE_HEIGHT),this,true);
        actors.push_back(pr);
    }
    for (int j=0; j<M;j++){
        BorderLine* pr = new BorderLine(IID_WHITE_BORDER_LINE, RIGHT_EDGE - ROAD_WIDTH/3,j * (4*SPRITE_HEIGHT),this,true);
        actors.push_back(pr);
    }
    lastWhiteY = (M-1)* (4*SPRITE_HEIGHT);
    return GWSTATUS_CONTINUE_GAME;
}

int StudentWorld::move()
{
    // This code is here merely to allow the game to build, run, and terminate after you hit enter.
    // Notice that the return value GWSTATUS_PLAYER_DIED will cause our framework to end the current level.
    player->doSomething();
    
    list<Actor*>:: iterator it;
    for(it = actors.begin(); it!=actors.end();it++){
        if((*it)->isLive()){
            (*it)->doSomething();
        }
    }
    
    //Remove dead
    for(it = actors.begin(); it!=actors.end();){
        if(!(*it)->isLive()){
            delete *it;
            it = actors.erase(it);
        }
        else
            it++;
    }
    
    //Add new BorderLine
    double new_border_y = VIEW_HEIGHT - SPRITE_HEIGHT;
    it = actors.end();
    for(; it!=actors.begin();){
        it--;
        if((*it)->isWhiteLine())
            break;
    }
    
    lastWhiteY = lastWhiteY + (*it)->getVerS()-player->getVerS();
    double delta_y = new_border_y - lastWhiteY;
    //double delta_y = lastWhiteY;
    if(delta_y >= SPRITE_HEIGHT){
        BorderLine* pr = new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH/2,new_border_y,this,false);
        actors.push_back(pr);
        BorderLine* pr2 = new BorderLine(IID_YELLOW_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH/2,new_border_y,this,false);
        actors.push_back(pr2);
    }
    if(delta_y >= 4*SPRITE_HEIGHT){
        BorderLine* wh = new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER - ROAD_WIDTH / 2 + ROAD_WIDTH/3,new_border_y,this,true);
        actors.push_back(wh);
        BorderLine* wh2 = new BorderLine(IID_WHITE_BORDER_LINE, ROAD_CENTER + ROAD_WIDTH / 2 - ROAD_WIDTH/3,new_border_y,this,true);
        actors.push_back(wh2);
        lastWhiteY  = new_border_y;
    }
    
    //Display
    int score = getScore();
    int level = getLevel();
    int souls = 5;
    int lives = getLives();
    int health = player->getHealth();
    int sprays = player->getSprays();
    int bonus = 500;
    ostringstream oss;
    oss << "Score: "<<score<<"  Lvl: "<<level<<"  Souls2Save: "<<souls<<"  Lives: "<<lives<<"  Health: "<<health <<"  Sprays: "<<sprays<<"  Bonus: "<<bonus;
    string s=oss.str();
    setGameStatText(s);
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


