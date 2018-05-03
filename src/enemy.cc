#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"
#include <random>
#include <cmath>

Enemy::Enemy() : GameObject() {}

void Enemy::set_up(int xx,int yy,std::string chr){
	
	x=xx;
	y=yy;
	
	img=chr;
	
	
	
	path = calc_path(y,x,village);
	
	path_tick=0;
	
}

void Enemy::tick(){
	path_tick++;
	
	
	if(path_tick>5){
		path_tick=0;
		path=calc_path(y,x,village);
	}
	
	
	
	if(path.size()>1){
		x=path[path.size()-1][1];
		y=path[path.size()-1][0];
		path.pop_back();
	}
	
	
}

std::vector<std::vector<int> > Enemy::calc_path(int sy,int sx,std::vector<std::vector<std::string> >grid){
	
	if(grid[sy][sx]=="^"||grid[sy][sx]=="_"){
		return {};
	}
	
	for(int i=0;i<24;i++){
		for(int j=0;j<80;j++){
			visited[{i,j}]=false;
			cost[{i,j}]={2147483647,2147483647,2147483647};
		}
	}
	
	
	//G H F
	cost[{sy,sx}]={0,calc_dis(sy,sx),calc_dis(sy,sx)};
	calc_sur(sy,sx,grid);
	
	int lowest;
	std::vector<int> nxt;
	
	while (true){
		lowest=2147483647;
		nxt={};
		for(std::map<std::vector<int>,std::vector<int> >::iterator it = cost.begin(); it != cost.end(); ++it) {
			//tmp_str=it->first;
			if(visited[it->first]){
				continue;
			}
			if(cost[it->first][2]<lowest){
				nxt=it->first;
				lowest=cost[it->first][2];
			}
		}
		
		
		
		if(lowest>calc_dis(sy,sx)*2){		//no path or too long path
			//std::cout<<"Couldnt find path"<<std::endl;
			return {};
		}
		if(nxt[0]==player.y&&nxt[1]==player.x){
			return get_path({player.y,player.x},sy,sx);
		}
		
		calc_sur(nxt[0],nxt[1],grid);
	}
	
	
}


int Enemy::calc_dis(int y,int x){
	return abs(player.y-y)+abs(player.x-x);
}

void Enemy::calc_sur(int y,int x,std::vector<std::vector<std::string> >grid){
	visited[{y,x}]=true;
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0&&j==0){
				continue;
			}
			if(i==0||j==0){
				if(y+i>=24||y+i<0){
					continue;
				}
				if(x+j>=80||x+j<0){
					continue;
				}
				if(grid[y][x]!="^"&&grid[y][x]!="#"&&grid[y][x]!="O"&&grid[y][x]!="_"){
					if(cost[{y+i,x+j}][0]>cost[{y,x}][0]+1){
						cost[{y+i,x+j}] = { cost[{y,x}][0]+1,	calc_dis(y+i,x+j),	cost[{y,x}][0]	+1+	calc_dis(y+i,x+j)	};
						back[{y+i,x+j}]={y,x};
					}
				}
			}
		}
	}
	
}


std::vector<std::vector<int> > Enemy::get_path(std::vector<int> nd,int sy,int sx){
		std::vector<std::vector<int> > pth={};
		while(true){
			if(nd[0]==sy&&nd[1]==sx){
				break;
			}
			pth.push_back(nd);
			nd=back[nd];
		}
		
		return pth;
}














