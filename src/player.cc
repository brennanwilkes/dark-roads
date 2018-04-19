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
	
	//sticks=0;
	//stones=0;
	//sharp=0;
	//wood=0;
	handid=0;
	hand = {" "};//,"/","."};
	craft = {"",""};
	
	//max_sticks=5;
	//max_stones=5;
	//max_sharp=2;
	//max_wood=3;
	
	
	inventory={0,0,0,0,0};
	max_inv={5,5,2,3,1};
	
	inv_codes["/"]=0;
	inv_codes["."]=1;
	inv_codes[","]=2;
	inv_codes["="]=3;
	inv_codes["A"]=4;
	
	
	
	last_dir=0;
	
	fire=-1;
	
}


void Player::tick(){
	//float mult=1;
	
	//bool move=false;
}


void Player::remove(std::string chr){
	std::vector<std::string> tmp={};
	int itmInd=player.hand.size();
	
	player.inventory[player.inv_codes[chr]]=player.inventory[player.inv_codes[chr]]-1;
	if(player.inventory[player.inv_codes[chr]]==0){
		for(unsigned int i=0;i<player.hand.size();i++){
			if(player.hand[i]!=chr){
				tmp.push_back(player.hand[i]);
			}
			else{
				itmInd=i;
			}
		}
		player.hand=tmp;
		if(player.handid>=itmInd){
			player.handid=player.handid-1;
		}
	}
}


bool Player::add(std::string chr){
	if(player.inventory[player.inv_codes[chr]]<player.max_inv[player.inv_codes[chr]]){
		if(player.inventory[player.inv_codes[chr]]==0){
			player.hand.push_back(chr);
		}
		player.inventory[player.inv_codes[chr]]=player.inventory[player.inv_codes[chr]]+1;
		return true;
	}
	return false;
}















