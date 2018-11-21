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
	hint=false;

	lore="";
	
	handid=0;
	hand = {" "};
	craft = {"",""};
	
	kills = 0;
	
	inventory["/"] = 0;
	inventory["."] = 0;
	inventory["="] = 0;
	inventory["A"] = 0;
	inventory["#"] = 0;
	inventory["o"] = 0;
	inventory["S"] = 0;
	inventory["O"] = 0;
	inventory["$"] = 0;
	inventory["?"] = 0;
	
	max_inv["/"] = 5;
	max_inv["."] = 2;
	max_inv["="] = 4;
	max_inv["A"] = 1;
	max_inv["#"] = 2;
	max_inv["o"] = 1;
	max_inv["S"] = 1;
	max_inv["O"] = 1;
	max_inv["$"] = 1;
	max_inv["?"] = 3;
	
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
	if(hand[handid]=="$"){
		village[y+hand_ys][x+hand_xs]="$";
		remove("$");
		trap[{y+hand_ys,x+hand_xs}]=1;
	}
	else if(hand[handid]=="o"){
		village[y+hand_ys][x+hand_xs]="o";
		fire[{y+hand_ys,x+hand_xs}]=16;
		if(stage<3){
			stage=3;
		}
		remove("o");
		return true;
	}
	else if(hand[handid]=="O"){
		village[y+hand_ys][x+hand_xs]="O";
		fire[{y+hand_ys,x+hand_xs}]=4;
		if(stage<3){
			stage=3;
		}
		remove("O");
		return true;
	}
	return false;
}


int Player::move(int xs,int ys,int xMax,int yMax,int ts){
	if(y+ys>(yMax-1) || y+ys<0 || x+xs>(xMax-1) ||x+xs<0){
		player.dead=true;
		return -1;
	}
	if(village[y+ys][x+xs]=="_"){
		y=y+ys;
		x=x+xs;
		water=true;
		last_dir=ts;
	}
	
	
	
	if(hand[handid]!=" "){
		last_dir=ts;
		
		if(village[y+ys][x+xs]==" "){
			xs=xs*2;
			ys=ys*2;
		}
	}
	if(y+ys>(yMax-1) || y+ys<0 || x+xs>(xMax-1) || x+xs<0){		//leave screen
		if(stage<4){
			return -1;
		}
		else{			//explore
			return -1;
		}
	}
	
	if(scene==0){
		if(village[y+ys][x+xs]==" "){					//move
			if(xs>1||xs<-1||ys>1||ys<-1){
				xs=xs/2;
				ys=ys/2;
			}
			y=y+ys;
			x=x+xs;
			water=false;
		}
		else if(y+ys==9&&x+xs==20){
			if(add(village[y+ys][x+xs])){
				village[y+ys][x+xs]=" ";				//pickup
			}
		}
		else if(village[y+ys][x+xs]=="/"||village[y+ys][x+xs]=="."||village[y+ys][x+xs]=="S"||village[y+ys][x+xs]=="A"||village[y+ys][x+xs]=="?"){
			if(add(village[y+ys][x+xs])){
				village[y+ys][x+xs]=" ";				//pickup
			}
		}
		else if(village[y+ys][x+xs]==">"){
			if(craft[0]==""&&hand[handid]!=" "){	//craft1
				craft[0]=hand[handid];
				remove(hand[handid]);
			}
			else{
				if(craft[0]!=""){
					add(craft[0]);
				}
				craft[0]="";
			}
		}
		else if(village[y+ys][x+xs]=="<"){				//craft2
			if(craft[1]==""&&hand[handid]!=" "){
				craft[1]=hand[handid];
				remove(hand[handid]);
			}
			else{
				if(craft[1]!=""){
					add(craft[1]);
				}
				craft[1]="";
			}
		}
		else if(village[y+ys][x+xs]=="o"){			//fire
			if(hand[handid]=="/"){
				fire[{y+ys,x+xs}]++;
				remove("/");
			}
			else if(hand[handid]=="="){					
				fire[{y+ys,x+xs}]=fire[{y+ys,x+xs}]+3;
				remove("=");
			}
			else if(hand[handid]=="S"){					
				fire[{y+ys,x+xs}]=fire[{y+ys,x+xs}]+10;
				remove("S");
			}
		}
		else if(village[y+ys][x+xs]=="O"){			//fire
			if(hand[handid]=="S"){					
				fire[{y+ys,x+xs}]=fire[{y+ys,x+xs}]+2;
				remove("S");
			}
		}
		else if(village[y+ys][x+xs]=="$"){			//fire
			if(hand[handid]=="S"){					
				trap[{y+ys,x+xs}]=trap[{y+ys,x+xs}]+1;
				remove("S");
			}
		}
		else if(village[y+ys][x+xs]=="^"&&hand[handid]=="A"){	//tree chop
			village[y+ys][x+xs]=" ";
			if(add("=")){
				if(add("/")){
					add("/");
				}
			}
		
			return 1;			//tree sound
		
		}
		else if(village[y+ys][x+xs]=="#"&&hand[handid]=="A"){	//wall chop
			village[y+ys][x+xs]=" ";
			add("#");
		}
	}
	else if(scene==1){//outsideworld
		if(xs>1||xs<-1||ys>1||ys<-1){
			xs=xs/2;
			ys=ys/2;
		}
		y=y+ys;
		x=x+xs;
		water=false;
	}
	return 0;
}







