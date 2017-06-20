#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"

Enemy::Enemy(float rad) : GameObject(rad) {}

void Enemy::set_up(int xx,int yy,int idd){
	
	x=xx;
	y=yy;
	
	id=idd;
	
	sprite.setFillColor(sf::Color::Red);
	
	interact=false;
	change=false;
	
}

void Enemy::tick(){
	
	sprite.setPosition(x,y);
	
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
}


















