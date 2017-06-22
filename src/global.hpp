#ifndef GLOBAL_H
#define GLOBAL_H

#include <vector>
#include <iostream>

#include "player.hpp"
#include "enemy.hpp"
#include "gameObject.hpp"

extern int scene;	//Just an example on how to do a global
extern Player player;
extern std::vector<Enemy*> dudes;
extern inline float getDis(GameObject* src,GameObject* dest);
extern inline float getDis(GameObject* src);
extern inline float getDis(GameObject* src,int x2,int y2);
extern inline float getDis(int x1,int y1,int x2,int y2);
#endif
