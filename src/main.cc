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
#include "terrain.hpp"
#include "global.hpp"


using namespace std;
using namespace sf;


int scene;	//Just an example on how to do a global
Player player=Player(15.f);
vector<Enemy*> dudes;

inline float getDis(GameObject* src,GameObject* dest);
inline float getDis(GameObject* src);
inline float getDis(GameObject* src,int x2,int y2);
inline float getDis(int x1,int y1,int x2,int y2);

int main(int argc, char *argv[]) {
	
	RenderWindow window(VideoMode(800, 800), "Hello World!");
	
	player.set_up();
	
	Enemy romar(10.f);
	romar.set_up(250,125,10);
	dudes.push_back(&romar);
	
	cout << "seed?" << endl;
	int seed;
	cin >> seed;
	const int terrain_width(250), terrain_height(250);
	Terrain terrain = Terrain(terrain_width,terrain_height,seed);
	
	
	
	while (window.isOpen()){
		
		window.clear();
		

		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed){
				window.close();
			}
			player.check_keys(event);
			if(event.type==Event::KeyPressed){
				if(event.key.code==Keyboard::Return){
					for(unsigned int j=0;j<dudes.size();j++){//Do interact stuff
						if(dudes[j]->hostile && dudes[j]->interact){
							dudes[j]->health=dudes[j]->health-(25.0/getDis(dudes[j]));
							dudes[j]->combat=true;
						}
					}		
				}
				if(event.key.code==Keyboard::R){
					seed++;
					terrain = Terrain(terrain_width,terrain_height,seed);
					//terrain = Terrain(250,250,seed);
					cout<<seed<<endl;
				}
			}
			if (Mouse::isButtonPressed(Mouse::Left)){
				Vector2i m_pos = sf::Mouse::getPosition();
				//cout<<m_pos.x<<" "<<m_pos.y<<endl;		
			}
		}
		
		
		terrain.sprite->setPosition(-player.x,-player.y);
		window.draw(*terrain.sprite);
		
		player.tick();
		for(unsigned int i=0;i<dudes.size();i++){
			dudes[i]->tick();
			if(getDis(dudes[i])<75){
				dudes[i]->change=true;
				dudes[i]->interact=true;

				
				
			}
			else if(dudes[i]->interact){
				dudes[i]->change=true;
				dudes[i]->interact=false;
			}
			if(!dudes[i]->dead){
				window.draw(dudes[i]->sprite);
			}
		}
		
		
		
		window.draw(player.sprite);

		window.display();
	}

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






