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

//SFML Includes


//User Includes
#include "player.hpp"
#include "gameObject.hpp"
#include "enemy.hpp"
#include "terrain.hpp"
#include "global.hpp"


using namespace std;



int scene;	//Just an example on how to do a global
Player player=Player(15.f);
vector<Enemy*> dudes;

inline float getDis(GameObject* src,GameObject* dest);
inline float getDis(GameObject* src);
inline float getDis(GameObject* src,int x2,int y2);
inline float getDis(int x1,int y1,int x2,int y2);
vector<pair<int,int> > gc;

//std::vector<std::vector<Terrain*> > fullmap;
std::map<std::pair<int,int>,Terrain*> fullmap;

int main(int argc, char *argv[]) {
	
	
	player.set_up();
	
	Enemy romar(10.f);
	romar.set_up(250,125,10);
	dudes.push_back(&romar);
	
	
	
	
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






