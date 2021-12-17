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
#define WIDTH 550
#define HEIGHT 600
#define SIZE 9
#define INTERVAL 30
static const int size_of_board = 20;
static int MAX = size_of_board * size_of_board;
static const char* filePath = "history.txt";
extern int countdown;
// draw blah blah
// Khai báo
void initGL();
// In kí tự ra màn hình
void vprint(int x, int y, void* font, const char* string, ...);
void vprint2(int x, int y, float size, const char* string, ...);
// Vẽ đường thẳng
void drawLine(int x1, int y1, int x2, int y2);
// Vẽ đường thẳng đậm
void drawTimeLine(int x, int y);
// Vẽ đường đếm thời gian
void lineCountdown(int x, int y);
// Vẽ đường nối 5 ô liền kề
void drawWinLine(int x1, int y1, int x2, int y2, int ch);
// Vẽ hình tròn
void draw8point(int xc, int yc, int x, int y);
void CircleBres(int xc, int yc, int R);
// Vẽ quân cờ O
void drawChessmanO(int x, int y, int R);
// Vẽ hai dấu chéo nhau
void drawX(int x, int y, int R);
// Vẽ quân cờ X
void drawChessmanX(int x, int y, int r);
// Vẽ khung dựa vào tọa độ 4 điểm
void drawBorder(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);