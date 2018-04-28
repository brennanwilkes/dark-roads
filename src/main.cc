/*

Summer project for IDS Best Team but probally just Brennan unless other people are interested

DARK ROADS

*/

//C++ Includes
#include <iostream>
#include <map>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <random>

//NCURSESSSSS Includes
#include <ncurses.h>
#include <unistd.h>


//User Includes
#include "player.hpp"
#include "gameObject.hpp"
#include "enemy.hpp"
#include "terrain.hpp"
#include "global.hpp"


using namespace std;

#define CAMPFIRE "O"

#define YMAX 24
#define XMAX 80


int stage;
Player player=Player();
vector<GameObject*> dudes;
int text_delay;

inline float getDis(GameObject* src,GameObject* dest);
inline float getDis(GameObject* src);
inline float getDis(GameObject* src,int x2,int y2);
inline float getDis(int x1,int y1,int x2,int y2);
void clear_screen(WINDOW*);
bool draw(WINDOW*);
int light_distance(int,int);
bool craft(string,string,string);
void tick(WINDOW*);
void stage_check();

unsigned int fire_tick=0;
unsigned int tree_tick=0;

vector<vector<string> > village(YMAX);

vector<vector<string> > recipes={
	{".",".",","},
	{".","=","o"},
	{"/",",","A"},
	{"=","=","#"},
};

//		 0
//		1 2
//		 34



