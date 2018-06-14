#ifndef WORLD_H
#define WORLD_H

#include <map>
#include <string>
#include <random>
#include <iostream>
#include <vector>
#include <cmath>

class World{
public:
	World();
	~World();
	void generate();
	std::vector<std::vector<int> > lights;
};

#endif
