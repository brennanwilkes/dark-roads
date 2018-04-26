#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"
#include <random>

Enemy::Enemy() : GameObject() {}

void Enemy::set_up(int xx,int yy,int idd){
	
	x=xx;
	y=yy;
	
	id=idd;
	
	calc_path(player.y,player.x,village);
	

}

void Enemy::tick(){
	
	
	
	
}

std::vector<std::vector<int> > Enemy::calc_path(int ty,int tx,std::vector<std::vector<std::string> >grid){
	
	
	
	
	
	
	
}
	
	

















