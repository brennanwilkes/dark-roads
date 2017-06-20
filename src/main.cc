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
#include <SFML/Graphics.hpp>

//User Includes
#include "player.hpp"
#include "gameObject.hpp"
#include "enemy.hpp"
#include "global.hpp"


using namespace std;
using namespace sf;


int scene;	//Just an example on how to do a global
Player player=Player(15.f);
vector<Enemy*> dudes;

inline float getDis(GameObject* src,GameObject* dest);

int main(int argc, char *argv[]) {
	
	RenderWindow window(VideoMode(800, 800), "Hello World!");
	
	player.set_up();
	
	Enemy romar(10.f);
	romar.set_up(250,125,10);
	dudes.push_back(&romar);
	
	while (window.isOpen()){
		window.clear();
		
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed){
				window.close();
			}
			player.check_keys(event);
		}
		
		
		player.tick();
		for(unsigned int i=0;i<dudes.size();i++){
			dudes[i]->tick();
			if(getDis(&player,dudes[i])<75){
				dudes[i]->change=true;
				dudes[i]->interact=true;
			}
			else if(dudes[i]->interact){
				dudes[i]->change=true;
				dudes[i]->interact=false;
			}
			window.draw(dudes[i]->sprite);
		}
		
		
		
		window.draw(player.sprite);
		window.display();
	}

	return 0;
}


inline float getDis(GameObject* src,GameObject* dest){
	return sqrt(pow((src->x-dest->x),2)+pow((src->y-dest->y),2));
}











