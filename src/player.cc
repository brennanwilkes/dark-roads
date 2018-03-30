#include "player.hpp"
#include "gameObject.hpp"
#include "global.hpp"

Player::Player() : GameObject() {}

void Player::set_up(){
	cx=0;
	cy=0;
	
	x=0;
	y=0;
	
	id=0;
	
	health=100;
	
	img = "@";
	water=false;
	
	sticks=0;
	stones=0;
	
	
	
}


void Player::tick(){
	float mult=1;
	
	bool move=false;
	
	
	
	
	
}


















