#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"
#include <random>

Enemy::Enemy() : GameObject() {}

void Enemy::set_up(int xx,int yy,int idd){
	
	x=xx;
	y=yy;
	
	id=idd;
	

	
	interact=false;
	change=false;
	rand_mov_left=0;
	rand_mov_dir=0;
	
	
	hostile=true;		//	so these should be determined
	combat=true;		//	on a case to case basis
	
	health=25;
	dead=false;	
}

void Enemy::tick(){
	
	if(health<=0){
		dead=true;
	}
	
	
}


















