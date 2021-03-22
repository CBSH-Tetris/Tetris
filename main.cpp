#include "blocks.h"
#include "gameboard_management.h"
#include "wndvisual.h"
#include "menu.h"
#include "room.h"
#include <cstdio>
#include <thread>
#include <ctime>
#include <sys/timeb.h>
#include <random>
#include <conio.h>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 6);

struct Player {
	tetris::gameboard board;
	int y = 18, x = 5; // position of new block
	int bK, bD;
	bool moveEnd = true, moved = true;

	void createBlock() {
		y = 18, x = 5;
		bK = dis(gen);
		bD = 0;
	}
};

Player P1, P2;
bool P1_end = false, P2_end = false;
bool moved = false;

DWORD GetTickCount(void);

int main(void){
	int xx, yy, lr;
	wndSize(32, 70);
	mainMenu();

	while(1) {
		GetMouseState(&xx, &yy, &lr);
		if(lr == 1) {
			if(13 <= yy && yy <= 15 && 24 <= xx && xx <= 44) { // CREATE
				createRoom();
				break;
			}
			if(18 <= yy && yy <= 20 && 24 <= xx && xx <= 44) { // JOIN
				joinRoom();
				break;
			}
			if(23 <= yy && yy <= 25 && 24 <= xx && xx <= 44) { // CONTROLS
				tutorial();
				mainMenu();
			}
			if(28 <= yy && yy <= 30 && 24 <= xx && xx <= 44) { // QUIT
				exit(0);
			}
		}
	}
	
	// 키 입력과 서버 통신을 쓰레드로, 블럭을 그리는 작업을 main 내에서 처리함
	
	

	init();
	tetris::showGameboard(0, 5, P1.board);
	tetris::showGameboard(30, 5, P2.board);
/*
	std::thread dropBlock(
		[]() {
			P1.createBlock();
			P2.createBlock();
			bool moveEnd = true;
			int prevT = -1000;
			while(!P1_end & !P2_end) {
				if(GetTickCount() >= prevT + 1000) {
					prevT = GetTickCount();

					P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
					if(P1.board.canMove({P1.y - 1, P1.x}, P1.bK, P1.bD)) {
						P1.board.add({P1.y -= 1, P1.x}, P1.bK, P1.bD);
					}
					else {
						P1.board.add({P1.y, P1.x}, P1.bK, P1.bD);
						P1.createBlock();
					}

					P2.board.del({P2.y, P2.x}, P2.bK, P2.bD);
					if(P2.board.canMove({P2.y - 1, P2.x}, P2.bK, P2.bD)) {
						P2.board.add({P2.y -= 1, P2.x}, P2.bK, P2.bD);
					}
					else {
						P2.board.add({P2.y, P2.x}, P2.bK, P2.bD);
						P2.createBlock();
					}
					P1.moved = P2.moved = true;
				}
			}
		}
	);
*/

	std::thread moveBlock(
		[]() {
			int prevT2 = -50;
			char c;
			while(!P1_end & !P2_end) {
				if (GetTickCount() >= prevT2 + 200) {
						prevT2 = GetTickCount();
						c = _getch();
						if (c == -32) {
							c = _getch();
							switch (c) {
								case LEFT:
									P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
									if(P1.board.canMove({P1.y, P1.x - 1}, P1.bK, P1.bD)) {
										P1.board.add({P1.y, P1.x -= 1}, P1.bK, P1.bD);
										P1.moved = true;
									}
									break;
								case RIGHT:
									P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
									if(P1.board.canMove({P1.y, P1.x + 1}, P1.bK, P1.bD)) {
										P1.board.add({P1.y, P1.x += 1}, P1.bK, P1.bD);
										P1.moved = true;
									}
									break;
								case UP:
									P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
									if(P1.board.canMove({P1.y, P1.x}, P1.bK, (P1.bD + 1) % 4)) {
										P1.bD = (P1.bD + 1) % 4;;
										P1.board.add({P1.y, P1.x}, P1.bK, P1.bD);
										P1.moved = true;
									}
									break;
								case DOWN:
									P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
									while(P1.board.canMove({P1.y - 1, P1.x}, P1.bK, P1.bD)) {
										P1.y--;
									}
									P1.board.add({P1.y, P1.x}, P1.bK, P1.bD);
									P1.moved = true;
									break;
						}
					}
				}
			}
		}
	);

	P1.createBlock();
	P2.createBlock();
	bool moveEnd = true;
	int prevT = -600;
	while(!P1_end & !P2_end) {
		if(GetTickCount() >= prevT + 600) {
			prevT = GetTickCount();
			P1.board.del({P1.y, P1.x}, P1.bK, P1.bD);
			if(P1.board.canMove({P1.y - 1, P1.x}, P1.bK, P1.bD)) {
				P1.board.add({P1.y -= 1, P1.x}, P1.bK, P1.bD);
			}
			else {
				P1.board.add({P1.y, P1.x}, P1.bK, P1.bD);
				P1.createBlock();
			}

			P2.board.del({P2.y, P2.x}, P2.bK, P2.bD);
			if(P2.board.canMove({P2.y - 1, P2.x}, P2.bK, P2.bD)) {
				P2.board.add({P2.y -= 1, P2.x}, P2.bK, P2.bD);
			}
			else {
				P2.board.add({P2.y, P2.x}, P2.bK, P2.bD);
				P2.createBlock();
			}
			P1.moved = P2.moved = true;
		}
		if(P1.moved) {
			P1.moved = false;
			P1_end = P1.board.addAttackLine(P2.board.clear());
			tetris::showGameboard(0, 5, P1.board);
		}
		if(P2.moved) {
			P2.moved = false;
			P2_end = P2.board.addAttackLine(P1.board.clear());
			tetris::showGameboard(30, 5, P2.board);
		}
	}

	

	return 0;
}