int main(int argc, char *argv[]) {
	
	
	stage=0;
	
	
	srand (time(NULL));
	
	for(int i=0;i<YMAX;i++){
		village[i].resize(XMAX);
		for(int j=0;j<XMAX;j++){
			village[i][j]=" ";	
		}
	}
	
	/* TODO: EXTRACT TO FUNCTION OR CLASS */
	ifstream village_file("Assets/village2.txt");
	if (!village_file) {
		cout << "Error loading Assets/village.txt" << endl;
	} else {
		string village_line;
		int village_x = 0;
		while (!village_file.eof()) {
			getline(village_file, village_line);
			if (village_line == "\n") continue; // Skip empty lines
			
			for (int i = 0; i < village_line.length(); i++) {
				village[village_x][i] = (village_line.at(i) == 'O') ? " " : village_line.at(i)
			}
			village_x++;
		}
	}
	village_file.close();
	/*
	ifstream infile;
	infile.open("Assets/village.txt");
	string tmpfl;
	int tmpl=0;
	while (!infile.eof()) {
		getline(infile,tmpfl);
		
		for(int i=0;i<tmpfl.length();i++){
			if(tmpfl.substr(i,1)!="\n"){
				village[tmpl][i]=tmpfl.substr(i,1);
				if(village[tmpl][i]=="O"){
					village[tmpl][i]=" ";
				}
			}
		}
		tmpl++;
	}
	infile.close();
*/
	
	
	
	
	player.set_up();
	player.x=XMAX/2; //40
	player.y=YMAX/2; //12
	
	Enemy romar;
	romar.set_up(30,10,0);
	
	if(argc>1){
		if(*argv[1]=='a'){
			stage=2;
			player.add("A");
			
		}
	}
	

	dudes.push_back(&player);
	
	
	
	initscr();
	noecho();
	cbreak();
	
	int yMax,xMax;
	getmaxyx(stdscr, yMax, xMax);
	int k_press;
	
	WINDOW* worldwin = newwin(yMax,xMax,0,0);
	
	refresh();
	wrefresh(worldwin);
	keypad(worldwin, true);
	
	curs_set(0);
	
	start_color();
	//init_color(10, 0, 0, 150);
	for(int i=0;i<10;i++){						//blue
		init_color(10+i, 0, 0, 150-(15*i));
	}
	for(int i=0;i<10;i++){
		init_color(20+i, 1000-((i+1)*100),1000-((i+1)*100),1000-((i+1)*100));	//white
		init_pair(i+1, 20+i, 10+i);
	}
	for(int i=0;i<10;i++){
		init_color(30+i, 1000-((i+1)*100), 800-((i+1)*80), 0);		//gold
		init_pair(i+11, 30+i, 10+i);
	}
	for(int i=0;i<10;i++){
		init_color(40+i, 500-((i+1)*50),500-((i+1)*50),500-((i+1)*50));	//grey
		init_pair(i+21, 40+i, 10+i);
	}
	
	//wattron(worldwin,COLOR_PAIR(1));
	
	/*
	*---*
	| d |
	*---*
		
	*/
	
	int xs,ys,ts;
	//int lst;
	
	
	
	
	
	
	while (true){
		tick(worldwin);
		
		
		
		k_press = wgetch(worldwin);			//keyboard input
		xs=0;
		ys=0;
		ts=10;
		if(k_press==KEY_UP || k_press==(int)'w'){
			ys=-1;
			ts=0;
		}
		else if(k_press==KEY_DOWN || k_press==(int)'s'){
			ys=1;
			ts=3;
		}
		else if(k_press==KEY_LEFT || k_press==(int)'a'){
			xs=-1;
			ts=1;
		}
		else if(k_press==KEY_RIGHT || k_press==(int)'d'){
			xs=1;
			ts=2;
		}
		else if(k_press==(int)'\t'){
			(++player.handid) %= player.hand.size();
		}
		else if(k_press==(int)' '){
		
			int hand_xs=0;
			int hand_ys=0;
			if(player.last_dir==0){
				hand_ys=-1;		//hand up
			}
			else if(player.last_dir==1){
				hand_xs=-1;		//hand left
			}
			else if(player.last_dir==2){
				hand_xs=1;		//hand right
			}
			else if(player.last_dir==3){
				hand_ys=1;		//hand down
			}
			if(player.hand[player.handid]=="#"){
				village[player.y+hand_ys][player.x+hand_xs]="#";
				player.remove("#");
			}
			else if(player.hand[player.handid]=="o"){
				village[player.y+hand_ys][player.x+hand_xs]=CAMPFIRE;
				player.fire[{player.y+hand_ys,player.x+hand_xs}]=16;
				if(stage<3){
					stage=3;
				}
				player.remove("o");
			}
		}
		else if(k_press==(int)'q'){
			break;
		}
		
		if(player.water){
			xs=1;
			ys=1;
			ts=4;
			
			refresh();
			wrefresh(worldwin);
			usleep(50000);
		}
		
		if(xs!=0 || ys!=0){
			if(player.y+ys>(yMax-1) || player.y+ys<0 || player.x+xs>(xMax-1) ||player.x+xs<0){
				continue;
			}
			if(village[player.y+ys][player.x+xs]=="_"){
				player.y=player.y+ys;
				player.x=player.x+xs;
				player.water=true;
				player.last_dir=ts;
			}
			
			
			
			if(player.hand[player.handid]!=" "){
				player.last_dir=ts;
				
				if(village[player.y+ys][player.x+xs]==" "){
					xs=xs*2;
					ys=ys*2;
				}
			}
			if(player.y+ys>(yMax-1) || player.y+ys<0 || player.x+xs>(xMax-1) || player.x+xs<0){
				continue;
			}
			
			
			if(village[player.y+ys][player.x+xs]==" "){					//move
				if(xs>1||xs<-1||ys>1||ys<-1){
					xs=xs/2;
					ys=ys/2;
				}
				player.y=player.y+ys;
				player.x=player.x+xs;
				player.water=false;
			}
			/*else if(village[player.y+ys][player.x+xs]=="o"){			//grab camp
				village[9][20]=" ";
				village[11][29]=CAMPFIRE;
				player.fire[{11,29}]=16;
			}*/
			else if(player.y+ys==9&&player.x+xs==20){
				if(player.add(village[player.y+ys][player.x+xs])){
					village[player.y+ys][player.x+xs]=" ";				//pickup
				}
			}
			else if(village[player.y+ys][player.x+xs]=="/"||village[player.y+ys][player.x+xs]=="."||village[player.y+ys][player.x+xs]==","||village[player.y+ys][player.x+xs]=="A"){
				if(player.add(village[player.y+ys][player.x+xs])){
					village[player.y+ys][player.x+xs]=" ";				//pickup
				}
			}
			else if(village[player.y+ys][player.x+xs]==">"){
				if(player.craft[0]==""&&player.hand[player.handid]!=" "){	//craft1
					player.craft[0]=player.hand[player.handid];
					player.remove(player.hand[player.handid]);
				}
				else{
					if(player.craft[0]!=""){
						player.add(player.craft[0]);
					}
					player.craft[0]="";
				}
			}
			else if(village[player.y+ys][player.x+xs]=="<"){				//craft2
				if(player.craft[1]==""&&player.hand[player.handid]!=" "){
					player.craft[1]=player.hand[player.handid];
					player.remove(player.hand[player.handid]);
				}
				else{
					if(player.craft[1]!=""){
						player.add(player.craft[1]);
					}
					player.craft[1]="";
				}
			}
			else if(village[player.y+ys][player.x+xs]==CAMPFIRE){			//fire
				if(player.hand[player.handid]=="/"){
					player.fire[{player.y+ys,player.x+xs}]++;
					player.remove("/");
				}
				else if(player.hand[player.handid]=="="){					
					player.fire[{player.y+ys,player.x+xs}]=player.fire[{player.y+ys,player.x+xs}]+3;
					player.remove("=");
				}
			}
			else if(village[player.y+ys][player.x+xs]=="^"&&player.hand[player.handid]=="A"){	//tree chop
				village[player.y+ys][player.x+xs]=" ";
				if(player.add("=")){
					if(player.add("/")){
						player.add("/");
					}
				}
			}
			else if(village[player.y+ys][player.x+xs]=="#"&&player.hand[player.handid]=="A"){	//wall chop
				village[player.y+ys][player.x+xs]=" ";
				player.add("#");
			}
		}
	
		
		

		
	}
	endwin();
	
	if (system(NULL)){ //checks if command processor is available
		if(system("reset")){}
	}
	

	cout<<yMax<<" "<<xMax<<endl;
	cout<<player.craft[0]<<endl;
	cout<<player.craft[1]<<endl;
	return 0;
}


