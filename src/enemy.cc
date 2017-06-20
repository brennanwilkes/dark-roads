#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"
#include <random>

Enemy::Enemy(float rad) : GameObject(rad) {}

void Enemy::set_up(int xx,int yy,int idd){
	
	x=xx;
	y=yy;
	
	id=idd;
	
	sprite.setFillColor(sf::Color::Red);
	
	interact=false;
	change=false;
	rand_mov_left=0;
	rand_mov_dir=0;
	
}

void Enemy::tick(){
	
	sprite.setPosition(x-player.x,y-player.y);
	
	if(change){
		if(interact){
			sprite.setFillColor(sf::Color::Yellow);
			change=false;
		}
		else{
			sprite.setFillColor(sf::Color::Red);
			change=false;
		}
	}
	if(rand_mov_left>0){
		rand_mov_left--;
		if(rand_mov_dir==1){
			x=x-0.01;
		}
		else if(rand_mov_dir==2){
			x=x+0.01;
		}
		else if(rand_mov_dir==3){
			y=y-0.01;
		}
		else if(rand_mov_dir==4){
			y=y+0.01;
		}	
	}
	float ran = rand()/(float)RAND_MAX;
	if(ran>0.9999){									//LOL THIS IS SO BAD
		if (((ran*10000.0)-9999)>0.75){
			rand_mov_dir=1;
		}
		else if (((ran*10000.0)-9999)>0.5){
			rand_mov_dir=2;
		}
		else if (((ran*10000.0)-9999)>0.35){
			rand_mov_dir=3;
		}
		else{
			rand_mov_dir=4;
		}
		rand_mov_left=5000;
		
	}
	
}


















