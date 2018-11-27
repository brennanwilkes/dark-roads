#include "world.hpp"

using namespace std;

World::World(){
	lights = {};
}
World::~World(){
}
void World::generate(){
	int a = 0;
	for(int i=0;i<300;i++){
		if(rand()%1000<(300-i)){
			a = rand()%360;
			a = a*180.0/3.14159265358979323846;
			lights.push_back({(int)(i*2*cos(a)),(int)(i*2*sin(a)),rand()%15});
			//cout<<lights[lights.size()-1][0]<<" "<<lights[lights.size()-1][1]<<" "<<lights[lights.size()-1][2]<<endl;
		}
	}
	
}
