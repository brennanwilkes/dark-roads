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
	
	dead=false;

	lore="";
	
	handid=0;
	hand = {" "};
	craft = {"",""};
	
	inventory["/"] = 0;
	inventory["."] = 0;
	inventory["="] = 0;
	inventory["A"] = 0;
	inventory["#"] = 0;
	inventory["o"] = 0;
	inventory["S"] = 0;
	
	max_inv["/"] = 5;
	max_inv["."] = 2;
	max_inv["="] = 4;
	max_inv["A"] = 1;
	max_inv["#"] = 2;
	max_inv["o"] = 1;
	max_inv["S"] = 1;
	
	/*
	inv_codes["/"]=0;
	inv_codes["."]=1;
	inv_codes[","]=2;
	inv_codes["="]=3;
	inv_codes["A"]=4;
	*/
	
	last_dir=0;
	
	
}


void Player::tick(){
	//float mult=1;
	
	//bool move=false;
}


void Player::remove(std::string chr){
	int indx = 0;
	
	player.inventory[chr]--;

	if(player.inventory[chr]==0){

		for(unsigned int i=0; i<player.hand.size(); i++){
			if(player.hand[i]==chr){
				indx = i;
				break;
			}
		}
		player.hand.erase(player.hand.begin()+indx);
		
		if(player.handid >= indx){
			player.handid--;
		}
	}
}


bool Player::add(std::string chr){
	if(player.inventory[chr]<player.max_inv[chr]){
		if(player.inventory[chr]==0){
			player.hand.push_back(chr);
		}
		player.inventory[chr]++;
		return true;
	}
	return false;
}















