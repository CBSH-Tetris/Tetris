#pragma once

#include<windows.h>
#include<fcntl.h>
#include<io.h>

void txtCol(int foreground=15,int background=0){
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

void init(){
	wndSize(25,50);
	_setmode(_fileno(stdout), _O_U8TEXT);  
}