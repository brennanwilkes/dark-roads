#ifndef GAME_OBJ_H
#define GAME_OBJ_H

#include <map>
#include <string>

class GameObject{
public:
	GameObject();
	~GameObject();
	//virtual void set_up();
	int x;
	int y;
	int id;
	int health;
	std::string img;
	
	
	virtual void tick();
	
	
};

#endif
