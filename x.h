#pragma once
#include "point.h"
#include "draw.h"
class X :public Point {
public:
	X(int i, int j, int v) :Point(i, j, v) {

	}
	virtual ~X() {

	}
	virtual void DrawS() {
		drawChessmanX(this->getX(), this->getY(), SIZE);
	}
};