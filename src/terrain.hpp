#ifndef TERRAIN_H
#define TERRAIN_H

#include <map>
#include <random>
#include <vector>
#include <string>

class Terrain{
public:
	Terrain();
	
	std::vector<std::vector<std::string> > gen_chunk(int,int);
	
	std::map<std::vector<int>,std::vector<std::vector<std::string> > > chunks;
	

private:
	
};

#endif
