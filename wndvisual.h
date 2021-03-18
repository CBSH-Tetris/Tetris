#pragma once

#include<windows.h>

void txtCol(int foreground,int background){
	int color=foreground+background*16;
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE),color);
}

void gotoxy(int x,int y){
	COORD pos={x,y};
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos); 
}

void wndSize(int xs,int ys){
	char cmd[999];
	sprintf(cmd,"mode con: cols=%d lines=%d",ys,xs);
	system(cmd);
}
