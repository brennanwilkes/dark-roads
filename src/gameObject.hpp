#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <map>
#include <string>

class GameObject{
public:
	GameObject();
	//virtual ~GameObject();
	//virtual void set_up();
	float x;
	float y;
	int id;
	int health;
	std::string img;
	
	
	
	
};

#endif
