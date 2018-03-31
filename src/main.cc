/*

Summer project for IDS Best Team but probally just Brennan unless other people are interested

SFML 2.4.2

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



int scene;	//Just an example on how to do a global
Player player=Player();
vector<GameObject*> dudes;

inline float getDis(GameObject* src,GameObject* dest);
inline float getDis(GameObject* src);
inline float getDis(GameObject* src,int x2,int y2);
inline float getDis(int x1,int y1,int x2,int y2);
void clear_screen(WINDOW*);

vector<vector<string> > village(24);

vector<string> sur(5);

//		 0
//		1 2
//		 34

int main(int argc, char *argv[]) {
	scene=0;
	
	for(int i=0;i<24;i++){
		village[i].resize(80);
		for(int j=0;j<80;j++){
			village[i][j]=" ";	
		}
	}
	
	
	ifstream infile;
	infile.open("Assets/village.txt");
	string tmpfl;
	int tmpl=0;
	while (!infile.eof()) {
		getline(infile,tmpfl);
		for(int i=0;i<tmpfl.length();i++){
			if(tmpfl.substr(i,1)!="\n"){
				village[tmpl][i]=tmpfl.substr(i,1);
				/*if(village[tmpl][i]==">"||village[tmpl][i]=="#"||village[tmpl][i]=="<"){
					village[tmpl][i]=" ";
				}*/
			}
		}
		tmpl++;
	}
	infile.close();

	
	
	
	player.set_up();
	player.x=40;
	player.y=12;

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
	
	/*
	*---*
	| d |
	*---*
		
	*/
	
	int xs,ys,ts;
	
	while (true){
		clear_screen(worldwin);
		for(unsigned int i=0;i<village.size();i++){
			for(unsigned int j=0;j<village[i].size();j++){
				if((village[i][j]==">"&&player.craft[0]!="")||(village[i][j]=="<"&&player.craft[1]!="")){
					wattron(worldwin,A_BOLD);
				}
				mvwprintw(worldwin,i,j,village[i][j].c_str());	
				wattroff(worldwin,A_BOLD);
			}
		}
		
		for(unsigned int i=0;i<dudes.size();i++){
			mvwprintw(worldwin,dudes[i]->y,dudes[i]->x,dudes[i]->img.c_str());	
		}
		
		
		mvwprintw(worldwin,1,74,"*---*");
		mvwprintw(worldwin,2,74,"|   |");
		mvwprintw(worldwin,2,76,player.hand[player.handid].c_str());
		mvwprintw(worldwin,3,74,"*---*");
		
		
		if(player.y>0){
			sur[0]=village[player.y-1][player.x];
		}
		else{
			sur[0]="N";
		}
		if(player.y<23){
			sur[3]=village[player.y+1][player.x];
		}
		else{
			sur[3]="N";
		}
		if(player.x>0){
			sur[1]=village[player.y][player.x-1];
		}
		else{
			sur[1]="N";
		}
		if(player.x<79){
			sur[2]=village[player.y][player.x+1];
		}
		else{
			sur[2]="N";
		}
		if(sur[2]=="N"||sur[3]=="N"){
			sur[4]="N";
		}
		else{
			sur[4]=village[player.y+1][player.x+1];
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
			if(k_press==KEY_UP){
				ys=-1;
				ts=0;
			}
			else if(k_press==KEY_DOWN){
				ys=1;
				ts=3;
			}
			else if(k_press==KEY_LEFT){
				xs=-1;
				ts=1;
			}
			else if(k_press==KEY_RIGHT){
				xs=1;
				ts=2;
			}
			else if(k_press==9){
				if(player.handid+1==player.hand.size()){
					player.handid=0;
				}
				else{
					player.handid++;
				}
			}
			else if(k_press==32){
				if(player.hand[player.handid]==" "){
					//Crafting?
					
				}
				
				
			}
		}
		if(xs!=0 || ys!=0){
			if(sur[ts]==" "){
				player.y=player.y+ys;
				player.x=player.x+xs;
				player.water=false;
			}
			else if(sur[ts]=="_"){
				player.y=player.y+ys;
				player.x=player.x+xs;
				player.water=true;
			}
			else if(sur[ts]=="/"&&player.sticks<player.max_sticks){
				player.add("/");
				village[player.y+ys][player.x+xs]=" ";
			}
			else if(sur[ts]=="."&&player.stones<player.max_stones){
				player.add(".");
				village[player.y+ys][player.x+xs]=" ";
			}
			else if(sur[ts]==">"){
				if(player.craft[0]==""&&player.hand[player.handid]!=" "){
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
			else if(sur[ts]=="<"){
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
			
		
		}
	
		
		
		if(k_press==113){
			break;
		}
		
	}
	endwin();
	
	cout<<yMax<<" "<<xMax<<endl;
	cout<<player.craft[0]<<endl;
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





