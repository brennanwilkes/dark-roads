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


vector<pair<int,int> > gc;

//std::vector<std::vector<Terrain*> > fullmap;
std::map<std::pair<int,int>,Terrain*> fullmap;

int main(int argc, char *argv[]) {
	scene=0;
	
	player.set_up();
	
	Enemy romar;
	romar.set_up(250,125,10);
	dudes.push_back(&romar);
	
	
	
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
	
	while (true){
		clear_screen(worldwin);
		k_press = wgetch(worldwin);			//keyboard input
		
		if(k_press==KEY_UP){
			
		}
		else if(k_press==KEY_DOWN){
			
		}
		else if(k_press==KEY_LEFT){
			
		}
		else if(k_press==KEY_RIGHT){
			
		}
		else if(k_press==113){
			break;
		}
		
	}
	endwin();
	
	cout<<yMax<<" "<<xMax<<endl;
	
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





