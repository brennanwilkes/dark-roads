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
	
	int fire;
	
	int last_dir;
	
	int handid;
	std::vector<std::string> hand;
	std::vector<std::string> craft;
	
	std::vector<int> inventory;
	std::vector<int> max_inv;
	
	std::map<std::string,int> inv_codes;
	
	void remove(std::string);
	void add(std::string);
	
};
#endif
