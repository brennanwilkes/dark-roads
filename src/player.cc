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
	wood=0;
	handid=0;
	hand = {" "};//,"/","."};
	craft = {"",""};
	
	max_sticks=5;
	max_stones=5;
	max_wood=3;
	
}


void Player::tick(){
	float mult=1;
	
	bool move=false;
	
	
	
	
	
}


void Player::remove(std::string chr){
	std::vector<std::string> tmp={};
	int tmp2;
	if(chr=="/"){
		player.sticks=player.sticks-1;
		if(player.sticks==0){
			for(unsigned int i=0;i<player.hand.size();i++){
				if(player.hand[i]!="/"){
					tmp.push_back(player.hand[i]);
				}
				else{
					tmp2=i;
				}
			}
			player.hand=tmp;
			if(player.handid>=tmp2){
				player.handid=player.handid-1;
			}
		}
	}
	else if(chr=="."){
		player.stones=player.stones-1;
		if(player.stones==0){
			for(unsigned int i=0;i<player.hand.size();i++){
				if(player.hand[i]!="."){
					tmp.push_back(player.hand[i]);
				}
				else{
					tmp2=i;
				}
			}
			player.hand=tmp;
			if(player.handid>=tmp2){
				player.handid=player.handid-1;
			}
		}
	}
	else if(chr=="WOOD"){
		
	}
	
	
	
}

void Player::add(std::string chr){
	if(chr=="/"){
		if(player.sticks==0){
			player.hand.push_back("/");
		}
		player.sticks=player.sticks+1;
	}
	else if(chr=="."){
		if(player.stones==0){
			player.hand.push_back(".");
		}
		player.stones=player.stones+1;
	}
	
	
	
}















