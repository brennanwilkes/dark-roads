#include "player.hpp"
#include "gameObject.hpp"
#include "global.hpp"

Player::Player(float rad) : GameObject(rad) {}

void Player::set_up(){
	cx=0;
	cy=0;
	
	x=0;
	y=0;
	
	id=0;
	
	health=100;
	sprite.setPosition(400,400);
	sprite.setFillColor(sf::Color::Green);
	
	
	keyPress["W"]=false;
	keyPress["S"]=false;
	keyPress["A"]=false;
	keyPress["D"]=false;
	keyPress["LSHIFT"]=false;
	keyPress["LCONTROL"]=false;
	
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
		if(e.key.code==sf::Keyboard::LShift){
			keyPress["LSHIFT"]=true;
		}
		if(e.key.code==sf::Keyboard::LControl){
			keyPress["LCONTROL"]=true;
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
		if(e.key.code==sf::Keyboard::LShift){
			keyPress["LSHIFT"]=false;
		}
		if(e.key.code==sf::Keyboard::LControl){
			keyPress["LCONTROL"]=false;
		}
	}
}

void Player::tick(){
	float mult=1;
	if(keyPress["LCONTROL"]){
		mult=0.5;
	}
	else if(keyPress["LSHIFT"]){
		mult=2;
	}
	bool move=false;
	
	
	if(player.keyPress["A"]){
		x=x-(0.08*mult);
		move=true;
	}
	if(player.keyPress["D"]){
		x=x+(0.08*mult);
		move=true;
	}
	if(player.keyPress["W"]){
		y=y-(0.08*mult);
		move=true;
	}
	if(player.keyPress["S"]){
		y=y+(0.08*mult);
		move=true;
	}
	
	cx=(int)floor((x+400)/800.0);
	cy=(int)floor((y+400)/800.0);
	
	//sprite.setPosition(x,y);
	//sprite.setPosition(400,400);		//set this to centre of screen
	
	
	
	
}


















