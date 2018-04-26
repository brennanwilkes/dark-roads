#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <iostream>
#include <cmath>

#include "player.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"
#include "terrain.hpp"

extern int stage;	
extern int text_delay;	
extern Player player;
extern inline float getDis(GameObject* src,GameObject* dest);
extern inline float getDis(GameObject* src);
extern inline float getDis(GameObject* src,int x2,int y2);
extern inline float getDis(int x1,int y1,int x2,int y2);
extern std::vector<std::vector<std::string> > village;

extern std::vector<GameObject*> dudes;


#endif
