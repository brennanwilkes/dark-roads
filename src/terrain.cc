#include <iostream>
#include "terrain.hpp"
#include "global.hpp"
#include <random>
#include <cmath>


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
	
	vector<int> water_seed = {};
	double water_seed_height = 0;
	vector<int> water_direction = {};
	
	for (int y2=0;y2<24;y2++){
		chunk.push_back({});
		for (int x2=0;x2<80;x2++){
			value = myModule.GetValue ((y*24*0.01)+(y2*0.01), (x*80*0.01)+(x2*0.01), 0.01);
			
			if(fmod(value,0.1)>0.00475&&fmod(value,0.1)<0.005&&water_seed.size()==0){
				if(y2>2&&y2<22&&x2>2&&x2<78){
					water_seed = {y2,x2};
					water_seed_height = value;
					water_direction = {((rand()%2)*2)-1,((rand()%2)*2)-1};
				}
				//chunk[y2].push_back("_");
				//continue;
			}
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
	
	if(water_seed.size()!=0){
		for(int i=-1;i<2;i++){
			for(int j=-1;j<2;j++){
				chunk[water_seed[0]+i][water_seed[1]+j]="_";
			}
		}
		
		int rand_dir = 0;
		
		for (int y2=2;y2<22;y2++){
			for (int x2=2;x2<78;x2++){
				value = myModule.GetValue ((y*24*0.01)+(y2*0.01), (x*80*0.01)+(x2*0.01), 0.01);
				
				if(value>water_seed_height-0.25&&value<water_seed_height+0.25){
					rand_dir = rand()%3;
					if(rand_dir==0){
						if(chunk[y2-water_direction[0]][x2-water_direction[1]]=="_"){
							chunk[y2][x2] = "_";
						}
					}
					else if(rand_dir==1){
						if(chunk[y2][x2-water_direction[1]]=="_"){
							chunk[y2][x2] = "_";
						}
					}
					else if(rand_dir==2){
						if(chunk[y2-water_direction[0]][x2]=="_"){
							chunk[y2][x2] = "_";
						}
					}
				}
			}
		}
	}
	
	chunk[high_coord[0]][high_coord[1]] = "o";
	
	
	chunks[{y,x}]=chunk;
	chunk_coords.push_back({y,x});
}
