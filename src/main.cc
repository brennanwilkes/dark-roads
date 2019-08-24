/*

DARK ROADS - BRENNAN WILKES - 2017/2018	


Special thanks to
Michael Liu - Ryan Carrusca - soundbible.com
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


//sound includes
#include <SFML/Audio.hpp>

//noise includes
#include "noise/noise.h"




//User Includes
#include "player.hpp"
#include "gameObject.hpp"
#include "enemy.hpp"
#include "terrain.hpp"
#include "global.hpp"
#include "world.hpp"


using namespace std;


#define YMAX 24
#define XMAX 80


int stage;
int scene;
Player player=Player();
vector<GameObject*> dudes;
int text_delay;
int xMax;
int yMax;

int sound_mult=1;

Enemy path_finder;

Terrain* outer_world;

sf::Music rain_sound,fire_sound;
sf::Sound enem_spawn_sound,enem_death_sound,craft_sound,tree_sound,meteor_sound,leave_sound;
sf::SoundBuffer enem_spawn_buffer,enem_death_buffer,craft_buffer,tree_buffer,meteor_buffer,leave_buffer;


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
bool light_cheats;

unsigned int fire_tick=0;
unsigned int tree_tick=0;
unsigned int enem_tick=0;
unsigned int lore_tick=0;

vector<vector<string> > village(YMAX);
vector<vector<string> >* e_village;
vector<vector<string> > lore = {{},{},{},{},{},{},{},{},{},{},{}};
map<vector<int>,string> exmap;

vector<vector<int> > tree_fire(YMAX);


vector<vector<string> > recipes={
	//{".",".",","},
	{"/",".","A"},
	{".","=","o"},
	{"=","=","#"},
	{"o","S","O"},
	{"S","#","$"},
	{"S","=","^"},
	{"?","S","C"}
};

vector<int> hint_staging = {0,0,2,2,5,6,100,100,100};

//		 0
//		1 2
//		 34



int main(int argc, char *argv[]) {
	
	
	stage=0;
	scene = 0; //village
	
	srand (time(NULL));
	
	

	light_cheats = false;
	
	
	
	Terrain* outer_world = new Terrain();
	
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0&&j==0){
				continue;
			}
			outer_world->pro_chunk(i,j);
		}
	}
	
	
	
	for(int i=0;i<YMAX;i++){
		tree_fire[i].resize(XMAX);
		for(int j=0;j<XMAX;j++){
			tree_fire[i][j]=-1;	
		}
	}
	
	
	for(int i=0;i<YMAX;i++){
		village[i].resize(XMAX);
		for(int j=0;j<XMAX;j++){
			village[i][j]=" ";	
		}
	}
	
	
	/*for(unsigned int i=0;i<tree_fire.size();i++){
		for(unsigned int j=0;j<tree_fire[i].size();j++){
			cout<<tree_fire[i][j];
		}
		cout<<endl;
	}
	cout<<1/0;*/
	
	/* TODO: EXTRACT TO FUNCTION OR CLASS */
	ifstream village_file("Assets/village.txt");
	if (!village_file) {
		cout << "Error loading Assets/village.txt" << endl;
	} else {
		string village_line;
		int village_x = 0;
		while (!village_file.eof()) {
			getline(village_file, village_line);
			if (village_line == "\n") continue; // Skip empty lines
			
			for (int i = 0; i < village_line.length(); i++) {
				village[village_x][i] = (village_line.at(i) == 'S') ? " " : village_line.substr(i, 1);
			}
			village_x++;
		}
	}
	village_file.close();
	
	
	outer_world->chunks[{0,0}] = village;
	e_village=&outer_world->chunks[{0,0}];
	
	
	ifstream lore_file("Assets/lore.txt");
	if (!lore_file) {
		cout << "Error loading Assets/lore.txt" << endl;
	} else {
		string lore_line;
		while (!lore_file.eof()) {
			getline(lore_file, lore_line);
			if (lore_line == "\n"||lore_line.length()<2) continue; // Skip empty lines
			lore[stoi(lore_line.substr(0,1))].push_back(lore_line.substr(1,lore_line.length()-1));
		}
	}
	lore_file.close();
	
	
	
	
	player.set_up();
	player.x=XMAX/2; //40
	player.y=YMAX/2; //12
	
	Enemy romar;

	string tmp_in;
	
	//command line arguments
	for(int i=0;i<argc;i++){
		tmp_in = argv[i];
		if(tmp_in=="-a"){
			stage=2;
			player.add("A");
		}
		else if(tmp_in=="-e"){
			romar.set_up(30,10,"&");
			dudes.push_back(&romar);
		}
		else if(tmp_in=="-o"){
			player.add("o");
		}
		else if(tmp_in=="-O"){
			player.add("O");
		}
		else if(tmp_in=="-w"){
			player.add("=");
			player.inventory["="]=25;
		}
		else if(tmp_in=="-$"){
			player.add("$");
		}
		else if(tmp_in=="-s"){
			sound_mult=0;
		}
		else if(tmp_in=="-k"){
			player.kills=10;
		}
		else if(tmp_in=="-c"){
			player.add("C");
		}
		else if (tmp_in=="-l"){
			light_cheats = true;
		}
		
	}

	dudes.push_back(&player);
	
	
	
	initscr();
	noecho();
	cbreak();
	
	//int yMax,xMax;
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
	
	for(int i=0;i<10;i++){
		init_color(50+i, 1000-((i+1)*85),0,0);	//red
		init_pair(i+31, 50+i, 10+i);
	}
	init_pair(41, 0, 31);	//GOLD BACKGROUND
	
	//wattron(worldwin,COLOR_PAIR(1));
	
	/*
	*---*
	| d |
	*---*
		
	*/
	
	int xs,ys,ts;
	//int lst;
	
	

	rain_sound.openFromFile("Assets/rain.ogg");
	rain_sound.setVolume(25*sound_mult);
	rain_sound.setLoop(true);
	rain_sound.play();
	
	fire_sound.openFromFile("Assets/fire.ogg");
	fire_sound.setLoop(true);
	
	
	enem_spawn_buffer.loadFromFile("Assets/monster.ogg");
	enem_spawn_sound.setBuffer(enem_spawn_buffer);
	enem_spawn_sound.setVolume(40*sound_mult);
	
	enem_death_buffer.loadFromFile("Assets/burn.ogg");
	enem_death_sound.setBuffer(enem_death_buffer);
	enem_death_sound.setVolume(10*sound_mult);
	
	tree_buffer.loadFromFile("Assets/tree.ogg");
	tree_sound.setBuffer(tree_buffer);
	tree_sound.setVolume(50*sound_mult);
	
	meteor_buffer.loadFromFile("Assets/meteor_explosion.ogg");
	meteor_sound.setBuffer(meteor_buffer);
	meteor_sound.setVolume(50*sound_mult);
	
	leave_buffer.loadFromFile("Assets/leave.ogg");
	leave_sound.setBuffer(leave_buffer);
	leave_sound.setVolume(50*sound_mult);
	
	craft_buffer.loadFromFile("Assets/craft.ogg");
	craft_sound.setBuffer(craft_buffer);
	craft_sound.setVolume(50*sound_mult);
	
	
	if(argc==1){
		wattron(worldwin,COLOR_PAIR(1));
		clear_screen(worldwin);
		mvwprintw(worldwin,(YMAX/2)-1,(XMAX/2)-10,"WELCOME TO DARK ROADS");
		mvwprintw(worldwin,(YMAX/2)+1,(XMAX/2)-18,"USE [WASD] [SPACE] and [TAB] to play");
		wattroff(worldwin,COLOR_PAIR(1));
		refresh();
		wrefresh(worldwin);
		wgetch(worldwin);
	}
	
	
	
	while (true){
	
		tick(worldwin);
		
		if(player.dead){
			if(player.dead_shift>=30){
				wattron(worldwin,COLOR_PAIR(1));
				mvwprintw(worldwin,20,55,"YOU DIED");
				mvwprintw(worldwin,21,50,"Press space to quit");
				wattroff(worldwin,COLOR_PAIR(1));
				refresh();
				wrefresh(worldwin);
				int t = wgetch(worldwin);
				if(t==(int)' '){
					break;
				}
			}
			else if(player.dead_shift>=20){
				wattron(worldwin,COLOR_PAIR(1));
				mvwprintw(worldwin,20,55,"YOU DIED");
				wattroff(worldwin,COLOR_PAIR(1));
				player.dead_shift++;
				refresh();
				wrefresh(worldwin);
				usleep(100000);
			}
			else{
				player.dead_shift++;
				refresh();
				wrefresh(worldwin);
				usleep(100000);
			}
			continue;
		}
		
		
		
		if(player.water){
			xs=1;
			ys=1;
			ts=4;
			
			refresh();
			wrefresh(worldwin);
			usleep(50000);
		}
		else{
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
			else if(k_press==(int)'\t'&&stage!=6){
				(++player.handid) %= player.hand.size();
			}
			else if(k_press==(int)' '&&stage!=6){
				if(player.place()){
					fire_sound.play();
					fire_sound.setVolume(0);
				}
				else if(player.hand[player.handid]==" "){
					player.hint = true;//needs hint
				}
			}
			else if(k_press==(int)'q'){
				break;
			}
		}
		
		
		if(xs!=0 || ys!=0){
			if(stage!=6){
				int mv = player.move(xs,ys,xMax,yMax,ts);
				if(mv==-1){
					continue;
				}
				else if(mv==1){
					tree_sound.play();
				}
				else if(mv==2){	//leave to region
					leave_sound.play();
					if(stage<3&&light_cheats==false){
						stage=3;
					}
					//stage = 6;
					player.chx=player.chx+xs;
					player.chy=player.chy+ys;
					
					player.switch_stage = true;
					
					int shft=1;
					if(player.hand[player.handid]!=" "){
						shft=2;
					}
					
					if(xs!=0){
						player.x=(xMax+(xs*shft))%xMax;
					}
					if (ys!=0){
						player.y=(yMax+(ys*shft))%yMax;
					}
					outer_world->pro_chunk(player.chy,player.chx);
					e_village=&(outer_world->chunks[{player.chy,player.chx}]);
				}
			}
		}
	
		
		

		
	}
	endwin();
	
	if (system(NULL)){ //checks if command processor is available
		if(system("reset")){}
	}
	

	//cout<<yMax<<" "<<xMax<<endl;
	//cout<<player.craft[0]<<endl;
	//cout<<player.craft[1]<<endl;
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
	string chr = "";
	for(int yy=0;yy<YMAX;yy++){
		for(int xx=0;xx<XMAX;xx++){
			if(((*e_village)[yy][xx]=="o")||((*e_village)[yy][xx]=="O")){
				int ls=(int)(sqrt(((y-yy)*(y-yy))+(((x-xx)/2)*((x-xx)/2))));
				ls=(ls*1)-(player.fire[{yy,xx}]/3);
				if(ls<dis){
					dis=ls;
					chr=(*e_village)[yy][xx];
				}
				
			}
		}
	}
	ls++;	//just to remove a warning
	
	
	
	if(player.dead){
		dis=dis+player.dead_shift;
	}
	
	
	if(dis>8){
		dis=9;
	}
	else if(dis<1){
		dis=1;
	}
	
	
	
	if(chr=="O"){
		dis=dis*-1;
	}
	
	
	return dis;
}

