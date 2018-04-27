#include "enemy.hpp"
#include "gameObject.hpp"
#include "global.hpp"
#include <random>
#include <cmath>

Enemy::Enemy() : GameObject() {}

void Enemy::set_up(int xx,int yy,int idd){
	
	x=xx;
	y=yy;
	
	id=idd;
	
	for(int i=0;i<24;i++){
		for(int j=0;j<80;j++){
			visited[{i,j}]=false;
			cost[{i,j}]={2147483647,2147483647,2147483647};
		}
	}
	
	calc_path(player.y,player.x,village);
	

}

void Enemy::tick(){
	
	
	
	
}

std::vector<std::vector<int> > Enemy::calc_path(int sy,int sx,std::vector<std::vector<std::string> >grid){
	
	//G H F
	cost[{sy,sx}]={0,calc_dis(sy,sx),calc_dis(sy,sx)};
	calc_sur(sy,sx);
	
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
		
		
		//check win condition here!
		
		
		
		calc_sur(nxt[0],nxt[1]);
	}
	
	
}


int Enemy::calc_dis(int y,int x){
	return abs(player.y-y)+abs(player.x-x);
}

void Enemy::calc_sur(int y,int x){
	visited[{y,x}]=true;
	for(int i=-1;i<2;i++){
		for(int j=-1;j<2;j++){
			if(i==0||j==0){
				if(y+i>=24||y+i<0){
					continue;
				}
				if(x+j>=80||x+j<0){
					continue;
				}
				if(cost[{y+i,x+j}][0]>cost[{y,x}][0]+1){
					cost[{y+i,x+j}]={cost[{y,x}][0]+1,calc_dis(y+i,x+j),cost[{y,x}][0]+1+calc_dis(y+i,x+j)};
				}
			}
		}
	}
	
}














