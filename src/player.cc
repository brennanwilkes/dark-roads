#include "player.hpp"
#include "gameObject.hpp"
#include "global.hpp"

Player::Player() : GameObject() {}

void Player::set_up(){
	
	x=0;
	y=0;
	
	id=0;
	
	sprite=sf::CircleShape(10.f);
	sprite.setFillColor(sf::Color::Green);
	
	
	keyPress["W"]=false;
	keyPress["S"]=false;
	keyPress["A"]=false;
	keyPress["D"]=false;
	
}

void Player::check_keys(sf::Event e){
	if(e.type==sf::Event::KeyPressed){
		if(e.key.code==sf::Keyboard::A){
			keyPress["A"]=true;
		}
		if(e.key.code==sf::Keyboard::D){
			keyPress["D"]=true;
		}
		if(e.key.code==sf::Keyboard::W){
			keyPress["W"]=true;
		}
		if(e.key.code==sf::Keyboard::S){
			keyPress["S"]=true;
		}
	}
	else if(e.type==sf::Event::KeyReleased){
		if(e.key.code==sf::Keyboard::A){
			keyPress["A"]=false;
		}
		if(e.key.code==sf::Keyboard::D){
			keyPress["D"]=false;
		}
		if(e.key.code==sf::Keyboard::W){
			keyPress["W"]=false;
		}
		if(e.key.code==sf::Keyboard::S){
			keyPress["S"]=false;
		}
	}
}

void Player::tick(){
	if(player.keyPress["A"]){
		x=x-0.1;
	}
	if(player.keyPress["D"]){
		x=x+0.1;
	}
	if(player.keyPress["W"]){
		y=y-0.1;
	}
	if(player.keyPress["S"]){
		y=y+0.1;
	}
	
	
	sprite.setPosition(x,y);
}


















