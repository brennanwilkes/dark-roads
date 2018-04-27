#ifndef ENEMY_H
#define ENEMY_H

#include "gameObject.hpp"
#include <map>
#include <string>
#include <vector>

class Enemy : public GameObject{
public:
	Enemy();
	
	void set_up(int xx,int yy,int idd);
	
	void tick();
	
	
	std::vector<std::vector<int> > path;
	
	std::vector<std::vector<int> > calc_path(int,int,std::vector<std::vector<std::string> >);	
	
	
	std::map<std::vector<int>,bool> visited;
	std::map<std::vector<int>,std::vector<int> > cost;
	
	int calc_dis(int,int);
	
	void calc_sur(int,int);
	
	
};
#endif
