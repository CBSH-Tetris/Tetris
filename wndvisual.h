#pragma once

#include <windows.h>
#include <fcntl.h>
#include <io.h>

#define BLACK       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  0)
#define NAVY        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  1)
#define GREEN       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  2)
#define BLUEGREEN   SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  3)
#define ORANGE      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  4)
#define VIOLET      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  5)
#define GOLD        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  6)
#define ORIGINAL    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  7)
#define GRAY        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  8)
#define BLUE        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),  9)
#define YELLOWGREEN SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10)
#define SKYBLUE     SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 11)
#define RED         SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12)
#define PINK        SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 13)
#define YELLOW      SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 14)
#define WHITE       SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15)

#define COL_BLACK        0
#define COL_NAVY         1
#define COL_GREEN        2
#define COL_BLUEGREEN    3
#define COL_ORANGE       4
#define COL_VIOLET       5
#define COL_GOLD         6
#define COL_ORIGINAL     7
#define COL_GRAY         8
#define COL_BLUE         9
#define COL_YELLOWGREEN 10
#define COL_SKYBLUE     11
#define COL_RED         12
#define COL_PINK        13
#define COL_YELLOW      14
#define COL_WHITE       15

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

void txtColor(int txt = COL_ORIGINAL,int bck = COL_BLACK){
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (bck<<4)|(txt));
}

void init() {
	wndSize(40, 70);
	_setmode(_fileno(stdout), _O_U8TEXT);  
}