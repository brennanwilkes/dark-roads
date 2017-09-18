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
vector<pair<int,int> > gc;

//std::vector<std::vector<Terrain*> > fullmap;
std::map<std::pair<int,int>,Terrain*> fullmap;

int main(int argc, char *argv[]) {
	
	RenderWindow window(VideoMode(800, 800), "Hello World!");
	
	player.set_up();
	
	Enemy romar(10.f);
	romar.set_up(250,125,10);
	dudes.push_back(&romar);
	
	//cout << "seed?" << endl;
	int seed;
	//cin >> seed;
	seed=2;
	const int terrain_width(128), terrain_height(128);
	//Terrain terrain = Terrain(terrain_width,terrain_height,seed);
	
	
	fullmap[make_pair(0,0)] = new Terrain(terrain_width,terrain_height,seed,0,0);
	gc.push_back(make_pair(0,0));
	
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
				
			}
			if (Mouse::isButtonPressed(Mouse::Left)){
				Vector2i m_pos = sf::Mouse::getPosition();
				//cout<<m_pos.x<<" "<<m_pos.y<<endl;		
			}
		}
		
		
		//fullmap[std::make_pair(player.cx,player.cy)]->sprite->setPosition(-player.x-std::abs(800*(player.cx)),-player.y);
		//window.draw(*(fullmap[std::make_pair(player.cx,player.cy)]->sprite));
		
		
		for(int ix=-1;ix<2;ix++){
			for(int iy=-1;iy<2;iy++){
				if(!fullmap.count(std::make_pair(player.cx+ix,player.cy+iy))){
					fullmap[std::make_pair(player.cx+ix,player.cy+iy)] = new Terrain(terrain_width,terrain_height,seed,player.cx+ix,player.cy+iy);
					gc.push_back(make_pair(player.cx+ix,player.cy+iy));
				}
			}
		}
		
		/*
		if(!fullmap.count(std::make_pair(player.cx-1,player.cy))){
			fullmap[std::make_pair(player.cx-1,player.cy)] = new Terrain(terrain_width,terrain_height,seed,player.cx-1,player.cy);
			gc.push_back(make_pair(player.cx-1,player.cy));
		}
		if(!fullmap.count(std::make_pair(player.cx+1,player.cy))){
			fullmap[std::make_pair(player.cx+1,player.cy)] = new Terrain(terrain_width,terrain_height,seed,player.cx+1,player.cy);
			gc.push_back(make_pair(player.cx+1,player.cy));
		}
		*/
		
		
	
	
		//std::cout<<"cx "<<player.cx<<" - xpos "<<std::abs(800*(player.cx+1))<<std::endl;
		
		/*
		fullmap[std::make_pair(player.cx+1,player.cy)]->sprite->setPosition(-player.x+std::abs(800*(player.cx+1)),-player.y);
		window.draw(*(fullmap[std::make_pair(player.cx+1,player.cy)]->sprite));
		
		fullmap[std::make_pair(player.cx-1,player.cy)]->sprite->setPosition(-player.x-std::abs(800*(player.cx-1)),-player.y);
		window.draw(*(fullmap[std::make_pair(player.cx-1,player.cy)]->sprite));
		*/
		
		for(unsigned int k=0;k<gc.size();k++){
			if(abs(player.cx-gc[k].first)<2 && abs(player.cy-gc[k].second)<2){
				//fullmap[gc[k]]->sprite->setPosition(-player.x-abs(800*(gc[k].first)),-player.y);
				fullmap[gc[k]]->sprite->setPosition(800*(gc[k].first)-player.x,800*(gc[k].second)-player.y);
				window.draw(*(fullmap[gc[k]]->sprite));
			}
		}
		
		/*terrain.sprite->setPosition(-player.x+800,-player.y);
		window.draw(*terrain.sprite);
		terrain.sprite->setPosition(-player.x-800,-player.y);
		window.draw(*terrain.sprite);
		terrain.sprite->setPosition(-player.x,-player.y+800);
		window.draw(*terrain.sprite);
		terrain.sprite->setPosition(-player.x,-player.y-800);
		window.draw(*terrain.sprite);
		*/
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






