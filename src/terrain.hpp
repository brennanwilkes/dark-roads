#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
#include <random>
#include <vector>
#include <string>
#include "noise/noise.h"

class Terrain{
public:
	Terrain();
	
	std::vector<std::vector<std::string> > gen_chunk(int,int);
	void pro_chunk(int, int);
	
	std::map<std::vector<int>,std::vector<std::vector<std::string> > > chunks;
	
	
	std::vector<std::vector<int> > chunk_coords={{0,0}};
	

private:
	
};

#endif
