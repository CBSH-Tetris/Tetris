#pragma once

#include <utility>
#include <vector>

namespace tetris{
	struct coord{
		int x,y;
		coord(int X=0,int Y=0) : x(X),y(Y) {}
		coord operator+(coord k){
			return coord(x+k.x,y+k.y);
		}
		coord operator*(coord k){
			return coord(x*k.x,y*k.y);
		}
		coord operator*(int k){
			return coord(x*k,y*k);
		}
	};
	
	coord dx[4] = {coord(-1, 0),coord( 0, 1),coord( 1, 0),coord( 0,-1)};
	coord dy[4] = {coord( 0, 1),coord( 1, 0),coord( 0,-1),coord(-1, 0)};
	
	struct block{
		std::vector<coord> v;//c[0] is Center
		block(coord a,coord b,coord c,coord d){
			v.resize(4);
			int i = 0;
			for(auto x:{a,b,c,d}){
				v[i++] = x;
			}
		}
	};
	
	std::vector<coord> dir(block b,int d){
		std::vector<coord> res(4);
		for(int i=0;i<4;i++){
			res[i] = dx[d]*b.v[i].x+dy[d]*b.v[i].y;
		}
		return res;
	}
	
	const block blk[7] = {
		block({0,0},{1,0},{2,0},{0,1}),block({0,0},{1,0},{2,0},{0,-1}),
		block({0,0},{0,1},{1,0},{1,1}),
		block({0,0},{1,0},{0,1},{-1,1}),block({0,0},{1,0},{0,-1},{-1,-1}),
		block({0,0},{1,0},{2,0},{-1,0}),
		block({0,0},{1,0},{0,-1},{0,1})
	};
}