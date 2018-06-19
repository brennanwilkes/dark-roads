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
	
	inventory[chr]--;

	if(inventory[chr]==0){

		for(unsigned int i=0; i<hand.size(); i++){
			if(hand[i]==chr){
				indx = i;
				break;
			}
		}
		hand.erase(hand.begin()+indx);
		
		if(handid >= indx){
			handid--;
		}
	}
}


bool Player::add(std::string chr){
	if(inventory[chr]<max_inv[chr]){
		if(inventory[chr]==0){
			hand.push_back(chr);
		}
		inventory[chr]++;
		return true;
	}
	return false;
}




bool Player::place(){
	
	int hand_xs=0;
	int hand_ys=0;
	if(last_dir==0){
		hand_ys=-1;		//hand up
	}
	else if(last_dir==1){
		hand_xs=-1;		//hand left
	}
	else if(last_dir==2){
		hand_xs=1;		//hand right
	}
	else if(last_dir==3){
		hand_ys=1;		//hand down
	}
	if(hand[handid]=="#"){
		village[y+hand_ys][x+hand_xs]="#";
		remove("#");
	}
	else if(hand[handid]=="o"){
		village[y+hand_ys][x+hand_xs]="O";
		fire[{y+hand_ys,x+hand_xs}]=16;
		if(stage<3){
			stage=3;
		}
		remove("o");
		return true;
	}
	return false;
}










