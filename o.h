#pragma once
#include "point.h"
#include "draw.h"
class O :public Point {
public:
	O(int i, int j, int v) :Point(i, j, v) {

	}
	virtual ~O() {

	}
	virtual void drawChessman() {
		drawChessmanO(this->getX() * 25 + 12, this->getY() * 25 + 12, SIZE);
	}
};