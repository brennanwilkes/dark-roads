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
	

	for (int y2;y2<24;y2++){
		chunk.push_back({});
		for (int x2=0;x2<80;x2++){
			
			if(rand()%10000<10){
				chunk[y2].push_back("o");
			}
			else{
				chunk[y2].push_back(" ");
			}
		}
	}
	
	
	chunks[{y,x}]=chunk;
	chunk_coords.push_back({y,x});
	return chunk;
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
	
	for (int y2=0;y2<24;y2++){
		chunk.push_back({});
		for (int x2=0;x2<80;x2++){
			value = myModule.GetValue ((y*24*0.01)+(y2*0.01), (x*80*0.01)+(x2*0.01), 0.01);
			//std::cout<<value<<std::endl;
			if(value>0){
				chunk[y2].push_back(" ");
			}
			else{
				chunk[y2].push_back("^");
			}
		}
	}
	
	
	chunks[{y,x}]=chunk;
	chunk_coords.push_back({y,x});
}
