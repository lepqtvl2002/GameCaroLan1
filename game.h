#pragma once
#include "draw.h"
#include "board.h"
static int xx, yy;
static int X, Y;
static int varTimer = 1;
static Board b;
//
int Fix(int xx);
//
void mouse(int button, int state, int mouse_x, int mouse_y);
//
void drawBackground(int w, int h);
void displayStartScreen();
void aboutGame();
void guideGame();
//
void mydisplay();
void Timer(int value);
//
void passive(int x, int y);

