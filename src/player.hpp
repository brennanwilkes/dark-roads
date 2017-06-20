#ifndef PLAYER_H
#define PLAYER_H

#include "gameObject.hpp"
#include <map>
#include <string>
#include <SFML/Graphics.hpp>

class Player : public GameObject{
public:
	Player();
	void set_up();
	
	std::map<std::string,bool> keyPress;
	
	void check_keys(sf::Event e);
	
	sf::CircleShape sprite;		//EVENTUALLY CHANGE THIS TO SPRITES
	
	void tick();
	
};
#endif
