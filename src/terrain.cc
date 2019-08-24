#include <iostream>
#include "terrain.hpp"
#include "global.hpp"
#include <random>
using namespace std;

Terrain::Terrain(){	
	
	
	
}

void Terrain::pro_chunk(int y,int x){
	
	vector<vector<string> > chunk = {};


	for(int i=0;i<chunk_coords.size();i++){
		if (chunk_coords[i][0]==y&&chunk_coords[i][1]==x){
			return;
		}
	}
	noise::module::Perlin myModule;
	
	double value;
	double highest=-1;
	vector<int> high_coord;
	
	for (int y2=0;y2<24;y2++){
		chunk.push_back({});
		for (int x2=0;x2<80;x2++){
			value = myModule.GetValue ((y*24*0.01)+(y2*0.01), (x*80*0.01)+(x2*0.01), 0.01);
			if(value>-0.1){
				if(value>highest&&y2>3&&y2<21&&x2>3&&x2<77){
					highest=value;
					high_coord = {y2,x2};
				}
				chunk[y2].push_back(" ");
			}
			else{
				chunk[y2].push_back("^");
			}
		}
	}
	
	chunk[high_coord[0]][high_coord[1]] = "o";
	
	
	chunks[{y,x}]=chunk;
	chunk_coords.push_back({y,x});
}
