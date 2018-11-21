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
	bool dead;
	int dead_shift;
	
	bool hint;
	
	void tick();
	int cx;
	int cy;
	bool water;
	
	std::map<std::vector<int>,int> fire;
	std::map<std::vector<int>,int> trap;
	
	int last_dir;
	
	int handid;
	std::vector<std::string> hand;
	std::vector<std::string> craft;

	std::map <std::string,int> inventory;
	std::map <std::string,int> max_inv;
		
	void remove(std::string);
	bool add(std::string);
	
	std::string lore;
	
	
	bool place();
	int move(int,int,int,int,int);
	
};
#endif
