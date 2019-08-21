#include <iostream>
#include "terrain.hpp"
#include "global.hpp"
#include <random>
using namespace std;

Terrain::Terrain(){	
	
	
	
}

vector<vector<string> > Terrain::gen_chunk(int y,int x){
	srand(time(0));
	
	vector<vector<string> > chunk = {};
	for (int y=0;y<24;y++){
		chunk.push_back({});
		for (int x=0;x<80;x++){
			
			if(rand()%100>98){
				chunk[y].push_back("o");
			}
			chunk[y].push_back(" ");
		}
	}
	
	
	chunks[{y,x}]=chunk;
	return chunk;
}
