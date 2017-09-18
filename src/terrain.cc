#include <iostream>
#include "terrain.hpp"
#include "global.hpp"

//TODO: switch to float-based coordinate system (allows for 'infinite' precision)
Terrain::Terrain(int w, int l, int s,int sx,int sy){	
	
	//width, height, seed, coordinates
	width = w;
	height = l;
	seed = (s*1000000)+(sx*1000)+sy;
	
	x=sx;
	y=sy;
	
	raw_map.resize(width, std::vector<float>(height));
	
	srand(seed);
	
	water_level=40;//rand()%255;
	
	gen_map();
	
	sprite = new sf::Sprite;
	heightmap_tex = new sf::Texture;
	map_tex = new sf::Texture;
	pixels = new sf::Uint8[w*l*4];
	cpixels = new sf::Uint8[w*l*4];
	
	
	create_height_tex();
	colourize();
	draw_sprite(map_tex);
	
	
}

void Terrain::gen_map(int num_octaves){
	//generate heightmap for terrain	(if num_octaves is -1, will loop until it cant anymore)

	//populate rand_array with floats between 0 and 1.
	rand_array.resize((width+1)*(height+1));
	
	for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){
		*elem = float(rand())/RAND_MAX;
	}
	
	
	/*if (fullmap.count(std::make_pair(x+1,y))){		//new terrain west
		
		std::cout<<"west"<<std::endl;
		
		for(unsigned int i = width; i < rand_array.size(); i+=width+1){		
			rand_array[i] = fullmap[std::make_pair(x+1,y)]->rand_array[i-width];
		}
	}
	else if(fullmap.count(std::make_pair(x-1,y))){	//new terrain east
		
		std::cout<<"east"<<std::endl;
		
		for(unsigned int i = width; i < rand_array.size(); i+=width+1){		
			rand_array[i] = fullmap[std::make_pair(x-1,y)]->rand_array[i+width];
		}
	}
	else{											//isolated square
		for(unsigned int i = width; i < rand_array.size(); i+=width+1){			// 		< x > wrapping
			rand_array[i] = rand_array[i-width];
			//std::cout<<"i "<<i<<" - width "<<width<<" - rand_array[i] "<<rand_array[i]<<std::endl;
		}
	}*/
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	if (fullmap.count(std::make_pair(x+1,y))){		//new terrain west
		
		
		unsigned int ti=width;
		for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){

			float temp = fullmap[std::make_pair(x+1,y)]->rand_array[ti-width]+((float(rand())/RAND_MAX)/10.0);

			ti++;
			if (temp<0){
				temp = 0.00001;
			}
			else if (temp>1){
				temp = 0.99999;
			}

			*elem = temp;
		}
		
	}
	else if(fullmap.count(std::make_pair(x-1,y))){	//new terrain east
		
		
		unsigned int ti=0;
		for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){
			float temp2 = fullmap[std::make_pair(x-1,y)]->rand_array[ti+width]+((float(rand())/RAND_MAX)/10.0);
			ti++;
			if (temp2<0){
				temp2 = 0.00001;
			}
			else if (temp2>1){
				temp2 = 0.99999;
			}
			
			*elem = temp2;
		}
		
	}
	else{											//isolated square
		for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){
			*elem = float(rand())/RAND_MAX;
		}
		for(unsigned int i = width; i < rand_array.size(); i+=width+1){			// 		< x > wrapping
			rand_array[i] = rand_array[i-width];
			//std::cout<<"i "<<i<<" - width "<<width<<" - rand_array[i] "<<rand_array[i]<<std::endl;
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	for(unsigned int i = (width+1)*height; i < rand_array.size(); i++){		// 		/\ y \/ wrapping
		rand_array[i] = rand_array[i-(width+1)*height];
	}
	
	float persistence = 0.25;						//how smooth the curve is (lower is more smooth)
	float range = 1;								//the maximum height change possible to generate. 
	int freq = 4;									//the number of steps in the first octave.
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
		freq *= 2;				//frequency will double
		if(freq > width || freq > height){
			depth = i+1;
			break;
		}
	}
	
}

std::vector<std::vector<float> > Terrain::gen_octave(float range, int freq){
	//generates a single octave and interpolates it
	
	const unsigned int x_step(width/freq), y_step(height/freq);		//width and height of a 'unit square', in pixels
	std::vector<std::vector<float> > octave(freq, std::vector<float>(freq)), 
									 intered(width, std::vector<float>(height));
	//interpolate
	for(unsigned int x = 0; x < width; x++){
		for(unsigned int y = 0; y < height; y++){
			intered[x][y] = range * interpolate(
								interpolate(
									rand_array[(x/x_step)*x_step + (y/y_step)*y_step*(width + 1)], 
									rand_array[(x/x_step)*x_step + x_step + (y/y_step)*y_step*(width + 1)], 
									float(x%x_step)/x_step), 
								interpolate(
									rand_array[(x/x_step)*x_step + ((y/y_step)*y_step + y_step)*(width + 1)], 
									rand_array[(x/x_step)*x_step + x_step + ((y/y_step)*y_step + y_step)*(width + 1)], 
									float(x%x_step)/x_step), 
								float(y%y_step)/y_step);
		}
	}
	
	return intered;
}
float Terrain::interpolate(float q1, float q2, float pos){
	return q1 * (1-pos) + pos * q2;
}

void Terrain::create_height_tex(){
	heightmap_tex->create(width,height);
	highest = raw_map[0][0];
	for(unsigned int i = 0; i < width*height; i++)//find highest
		if(highest < raw_map[i%width][i/height]) highest = raw_map[i%width][i/height];
		
	
	for(unsigned int i = 0; i < width*height; i++){
		pixels[i*4] = 255;
		pixels[i*4+1] = 255;
		pixels[i*4+2] = 255;
		pixels[i*4+3] = int(raw_map[i%width][i/height]*255/highest);
	}
	heightmap_tex->update(pixels);
	
}

void Terrain::colourize(){
	map_tex->create(width,height);
	highest = raw_map[0][0];
	for(unsigned int i = 0; i < width*height; i++)//find highest
		if(highest < raw_map[i%width][i/height]) highest = raw_map[i%width][i/height];
		
	
	
	int weight;		//I thought about spelling this wait #welcometosummer
	for(unsigned int i = 0; i < width*height; i++){
		weight = int(raw_map[i%width][i/height]*255/highest);
		
		
		
		if (weight<water_level){
			cpixels[i*4] = 0;
			cpixels[i*4+1] = 0;
			cpixels[i*4+2] = 255;
		}
		else if(weight<100){
			cpixels[i*4] = 255;
			cpixels[i*4+1] = 205;
			cpixels[i*4+2] = 155;
		}
		else if(weight<200){
			cpixels[i*4] = 0;
			cpixels[i*4+1] = 205;
			cpixels[i*4+2] = 0;
		}
		else{
			cpixels[i*4] = 125;
			cpixels[i*4+1] = 125;
			cpixels[i*4+2] = 125;
		}
		cpixels[i*4+3] = weight;
	}
	map_tex->update(cpixels);
	
}

void Terrain::draw_sprite(sf::Texture* dis_tex){
	sprite->setTexture(*dis_tex);
	sprite->setScale(800.0/width, 800.0/height);
}


