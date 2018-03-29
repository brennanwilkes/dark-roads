#ifndef ENEMY_H
#define ENEMY_H

#include "gameObject.hpp"
#include <map>
#include <string>

class Enemy : public GameObject{
public:
	Enemy(float rad);
	
	void set_up(int xx,int yy,int idd);
	
	void tick();
	
	bool interact;
	bool change;
	
	int rand_mov_left;
	int rand_mov_dir;
	
	bool hostile;
	bool combat;
	
	bool dead;	//EVENTUALLY this should be replaced with a deconstructor
	
};
#endif