bool draw(WINDOW* w){
	
	int hand_xs,hand_ys,ls,colour_shift=0;
	wattroff(w,COLOR_PAIR(1));
	clear_screen(w);
	
	for(unsigned int i=0;i<e_village->size();i++){
		for(unsigned int j=0;j<(*e_village)[i].size();j++){
			ls=abs(light_distance(i,j));
			
			if(((*e_village)[i][j]=="^")&&(ls<2)&&(stage>=3)){
				if(tree_fire[i][j] == -1){				//light trees on fire
					tree_fire[i][j] = 1;
				}
			}
			
			if(tree_fire[i][j]>0){
				colour_shift=30;
			}
			else if(((*e_village)[i][j]==">"||(*e_village)[i][j]=="<")&&player.hand[player.handid]!=" "&&stage<3){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if((*e_village)[i][j]=="o"&&(player.hand[player.handid]=="/"||player.hand[player.handid]=="="||player.hand[player.handid]=="S")){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if((*e_village)[i][j]=="O"&&(player.hand[player.handid]=="S")){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if((*e_village)[i][j]=="$"&&(player.hand[player.handid]=="S")){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if((*e_village)[i][j]=="^"&&(player.hand[player.handid]=="A")&&player.inventory["="]<player.max_inv["="]){
				colour_shift=10;
				//wattron(w,A_BOLD);
			}
			else if((*e_village)[i][j]==" "&&player.hand[player.handid]=="C"&&(i==0||i==yMax-1||j==0||j==xMax-1)){
				colour_shift=40;
				ls=0;
			}
			else{
				colour_shift=0;
			}
			string tmp_str;
			
			for(map<string,int>::iterator it = player.inventory.begin(); it != player.inventory.end(); ++it) {
				tmp_str=it->first;
				if((*e_village)[i][j]==tmp_str){
					if(player.inventory[(*e_village)[i][j]]<player.max_inv[(*e_village)[i][j]]){
						if((stage<2&&tmp_str!="^")||((*e_village)[i][j]=="?"&&stage==5&&colour_shift!=30)){
							colour_shift=10;
						}
					}
				}
			}
			
			
						
			if(((*e_village)[i][j]==">"&&player.craft[0]!="")||((*e_village)[i][j]=="<"&&player.craft[1]!="")){
				wattron(w,A_REVERSE);
			}
			
			wattron(w,COLOR_PAIR(colour_shift+ls+1));
			mvwprintw(w,i,j,(*e_village)[i][j].c_str());	
			
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
		wattron(w,COLOR_PAIR(21+abs(light_distance(player.y+hand_ys,player.x+hand_xs))));
		mvwprintw(w,player.y+hand_ys,player.x+hand_xs,player.hand[player.handid].c_str());
		wattroff(w,COLOR_PAIR(21+abs(light_distance(player.y+hand_ys,player.x+hand_xs))));
		wattron(w,COLOR_PAIR(1));
		
		
		
	}
	if(lore[stage].size()>0){
		if(lore_tick==15){
			player.lore=lore[stage][rand() % lore[stage].size()];
		}
		if(lore_tick>15){
			mvwprintw(w,22,40,player.lore.c_str());
		}
		if(lore_tick>18){
			lore_tick=0;
		}
	}
	
	
	if(player.hint){
		player.hint=false;
		mvwprintw(w,0,xMax-13,"_____________");
		mvwprintw(w,1,xMax-13,"|           |");
		int t=0;
		for(int i=0;i<recipes.size();i++){
			if(i>hint_staging[stage]){
				break;
			}
			t++;
			mvwprintw(w,i+2,xMax-13,("| "+recipes[i][0]+" + "+recipes[i][1]+" > "+recipes[i][2]+" |").c_str());
		}
		mvwprintw(w,t+2,xMax-13,"|___________|");
	}
	
	
	return true;
}


bool craft(string s1,string s2,string r){
	if((player.craft[0]==s1&&player.craft[1]==s2)||(player.craft[1]==s1&&player.craft[0]==s2)){
		player.craft[0]="";
		player.craft[1]="";
		(*e_village)[9][20]=r;
		craft_sound.play();
		return true;
	}
	return false;
}

void tick(WINDOW* w){
	fire_tick++;
	//tree_tick++;
	enem_tick++;
	
	lore_tick++;
	
	
	
	
	
	
	
	stage_check();
	
	int tmp_fire=((10-abs(light_distance(player.y,player.x)))*2)-3;
	if(tmp_fire<0){
		tmp_fire=0;
	}
	
	fire_sound.setVolume(tmp_fire*sound_mult);
			
			
	
	if(player.craft[0]!=""&&player.craft[1]!=""){
		//make thing
		for(int i=0;i<recipes.size();i++){
			if(craft(recipes[i][0],recipes[i][1],recipes[i][2])){
				break;
			}
		}
	}
	
	draw(w);
	
	
	
	if((stage==4&&player.kills>=3&&player.chy==0&&player.chx==0)||((player.chy!=0||player.chx!=0)&&(rand()%70==10))){
		vector<vector<string> > ast = {
		{"?","?",".",".","?"}, //	??..?
		{"?","?","O","?","?"}, //	?O??.
		{".","?",".",".","?"}, //	.?..?	
		};
		stage=5;
		bool space = true;
		for(int y=5;y<e_village->size()-7;y++){
			for(int x=0;x<(*e_village)[y].size()-20;x++){
				space = true;
				for(int i=0;i<7;i++){
					for(int j=0;j<9;j++){
						if((*e_village)[y+i][x+j]!=" "){
							space = false;
							break;
						}
					}
					if(space == false){
						break;
					}
					else{
						for(int ii=0;ii<ast.size();ii++){
							for(int jj=0;jj<ast[ii].size();jj++){
								(*e_village)[y+ii+3][x+jj+3]=ast[ii][jj];
								tree_fire[y+ii+3][x+jj+3]=3;
							}
						}
						meteor_sound.play();
						break;
					}
				}
				if(space==true){
					break;
				}
			}
			if(space==true){
				break;
			}
		}
	}
	
	
	
	if(stage>=3){
		if(fire_tick>3){
			
			for(map<vector<int>,int>::iterator it = player.fire.begin(); it != player.fire.end(); ++it) {
				if((*e_village)[it->first[0]][it->first[1]]=="o"){
					player.fire[it->first]--;
					if(player.fire[it->first]<0){
						player.fire[it->first]=0;
					}
				}
			}
			
			for(int i=0;i<tree_fire.size();i++){
				for(int j=0;j<tree_fire[i].size();j++){
					if(tree_fire[i][j]>5){
						tree_fire[i][j]=-1;
						if((*e_village)[i][j]=="^"){
							(*e_village)[i][j]=" ";
						}
					}
					else if(tree_fire[i][j]>-1){
						tree_fire[i][j]++;
					}
				}
			}
			
			fire_tick=0;
		}
	}
	
	vector<vector<int> > sur={};
	
	if(stage>=2){
		for(int i=0;i<e_village->size();i++){
			for(int j=0;j<(*e_village)[i].size();j++){
				
				if((*e_village)[i][j]=="^"){
					if((int)(rand()%1000)==0){
						sur.clear();
						for(int y=0;y<3;y++){
							for(int x=0;x<3;x++){
								if(i+y<23&&i+y>0&&j+x<79&&j+x>0){
									if((*e_village)[i+y][j+x]==" "){
										sur.push_back({i+y,j+x});
									}
								}
							}
						}
						if(sur.size()>0){
							int tmp=(int)(rand()%sur.size());
							(*e_village)[sur[tmp][0]][sur[tmp][1]]="^";
						}
					}
				}
			}
		}
	}
	
	for(int i=0;i<dudes.size();i++){
		dudes[i]->tick();
		if(dudes[i]->img=="&"){
			
			if(player.switch_stage==true){
				GameObject* tmp = dudes[i];
				dudes.erase(dudes.begin()+i);
				delete tmp;
				continue;
			}
			for(map<vector<int>,int>::iterator it = player.trap.begin(); it != player.trap.end(); ++it) {
				vector<int> tc=it->first;
				int tv=it->second;
				if((abs(tc[0]-dudes[i]->y)<=tv&&abs(tc[1]-dudes[i]->x)<=tv)){

					if((abs(player.y-dudes[i]->y)<=3&&abs(player.x-dudes[i]->x)<=3)&&player.dead==false){
						(*e_village)[dudes[i]->y][dudes[i]->x]="S";
						player.kills++;
					}
					GameObject* tmp = dudes[i];
					dudes.erase(dudes.begin()+i);
					delete tmp;
					enem_death_sound.play();
				}
				
			}
			
			
			
			if(light_distance(dudes[i]->y,dudes[i]->x)==1){
				if((abs(player.y-dudes[i]->y)<=4&&abs(player.x-dudes[i]->x)<=4)&&player.dead==false){
					(*e_village)[dudes[i]->y][dudes[i]->x]="S";
					player.kills++;
				}
				GameObject* tmp = dudes[i];
				dudes.erase(dudes.begin()+i);
				delete tmp;
				enem_death_sound.play();
				
			}
			if((abs(player.y-dudes[i]->y)<=1&&abs(player.x-dudes[i]->x)<=1)&&player.dead==false){
				player.dead=true;
				player.dead_shift=0;
			}
		}
	}

	player.switch_stage=false;
	
	if(enem_tick>20){
		enem_tick=0;
		if(stage>=3){
			vector<vector<int> > spawns={};
			for(int i=0;i<65;i++){
				if(i<18&&(*e_village)[i][0]==" "&&(*e_village)[i][1]==" "){
					spawns.push_back({0,i});
				}
				if(i<45&&(*e_village)[0][i]==" "&&(*e_village)[1][i]==" "){
					spawns.push_back({i,0});
				}
				if(i>15&&(*e_village)[23][i]==" "&&(*e_village)[22][i]==" "){
					spawns.push_back({i,23});
				}
			}
			if(spawns.size()>0&&dudes.size()<=(int)(spawns.size()/10)+1){
				vector<int> spawn = spawns[rand()%spawns.size()];
				Enemy* new_en = new Enemy();
				new_en->set_up(spawn[0],spawn[1],"&");
				dudes.push_back(new_en);
				enem_spawn_sound.play();	
				if(stage<4){
					stage=4;
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













