#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.hpp"
#include <map>
#include <vector>
#include <string>

class Player : public GameObject{
public:
	Player();
	void set_up();
	
	
	void tick();
	int cx;
	int cy;
	bool water;
	int sticks;
	int stones;
	
};
#endif