inline float getDis(GameObject* src,GameObject* dest){
	return sqrt(pow((src->x-dest->x),2)+pow((src->y-dest->y),2));
}
inline float getDis(GameObject* src){
	return sqrt(pow((src->x-(player.x+400)),2)+pow((src->y-(player.y+400)),2));
}
inline float getDis(GameObject* src,int x2,int y2){
	return sqrt(pow((src->x-x2),2)+pow((src->y-y2),2));
}
inline float getDis(int x1,int y1,int x2,int y2){
	return sqrt(pow((x1-x2),2)+pow((y1-y2),2));
}
void clear_screen(WINDOW* w){
	for(int i=1;i<getmaxy(w)-1;i++){
		for(int j=1;j<getmaxx(w)-1;j++){
			mvwprintw(w, i, j, " ");
		}
	}
	wclear(w);
}
int light_distance(int y,int x){
	if(stage<3){
		return 0;
	}
	int dis=9;
	//vector<int> pick={};
	int ls=0;
	for(int yy=0;yy<YMAX;yy++){
		for(int xx=0;xx<XMAX;xx++){
			if(village[yy][xx]=="O"){
				int ls=(int)(sqrt(((y-yy)*(y-yy))+(((x-xx)/2)*((x-xx)/2))));
				ls=(ls*2)-player.fire[{yy,xx}];
				if(ls>8){
					ls=9;
				}
				else if(ls<1){
					ls=1;
				}
				
				if(ls<dis){
					dis=ls;
				}
				
			}
		}
	}
	/*
	
	int ls=(int)(sqrt(((y-11)*(y-11))+(((x-29)/2)*((x-29)/2))));	//fireplace is at 29 11
	ls=(ls*2)-player.fire;
	if(ls>8){
		ls=9;
	}
	else if(ls<1){
		ls=1;
	}
	*/
	return dis;
}

