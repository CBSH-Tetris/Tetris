#include "blocks.h"
#include "gameboard_management.h"
#include "wndvisual.h"
#include "menu.h"
#include "room.h"
#include "server.h"
#include <cstdio>
#include <thread>
#include <ctime>
#include <sys/timeb.h>
#include <random>
#include <conio.h>
#include <iostream>

#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77

using namespace std;

std::random_device rd;
std::mt19937 gen(rd());
std::uniform_int_distribution<int> dis(0, 6);

std::random_device rd3;
std::mt19937 gen3(rd3());
std::uniform_int_distribution<int> dis3(1, 10);

struct Player {
	tetris::gameboard board;
	int y = 18, x = 5; // position of new block
	int bK, bD;
	bool moved = false;

	void createBlock() {
		y = 18, x = 5;
		bK = dis(gen);
		bD = 0;
	}
};

Player P1, P2;
Player *slf, *otr;

bool P1_end = false, P2_end = false;
int prevT = -600;
int prevT2 = -50;

DWORD GetTickCount(void);

string IP = "127.0.0.1";

int main(void){
	cin >> IP;

	wndSize(32, 70);
	CursorView(0);
	int xx, yy, lr;

	gotoxy(0, 0);
	printf("\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                         @@@@    @@@@    @@@@    @   @\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                       @        @   @   @       @   @\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                      @        @@@@     @@@    @@@@@\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                     @        @   @       @   @   @\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                     @@@@    @@@@     @@@@   @   @\n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                @@@@@   @@@@@   @@@@@    @@@@@   @    @@@@   \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                 @     @         @      @   @   @    @              \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("                @     @@@@@     @      @@@@    @     @@@            \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("               @     @         @      @  @    @        @            \n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), dis2(gen2));
	printf("              @     @@@@@     @      @   @   @     @@@@             \n\n");
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);

	mainMenu();

	while(1) {
		GetMouseState(&xx, &yy, &lr);
		if(lr == 1) {
			if(13 <= yy && yy <= 15 && 24 <= xx && xx <= 44) { // CREATE
				create();
    			server::makeConnection_s();
				slf = &P1;
				otr = &P2;
				break;
			}
			if(18 <= yy && yy <= 20 && 24 <= xx && xx <= 44) { // JOIN
				join();
    			server::makeConnection_c(IP);
				slf = &P2;
				otr = &P1;
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

	tetris::showGameboard(0, 5, slf->board);
	tetris::showGameboard(30, 5, otr->board);

	std::thread moveBlock(
		[]() {
			char c;
			while(1) {
				if (GetTickCount() >= prevT2 + 200) {
						prevT2 = GetTickCount();
						c = _getch();
						if (c == -32) {
							c = _getch();
							switch (c) {
								case LEFT:
									slf->board.del({slf->y, slf->x}, slf->bK, slf->bD);
									if(slf->board.canMove({slf->y, slf->x - 1}, slf->bK, slf->bD)) {
										slf->board.add({slf->y, slf->x -= 1}, slf->bK, slf->bD);
										slf->moved = true;
									}
									break;
								case RIGHT:
									slf->board.del({slf->y, slf->x}, slf->bK, slf->bD);
									if(slf->board.canMove({slf->y, slf->x + 1}, slf->bK, slf->bD)) {
										slf->board.add({slf->y, slf->x += 1}, slf->bK, slf->bD);
										slf->moved = true;
									}
									break;
								case UP:
									slf->board.del({slf->y, slf->x}, slf->bK, slf->bD);
									if(slf->board.canMove({slf->y, slf->x}, slf->bK, (slf->bD + 1) % 4)) {
										slf->bD = (slf->bD + 1) % 4;
										slf->board.add({slf->y, slf->x}, slf->bK, slf->bD);
										slf->moved = true;
									}
									break;
								case DOWN:
									slf->board.del({slf->y, slf->x}, slf->bK, slf->bD);
									while(slf->board.canMove({slf->y - 1, slf->x}, slf->bK, slf->bD))
										slf->y--;
									slf->board.add({slf->y, slf->x}, slf->bK, slf->bD);
									break;
						}
					}
				}
			}
		}
	);

	std::thread rcv(
		[]() {
			while(1) {
				if(GetTickCount() < prevT + 600 && GetTickCount() >= prevT2 + 200) {
					string s = server::recvTxt();
					if(s.size()) {
						if(s[0] == 'C') { // clear
							int lines = otr->board.clear();
							slf->board.addAttackLine(lines, s[1] - '0');
							otr->moved = slf->moved = true;
							
						}
						else { // drop
							int nums[4] = {}, i = 0;
							for(int j = 0; j < s.size(); j++) {
								if(s[j] == ' ')
									i++;
								else
									nums[i] = nums[i] * 10 + s[j] - '0';
							}
							otr->board.add({nums[0], nums[1]}, nums[2], nums[3]);
							otr->moved = true;
						}
					}
					Sleep(200);
				}
			}
		}
	);

	while(!P1_end & !P2_end) {
		if(GetTickCount() >= prevT + 600) {
			prevT = GetTickCount();
			slf->board.del({slf->y, slf->x}, slf->bK, slf->bD);
			if(slf->board.canMove({slf->y - 1, slf->x}, slf->bK, slf->bD)) {
				slf->board.add({slf->y -= 1, slf->x}, slf->bK, slf->bD);
			}
			else {
				slf->board.add({slf->y, slf->x}, slf->bK, slf->bD);
				char send[999];
				sprintf(send, "%d %d %d %d ", slf->y, slf->x, slf->bK, slf->bD);
				server::sendTxt(send);
				slf->createBlock();
			}
			slf->moved = true;
		}
		if(slf->moved) {
			slf->moved = false;
			int lines = slf->board.clear();
			if(lines) {
				int x = dis3(gen3);
				char send[999];
				sprintf(send, "C%d", x);
				server::sendTxt(send);
				otr->board.addAttackLine(lines, x);
			}
			tetris::showGameboard(0, 5, slf->board);
		}
		if(otr->moved) {
			otr->moved = false;
			tetris::showGameboard(30, 5, otr->board);
		}
	}

	

	return 0;
}
