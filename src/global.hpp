#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <iostream>
#include <cmath>
#include <map>

#include "player.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "terrain.hpp"

extern int stage;
extern int scene;
extern int text_delay;	
extern int xMax;
extern int yMax;
extern Player player;
extern inline float getDis(GameObject* src,GameObject* dest);
extern inline float getDis(GameObject* src);
extern inline float getDis(GameObject* src,int x2,int y2);
extern inline float getDis(int x1,int y1,int x2,int y2);
extern std::vector<std::vector<std::string> > village;
extern std::vector<std::vector<int> > tree_fire;
extern std::vector<int> hint_staging;
extern std::map<std::vector<int>,std::string> exmap;

extern std::vector<GameObject*> dudes;


#endif
