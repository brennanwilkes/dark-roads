#include <iostream>
#include "terrain.hpp"
#include "global.hpp"
#include <random>
using namespace std;

Terrain::Terrain(){	
	
	
	
}

vector<vector<string> > Terrain::gen_chunk(int y,int x){
	vector<vector<string> > chunk = {};


	for(int i=0;i<chunk_coords.size();i++){
		if (chunk_coords[i][0]==y&&chunk_coords[i][1]==x){
			return chunk;
		}
	}
	
	srand(time(0));
	

	for (int y=0;y<24;y++){
		chunk.push_back({});
		for (int x=0;x<80;x++){
			
			if(rand()%10000<10){
				chunk[y].push_back("o");
			}
			chunk[y].push_back(" ");
		}
	}
	
	
	chunks[{y,x}]=chunk;
	return chunk;
}
