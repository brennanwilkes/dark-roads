#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
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
	

	
	std::vector<float> rand_array;		//array for generating heightmap of terrain
	

private:
	int depth;							//number of octaves used to generate. 

	
	float highest;
	
	
	bool spam;
};

#endif