bool draw(WINDOW* w){
	

	
	int hand_xs,hand_ys,ls,colour_shift=0;
	
	wattroff(w,COLOR_PAIR(1));
	
	
	
	clear_screen(w);
	for(unsigned int i=0;i<village.size();i++){
		for(unsigned int j=0;j<village[i].size();j++){
			ls=light_distance(i,j);
			
			if((village[i][j]==">"||village[i][j]=="<")&&player.hand[player.handid]!=" "&&stage<3){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if(village[i][j]=="O"&&(player.hand[player.handid]=="/"||player.hand[player.handid]=="=")){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if(village[i][j]=="^"&&(player.hand[player.handid]=="A")&&player.inventory["="]<player.max_inv["="]){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else{
				colour_shift=0;
			}
			string tmp_str;
			
			for(map<string,int>::iterator it = player.inventory.begin(); it != player.inventory.end(); ++it) {
				tmp_str=it->first;
				if(village[i][j]==tmp_str){
					if(player.inventory[village[i][j]]<player.max_inv[village[i][j]]&&stage<2){
						colour_shift=10;
					}
				}
			}
			
			
			/*for(int k=0;k<player.inventory.keys().size();k++){
				tmp_str=player.inventory.keys()[0];
				if(village[i][j]==tmp_str){
					if(player.inventory[village[i][j]]<player.max_inv[village[i][j]]&&stage<2){
						colour_shift=10;
					}
				}
			}*/
						
			if((village[i][j]==">"&&player.craft[0]!="")||(village[i][j]=="<"&&player.craft[1]!="")){
				wattron(w,A_REVERSE);
			}
			
			wattron(w,COLOR_PAIR(colour_shift+ls+1));
			mvwprintw(w,i,j,village[i][j].c_str());	
			
			wattroff(w,A_BOLD);
			wattroff(w,COLOR_PAIR(colour_shift+ls+1));
			wattroff(w,A_REVERSE);
		}
	}
	
	wattron(w,COLOR_PAIR(1));
	for(unsigned int i=0;i<dudes.size();i++){
		mvwprintw(w,dudes[i]->y,dudes[i]->x,dudes[i]->img.c_str());	
	}
	hand_xs=0;
	hand_ys=0;
	if(player.hand[player.handid]!=" "){
		if(player.last_dir==0){
			hand_ys=-1;		//print hand up
		}
		else if(player.last_dir==1){
			hand_xs=-1;		//print hand left
		}
		else if(player.last_dir==2){
			hand_xs=1;		//print hand right
		}
		else if(player.last_dir==3){
			hand_ys=1;		//print hand down
		}
		
		wattroff(w,COLOR_PAIR(1));
		wattron(w,COLOR_PAIR(21+light_distance(player.y+hand_ys,player.x+hand_xs)));
		mvwprintw(w,player.y+hand_ys,player.x+hand_xs,player.hand[player.handid].c_str());
		wattroff(w,COLOR_PAIR(21+light_distance(player.y+hand_ys,player.x+hand_xs)));
		wattron(w,COLOR_PAIR(1));
		
		
		
	}
	return true;
}

bool craft(string s1,string s2,string r){
	if((player.craft[0]==s1&&player.craft[1]==s2)||(player.craft[1]==s1&&player.craft[0]==s2)){
		player.craft[0]="";
		player.craft[1]="";
		village[9][20]=r;
		return true;
	}
	return false;
}

void tick(WINDOW* w){
	fire_tick++;
	//tree_tick++;
	
	stage_check();
	
	if(player.craft[0]!=""&&player.craft[1]!=""){
		//make thing
		for(int i=0;i<recipes.size();i++){
			if(craft(recipes[i][0],recipes[i][1],recipes[i][2])){
				break;
			}
		}
	}
	
	draw(w);
	
	if(stage>=3){
		if(fire_tick>10){
			for(map<vector<int>,int>::iterator it = player.fire.begin(); it != player.fire.end(); ++it) {
				player.fire[it->first]--;
				if(player.fire[it->first]<0){
					player.fire[it->first]=0;
				}
			}
			fire_tick=0;
		}
	}
	
	vector<vector<int> > sur={};
	
	if(stage>=2){
		for(int i=0;i<village.size();i++){
			for(int j=0;j<village[i].size();j++){
				
				if(village[i][j]=="^"){
					if((int)(rand()%1000)==0){
						sur.clear();
						for(int y=0;y<3;y++){
							for(int x=0;x<3;x++){
								if(i+y<23&&i+y>0&&j+x<79&&j+x>0){
									if(village[i+y][j+x]==" "){
										sur.push_back({i+y,j+x});
									}
								}
							}
						}
						if(sur.size()>0){
							int tmp=(int)(rand()%sur.size());
							village[sur[tmp][0]][sur[tmp][1]]="^";
						}
					}
				}
			}
		}
	}
}

void stage_check(){
	if(stage==0){
		if(player.hand.size()>1){
			stage=1;
		}
	}
	else if(stage==1){
		if(player.inventory["A"]>0){
			stage=2;
		}
	}
	
	
	
}













