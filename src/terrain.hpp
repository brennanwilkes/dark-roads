#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Terrain{
public:
	int width;			//width of generated terrain
	int height;			//y-height of generated terrain
	int seed;			//seed used to generate terrain
	int water_level;
	
	int x;
	int y;
	
	std::vector<std::vector<float> > raw_map;	//raw heightmap of terrain
	
	Terrain(int,int,int,int,int);
	
	sf::Sprite* sprite;
	
	std::vector<float> rand_array;		//array for generating heightmap of terrain
	

private:
	int depth;							//number of octaves used to generate. 

	void gen_map(int = -1);				//generate heightmap
	
	std::vector<std::vector<float> > gen_octave(float, int);	//generate one octave of terrain and interpolate it
	float interpolate(float, float, float);						//interpolation function
	
	sf::Texture* heightmap_tex;
	sf::Texture* map_tex;
	sf::Uint8* pixels;
	sf::Uint8* cpixels;
	float highest;
	
	void create_height_tex();
	void colourize();
	void draw_sprite(sf::Texture*);
	
	bool spam;
};

#endif
