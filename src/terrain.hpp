#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Terrain{
public:
	int width;	//width of generated terrain
	int height;	//y-height of generated terrain
	int seed;	//seed used to generate terrain
	
	std::vector<std::vector<float> > raw_map;	//raw heightmap of terrain
	
	Terrain(int,int,int);

private:
	int depth;	//number of octaves used to generate. 
	std::vector<float> rand_array;	//array for generating heightmap of terrain
	void gen_map(int = -1);	//generate heightmap
	std::vector<std::vector<float> > gen_octave(float, int);	//generate one octave of terrain and interpolate it
	float interpolate(float, float, float);		//interpolation function
};

#endif
