#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <map>
#include <SFML/Graphics.hpp>

class GameObject{
public:
	GameObject(float rad);
	//virtual ~GameObject();
	//virtual void set_up();
	float x;
	float y;
	float r;
	int id;
	int health;
	
	sf::CircleShape sprite;		//EVENTUALLY CHANGE THIS TO SPRITES
	
	
	
};

#endif
