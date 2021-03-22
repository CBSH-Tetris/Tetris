#include "wndvisual.h"
#include "mouse.h"
#include <windows.h>
#include <cstdio>
#include <stdio.h>
#include <random>
#include <stdlib.h>

using namespace std;

std::random_device rd2;
std::mt19937 gen2(rd2());
std::uniform_int_distribution<int> dis2(1, 15);



void mainMenu() {
    gotoxy(0, 13);
    SKYBLUE;
    printf("                        +-------------------+                       \n");
    printf("                        |    C R E A T E    |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    WHITE;
    printf("                        +-------------------+                       \n");
    printf("                        |      J O I N      |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    BLUEGREEN;
    printf("                        +-------------------+                       \n");
    printf("                        |  C O N T R O L S  |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    NAVY;
    printf("                        +-------------------+                       \n");
    printf("                        |      Q U I T      |                       \n");
    printf("                        +-------------------+                       \n");
}

void tutorial() {
    gotoxy(0, 13);
    SKYBLUE;
    printf("                        +-------------------+                       \n");
    printf("                        |  C O N T R O L S  |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    WHITE;
    printf("        MOVE FALLING PIECE LEFT                         LEFT        \n");
    printf("        MOVE FALLING PIECE RIGHT                        RIGHT       \n");
    printf("        ROTATE CLOCKWISE                                X, UP       \n");
    printf("        ROTATE COUNTERCLOCKWISE                         Z           \n");
    printf("        HARD DROP                                       SPACE       \n");
    printf("        SOFT DROP                                       DOWN        \n");
    BLUEGREEN;
    printf("                        +-------------------+                       \n");
    printf("                        |      B A C K      |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
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


void join() {
    gotoxy(0, 13);
    SKYBLUE;
    printf("                        +-------------------+                       \n");
    printf("                        |    FIND ROOM ...  |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    WHITE;
    printf("        MOVE FALLING PIECE LEFT                         LEFT        \n");
    printf("        MOVE FALLING PIECE RIGHT                        RIGHT       \n");
    printf("        ROTATE CLOCKWISE                                X, UP       \n");
    printf("        ROTATE COUNTERCLOCKWISE                         Z           \n");
    printf("        HARD DROP                                       SPACE       \n");
    printf("        SOFT DROP                                       DOWN        \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
}

void create() {
    gotoxy(0, 13);
    SKYBLUE;
    printf("                        +-------------------+                       \n");
    printf("                        |   WAIT PLAYER ... |                       \n");
    printf("                        +-------------------+                       \n");
    printf("                                                                    \n");
    WHITE;
    printf("        MOVE FALLING PIECE LEFT                         LEFT        \n");
    printf("        MOVE FALLING PIECE RIGHT                        RIGHT       \n");
    printf("        ROTATE CLOCKWISE                                X, UP       \n");
    printf("        ROTATE COUNTERCLOCKWISE                         Z           \n");
    printf("        HARD DROP                                       SPACE       \n");
    printf("        SOFT DROP                                       DOWN        \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");
    printf("                                                                    \n");

}