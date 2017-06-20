#ifndef ENEMY_H
#define ENEMY_H

#include "gameObject.hpp"
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Enemy : public GameObject{
public:
	Enemy(float rad);
	
	void set_up(int xx,int yy,int idd);
	
	void tick();
	
	bool interact;
	bool change;
	
};
#endif
