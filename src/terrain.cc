#include <iostream>
#include "terrain.hpp"

//TODO: switch to float-based coordinate system (allows for 'infinite' precision)
Terrain::Terrain(int w, int l, int s,bool spammy){
	
	spam=spammy;
	
	
	//width, height, seed
	width = w;
	height = l;
	seed = s;
	raw_map.resize(width, std::vector<float>(height));
	
	srand(seed);
	
	water_level=rand()%255;
	//std::cout<<"water "<<water_level<<" "<<rand()<<std::endl;
	
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
	rand_array.resize(width*height, 0);
	
	for(auto elem = rand_array.begin(); elem != rand_array.end(); elem++){
		*elem = float(rand())/RAND_MAX;
		//std::cout<<*elem<<std::endl;
	}
	
	
	/*for(unsigned int a=0;a<width;a++){
		for(unsigned int b=0;b<height;b++){
			rand_array[(a*height)+b]=float(rand())/RAND_MAX;
		}
	}*/
	
	float persistence = float(rand())/RAND_MAX;		//how smooth the curve is (lower is more smooth)
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
		freq *= 2;		//frequency will double
		if(freq > width || freq > height){
			depth = i+1;
			break;
		}
	}
	
}

std::vector<std::vector<float> > Terrain::gen_octave(float range, int freq){
	if(spam)	std::cout << "running octave" << std::endl;
	//generates a single octave and interpolates it
	
	const unsigned int x_step(width/freq), y_step(height/freq);		//width and height of a 'unit square', in pixels
	std::vector<std::vector<float> > octave(freq, std::vector<float>(freq)), 
									 intered(width, std::vector<float>(height));
	
	if(spam)	std::cout << "octave generated!" << std::endl;
	if(spam)	std::cout << "width: " << width << "\nheight: " << height << "\nfreq: " << freq << "\nrange: " << range << "\nx_step: " << x_step << "\ny_step: " << y_step <<std::endl;
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
			if(intered[x][y]>100 || intered[x][y]<-100){
				//THERE IS A PROBLEM HERE SOMETIMES THIS IS TRIGGERED AND CAUSES BLACK PIXELS
				
				std::cout<<x<<" "<<y<<" "<<intered[x][y]<<std::endl;
				//std::cout<<rand_array[(x/x_step)*x_step + (y/y_step)*y_step*width]<<std::endl;
				//std::cout<<rand_array[(x/x_step)*x_step + x_step + (y/y_step)*y_step*width]<<std::endl;
				std::cout<<(x/x_step)*x_step + ((y/y_step)*y_step + y_step)*width<<" "<<rand_array[(x/x_step)*x_step + ((y/y_step)*y_step + y_step)*width]<<std::endl;
				std::cout<<(x/x_step)*x_step + x_step + ((y/y_step)*y_step + y_step)*width<<" "<<rand_array[(x/x_step)*x_step + x_step + ((y/y_step)*y_step + y_step)*width]<<std::endl;
				//std::cout<<float(x%x_step)/x_step<<std::endl;
				//std::cout<<float(y%y_step)/y_step<<std::endl;
				std::cout<<std::endl;
				
			}
		}
	}
	
	return intered;
}
float Terrain::interpolate(float q1, float q2, float pos){
	/*if(q1>100000||q1<-100000){
		std::cout<<"q1"<<std::endl;
	}
	
	if(q2>100000||q2<-100000){
		std::cout<<"q2"<<std::endl;
	}*/
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


