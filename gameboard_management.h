#pragma once

#include<vector>
#include"blocks.h"

namespace tetris{
	class gameboard{
	private:
		struct boardline{
			int col[11];
			boardline* nxt;
			boardline(boardline* NXT=nullptr) : nxt(NXT) {}
		};
		boardline bhead;
	public:
		gameboard(){
			boardline* p = &bhead;
			for(int i=0;i<25;i++){
				p->nxt = new boardline;
				p = p->nxt;
			}
		}
		
		boardline* getNthLine(int n){
			boardline* p = &bhead;
			for(int i=0;i<n;i++){
				p = p->nxt;
			}
			return p;
		}
		
		void add(coord cen, int bKind, int d){
			for(coord p:dir(blk[bKind],d)){
				coord k = cen+p;
				getNthLine(k.x)->col[k.y] = bKind;
			}
		}
		
		void clear(){
			for(int i=1;i<=20;i++){
				boardline* prv = getNthLine(i-1);
				boardline* now = prv->nxt;
				for(int j=1;j<=10;j++){
					
				}
			}
		}
	};
}