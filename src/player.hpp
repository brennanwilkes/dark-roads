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
	int sharp;
	int wood;
	
	int max_sticks;
	int max_stones;
	int max_sharp;
	int max_wood;
	
	int handid;
	std::vector<std::string> hand;
	std::vector<std::string> craft;
	
	void remove(std::string);
	void add(std::string);
	
};
#endif
