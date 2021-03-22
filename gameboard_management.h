#pragma once

#include <vector>
#include <memory>
#include <algorithm>
#include <stdio.h>
#include <stdlib.h>

#include "blocks.h"
#include "wndvisual.h"

namespace tetris {
	class gameboard {
	public:
		struct boardline {
			int col[11];
			boardline* nxt;
			boardline(int k = -1, boardline* NXT = nullptr) : nxt(NXT) {
				std::fill(col, col + 11, k);
			}
		};
	private:
		boardline bhead;
	public:
		gameboard() {
			boardline* p = &bhead;
			for(int i = 0; i < 25; i++) {
				p->nxt = new boardline;
				p = p->nxt;
			}
		}
		~gameboard() {
			boardline* p = &bhead;
			while(p->nxt != nullptr) {
				boardline* nnxt = p->nxt->nxt;
				delete p->nxt;
				p->nxt = nnxt;
			}
		}
		
		boardline* getNthLine(int n) {
			boardline* p = &bhead;
			for(int i = 0; i < n; i++) {
				p = p->nxt;
			}
			return p;
		}
		
		int add(coord cen, int bKind, int d) {
			for(coord p : dir(blk[bKind], d)) {
				coord k = cen + p;
				if(k.x>20)return 1;
				getNthLine(k.x)->col[k.y] = bKind;
			}
			return 0;
		}
		
		void del(coord cen, int bKind, int d) {
			for(coord p : dir(blk[bKind], d)) {
				coord k = cen + p;
				getNthLine(k.x)->col[k.y] = -1;
			}
		}

		void draw(int bx, int by, coord cen, int bKind, int d) {
			for(coord p : dir(blk[bKind], d)) {
				coord k = cen + p;
				getNthLine(k.x)->col[k.y] = bKind;
				gotoxy(bx + 1 + (20 - k.x) , by + 1 + 2 * k.y);
			}
		}
		
		bool canMove(coord cen, int bKind, int d) {
			for(coord p : dir(blk[bKind], d)) {
				coord k = cen + p;
				if(getNthLine(k.x)->col[k.y] != -1 || 1 > k.y || k.y > 10 || 1 > k.x || k.x > 20)
					return false;
			}
			return true;
		}

		int addAttackLine(int n, int x) {
			for(int i = 0; i < n; i++) {
				boardline* p = bhead.nxt;
				bhead.nxt = new boardline(7);
				bhead.nxt->col[x] = -1;
				bhead.nxt->nxt = p;
				p = bhead.nxt;
			}
			for(int i = 0; i < n; i++) {
				boardline* p = getNthLine(25 + n - i);
				bool flag = false;
				for(int i = 1; i <= 10; i++) {
					if(p->col[i] != -1) {
						flag = true;
						break;
					}
				}
				if(flag)
					return 1;
			}
			return 0;
		}
		
		int clear() {
			int ret = 0;
			for(int i = 1; i <= 20; i++) {
				boardline* prv = getNthLine(i - 1);
				boardline* now = prv->nxt;
				bool flag = true;
				for(int j = 1; j <= 10; j++) {
					if(now->col[j] == -1) {
						flag = false;
						break;
					}
				}
				if(flag) {
					getNthLine(25)->nxt = new boardline;
					prv->nxt = now->nxt;
					delete now;
					i--;
					ret++;
				}
			}
			return ret;
		}
		
		int getBlkInfo(int x, int y) {
			return getNthLine(x)->col[y];
		}
	};
	
	void showGameboard(int bx, int by, gameboard& g) {
		gotoxy(bx, by);
		GRAY; wprintf(L"■■■■■■■■■■■■");
		for(int i = 1; i <= 25; i++) {
			gotoxy(bx, by + i);
			GRAY; wprintf(L"■");
			gameboard::boardline* p = g.getNthLine(26 - i);
			for(int j = 1; j <= 10; j++) {
				switch(p->col[j]) {
					case E: txtColor(COL_WHITE  ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"  "); break;
					case I: txtColor(COL_SKYBLUE,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case L: txtColor(COL_BLUE   ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case J: txtColor(COL_ORANGE ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case O: txtColor(COL_YELLOW ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case S: txtColor(COL_GREEN  ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case T: txtColor(COL_PINK   ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case Z: txtColor(COL_RED    ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▣"); break;
					case G: txtColor(COL_GRAY   ,i<=6?COL_VIOLET:COL_BLACK); wprintf(L"▩"); break;
				}
			}
			GRAY; wprintf(L"■");
		}
		gotoxy(bx, by + 26);
		GRAY; wprintf(L"■■■■■■■■■■■■");
	}
}