#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.hpp"
#include <map>
#include <vector>
#include <string>

class Player : public GameObject{
public:
	Player(float rad);
	void set_up();
	
	std::map<std::string,bool> keyPress;
	
	void check_keys();
	
	void tick();
	int cx;
	int cy;
	
};
#endif
