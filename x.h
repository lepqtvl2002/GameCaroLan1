#pragma once
#include "point.h"
#include "draw.h"
class X :public Point {
public:
	X(int i, int j, int v) :Point(i, j, v) {

	}
	virtual ~X() {

	}
	virtual void drawChessman() {
		drawChessmanX(this->getX() * 25 + 12, this->getY() * 25 + 12, SIZE);
	}
};