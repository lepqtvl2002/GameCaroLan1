#pragma once
#include "point.h"

class Board {
	const int n = 20 + 1;
	Point* board[21][21];
public:
	Board();
	virtual ~Board();
	int STT = 0;
	int getSize();
	void reset();
	int operator () (int, int);
	int getVal(int, int);
	void input(int, int, int);
	void setLocation(int, int);
	int getX(int, int);
	int getY(int, int);
	bool check(int, int);
	bool checkArea(int, int);
	bool checkWin(int, int);
	bool checkWinRow(int, int);
	bool checkWinCol(int, int);
	bool checkWinFirstDiagonaly(int, int);
	bool checkWinSecDiagonaly(int, int);
	void DrawS(int, int);
};

