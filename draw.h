#pragma once
#pragma warning(disable : 4996)
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <stdarg.h>
#include <time.h>
#include <Windows.h>
#include <mmsystem.h>
#include <GL/glut.h>
#include "board.h"
static Board b;
#define WIDTH 600
#define HEIGHT 600
#define SIZE 9
#define INTERVAL 30
static const int size_of_board = 20;

static const char* filePath = "history.txt";
// draw blah blah

void initGL();

void vprint(int x, int y, void* font, const char* string, ...);
void vprint2(int x, int y, float size, const char* string, ...);

void drawLine(int x1, int y1, int x2, int y2);

void drawTimeLine(int x, int y);
void drawWinLine(int x1, int y1, int x2, int y2, int ch);

void draw8point(int xc, int yc, int x, int y);
void CircleBres(int xc, int yc, int R);
void drawChessmanO(int x, int y, int R);

void drawX(int x, int y, int R);
void drawChessmanX(int x, int y, int r);

void drawBorder(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);