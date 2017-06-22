#ifndef BMAP_H
#define BMAP_H

#include <map>
#include <SFML/Graphics.hpp>
#include <random>
#include <vector>

class BMap{
public:
	int x;
	int y;
	int oct;
	float lac;
	float per;
	
	std::vector<float> noise;
	
	BMap(int,int,int,float,float);
	
	std::vector<float> genNoise();
	
	float perlinNoise();
	
};

#endif
