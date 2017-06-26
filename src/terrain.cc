#include "Terrain.hpp"

Terrain::Terrain(int w, int l, int s){
	//constructor for terrain object
	width = w;
	length = l;
	seed = s;
	raw_map.resize(width, std::vector<int>(length) );
	
	srand(seed);
	gen_map(3);	//use 3 octaves for now
}

void Terrain::gen_map(int octaves){
	//generate heightmap for terrain
	
	
}

std::vector<std::vector<float> > Terrain::octave(int range, int freq){
	//generate one octave for gen_map
	
}
