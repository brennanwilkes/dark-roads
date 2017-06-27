#include <iostream>
#include "terrain.hpp"

//TODO: switch to float-based coordinate system (allows for 'infinite' precision)
Terrain::Terrain(int w, int l, int s){
	//width, height, seed
	width = w;
	height = l;
	seed = s;
	raw_map.resize(width, std::vector<float>(height));
	
	srand(seed);
	
	//populate rand_array with floats between 0 and 1.
	rand_array.resize(width*height, 0);
	for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){
		*elem = float(rand())/RAND_MAX;
	}
	
	gen_map();
}

void Terrain::gen_map(int num_octaves){
	//generate heightmap for terrain	(if num_octaves is -1, will loop until it cant anymore)
	std::cout << "gen_map running!" << std::endl;
	float persistence = float(rand())/RAND_MAX;	//how smooth the curve is (lower is more smooth)
	float range = persistence;	//the range (+/-) possible to generate. 
	int freq = 4;	//the number of steps in the first octave.
	std::vector<std::vector<float> > octave;
	
	for(unsigned int i = 0; i != num_octaves; i++){
		//generate octave and add to raw_map
		octave = gen_octave(range, freq);
		for(unsigned int x = 0; x < width; x++){
			for(unsigned int y = 0; y < height; y++){
				raw_map[x][y] += octave[x][y];
			}
		}
		//determine next octave's range and frequency
		range *= persistence;	//range will decrease
		freq *= 2;		//frequency will double
		if(freq > width || freq > height){
			depth = i+1;
			break;
		}
	}
	
}

std::vector<std::vector<float> > Terrain::gen_octave(float range, int freq){
	std::cout << "running octave" << std::endl;
	//generates a single octave and interpolates it
	
	const unsigned int x_step(width/freq), y_step(height/freq);		//width and height of a 'unit square', in pixels
	std::vector<std::vector<float> > octave(freq, std::vector<float>(freq)), 
									 intered(width, std::vector<float>(height));
	
	std::cout << "octave generated!" << std::endl;
	std::cout << "width: " << width << "\nheight: " << height << "\nfreq: " << freq << "\nrange: " << range << "\nx_step: " << x_step << "\ny_step: " << y_step <<std::endl;
	//interpolate
	for(unsigned int x = 0; x < width; x++){
		for(unsigned int y = 0; y < height; y++){
			intered[x][y] = range * interpolate(
								interpolate(
									rand_array[(x/x_step)*x_step + (y/y_step)*y_step*width], 
									rand_array[(x/x_step)*x_step + x_step + (y/y_step)*y_step*width], 
									float(x%x_step)/x_step), 
								interpolate(
									rand_array[(x/x_step)*x_step + ((y/y_step)*y_step + y_step)*width], 
									rand_array[(x/x_step)*x_step + x_step + ((y/y_step)*y_step + y_step)*width], 
									float(x%x_step)/x_step), 
								float(y%y_step)/y_step);
		}
	}
	
	return intered;
}
float Terrain::interpolate(float q1, float q2, float pos){
	return q1 * (1-pos) + pos * q2;
}
