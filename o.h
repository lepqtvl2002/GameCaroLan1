#pragma once
#include "point.h"
#include "draw.h"
class O :public Point {
public:
	O(int i, int j, int v) :Point(i, j, v) {

	}
	virtual ~O() {

	}
	virtual void DrawS() {
		drawChessmanO(this->getX(), this->getY(), SIZE);
	}
};