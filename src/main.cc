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
#include "global.hpp"


using namespace std;
using namespace sf;


int scene;	//Just an example on how to do a global
Player player;

int main(int argc, char *argv[]) {
	
	RenderWindow window(VideoMode(800, 800), "Hello World!");
	CircleShape shape(200.f);
	shape.setFillColor(Color::Green);
	
	player.set_up();
	

	while (window.isOpen()){
		Event event;
		while (window.pollEvent(event))
		{
			if (event.type == Event::Closed){
				window.close();
			}
			player.check_keys(event);
		}
		if(player.keyPress["A"]){
			player.x=player.x-1;
		}
		if(player.keyPress["D"]){
			player.x=player.x+1;
		}
		if(player.keyPress["W"]){
			player.y=player.y-1;
		}
		if(player.keyPress["S"]){
			player.y=player.y+1;
		}
		
		
		cout<<player.x<<" "<<player.y<<endl;
		window.clear();
		window.draw(shape);
		window.display();
	}

	return 0;
}
