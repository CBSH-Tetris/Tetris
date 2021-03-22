#pragma once

#include <windows.h>
#include <fcntl.h>
#include <io.h>

#define BLACK SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 0)
#define NAVY SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 1)
#define GREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 2)
#define BLUEGREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 3)
#define ORANGE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 4)
#define VIOLET SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 5)
#define GOLD SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6)
#define ORIGINAL SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 7)
#define GRAY SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 8)
#define BLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 9)
#define YELLOWGREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define SKYBLUE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)
#define RED SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define PINK SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13)
#define YELLOW SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define WHITE SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

enum {
	E = -1, // Empty
    L,
    J,
    O,
    S,
    Z,
    I,
    T,
	G // Garbage
};

void gotoxy(int x, int y) {
	COORD pos = {x, y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void wndSize(int xs, int ys) {
	char cmd[999];
	sprintf(cmd, "mode con: cols=%d lines=%d", ys, xs);
	system(cmd);
	DWORD dwmode;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwmode) | ENABLE_MOUSE_INPUT);
}


void init() {
	wndSize(32, 70);
	_setmode(_fileno(stdout), _O_U8TEXT);  
}