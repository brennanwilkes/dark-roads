#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class Terrain{
public:
	int width;	//width of generated terrain
	int length;	//y-length of generated terrain
	int seed;	//seed used to generate terrain
	
	std::vector<std::vector<int> > raw_map;	//raw heightmap of terrain
	
	Terrain(int,int,int);

private:
	void gen_map(int);	//generate heightmap
	std::vector<std::vector<float> > octave(int, int);	//generate one octave of terrain
	
};

#endif
