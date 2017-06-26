#include <iostream>
#include "terrain.hpp"

//TODO: only interpolate necessary points for intermediate octaves?

Terrain::Terrain(int w, int l, int s){
	//width, length, seed
	width = w;
	length = l;
	seed = s;
	raw_map.resize(width, std::vector<float>(length) );
	
	srand(seed);
	gen_map(1);	//TODO: make it so that this doesn't kill itself when a division greater than the number of pixels is used :)
}

void Terrain::gen_map(int num_octaves){
	//generate heightmap for terrain
	std::cout << "gen_map running!" << std::endl;
	float persistence = 0.5;//float(rand())/RAND_MAX;	//how smooth the curve is (lower is more smooth)
	float range = persistence;	//the range (+/-) possible to generate. 
	int freq = 4;	//the number of steps in the first octave.
	std::vector<std::vector<float> > prev_octave;
	
	for(unsigned int i = 0; i < num_octaves; i++){
		//generate octave and add to raw_map
		prev_octave = octave(range, freq);
		for(unsigned int x = 0; x < width; x++){
			for(unsigned int y = 0; y < length; y++){
				raw_map[x][y] += prev_octave[x][y];
			}
		}
		//determine next octave's range and frequency
		range *= persistence;	//range will decrease
		freq *= 2;		//frequency will double
	}
	
}

std::vector<std::vector<float> > Terrain::octave(float range, int freq){
	std::cout << "running octave" << std::endl;
	//generate a single octave and interpolates it
	
	const unsigned int x_step(width/freq), y_step(length/freq);		//width and length of a 'unit square', in pixels
	
	std::vector<std::vector<float> > octave_x(freq, std::vector<float>(freq)), 
			octave_y(freq, std::vector<float>(freq)), 
			intered(width, std::vector<float>(length));
	//generate the octave
	for(unsigned int i = 0; i < freq; i++){
		for(unsigned int j = 0; j < freq; j++){
			octave_x[i][j] = range * float(rand())/RAND_MAX;
			octave_y[i][j] = range * float(rand())/RAND_MAX;
		}
	}

	std::cout << "octave generated!" << std::endl;
	std::cout << "width: " << width << "\nheight: " << length << "\nfreq: " << freq << "\nrange: " << range << "\nx_step: " << x_step << "\ny_step: " << y_step <<std::endl;
	//interpolate
	for(unsigned int x = 0; x < width; x++){
		for(unsigned int y = 0; y < length; y++){
			intered[x][y] = octave_x[x/x_step][y/y_step] * (x%x_step) + 
							octave_x[(x/x_step+1)%freq][(y/y_step+1)%freq] * (x_step-x%x_step) + 
							octave_y[x/x_step][y/y_step] * (y%y_step) + 
							octave_y[(x/x_step+1)%freq][(y/y_step+1)%freq] * (y_step-y%y_step);
		}
	}
	
	return intered;
}
