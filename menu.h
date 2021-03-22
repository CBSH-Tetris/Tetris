#include "wndvisual.h"
#include "mouse.h"
#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <stdlib.h>



void mainMenu() {
    system("cls");
    DWORD dwmode;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwmode) | ENABLE_MOUSE_INPUT);

    printf("\n");
    printf("                         @@@@    @@@@    @@@@    @   @\n");
    printf("                       @        @   @   @       @   @\n");
    printf("                      @        @@@@     @@@    @@@@@\n");
    printf("                     @        @   @       @   @   @\n");
    printf("                     @@@@    @@@@     @@@@   @   @\n\n");
    printf("                @@@@@   @@@@@   @@@@@    @@@@@   @    @@@@  \n");
    printf("                 @     @         @      @   @   @    @      \n");
    printf("                @     @@@@@     @      @@@@    @     @@@   \n");
    printf("               @     @         @      @  @    @        @   \n");
    printf("              @     @@@@@     @      @   @   @     @@@@    \n\n");
    printf("                        +-------------------+                       \n");
    printf("                        |    C R E A T E    |                       \n");
    printf("                        +-------------------+                       \n\n\n");
    printf("                        +-------------------+                       \n");
    printf("                        |      J O I N      |                       \n");
    printf("                        +-------------------+                       \n\n\n");
    printf("                        +-------------------+                       \n");
    printf("                        |  C O N T R O L S  |                       \n");
    printf("                        +-------------------+                       \n\n\n");
    printf("                        +-------------------+                       \n");
    printf("                        |      Q U I T      |                       \n");
    printf("                        +-------------------+                       \n");
}

void tutorial() {
    system("cls");
    DWORD dwmode;
	SetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), GetConsoleMode(GetStdHandle(STD_INPUT_HANDLE), &dwmode) | ENABLE_MOUSE_INPUT);

    printf("\n");
    printf("                         @@@@    @@@@    @@@@    @   @\n");
    printf("                       @        @   @   @       @   @\n");
    printf("                      @        @@@@     @@@    @@@@@\n");
    printf("                     @        @   @       @   @   @\n");
    printf("                     @@@@    @@@@     @@@@   @   @\n\n");
    printf("                @@@@@   @@@@@   @@@@@    @@@@@   @    @@@@  \n");
    printf("                 @     @         @      @   @   @    @      \n");
    printf("                @     @@@@@     @      @@@@    @     @@@   \n");
    printf("               @     @         @      @  @    @        @   \n");
    printf("              @     @@@@@     @      @   @   @     @@@@    \n\n");
    printf("                        +-------------------+                       \n");
    printf("                        |  C O N T R O L S  |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    printf("        MOVE FALLING PIECE LEFT                         LEFT        \n");
    printf("        MOVE FALLING PIECE RIGHT                        RIGHT       \n");
    printf("        ROTATE CLOCKWISE                                X, UP       \n");
    printf("        ROTATE COUNTERCLOCKWISE                         Z           \n");
    printf("        HARD DROP                                       SPACE       \n");
    printf("        SOFT DROP                                       DOWN        \n");
    printf("                        +-------------------+                       \n");
    printf("                        |      B A C K      |                       \n");
    printf("                        +-------------------+                       \n\n\n\n\n\n");
    Sleep(100);
    int xx, yy, lr;
    while(1) {
		GetMouseState(&xx, &yy, &lr);
        if(23 <= yy && yy <= 25 && 24 <= xx && xx <= 44) { // BACK
			break;
		}
    }
    return;
}