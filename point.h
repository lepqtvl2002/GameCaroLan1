#pragma once
class Point {
	int x, y;
public:
	int val;
	Point();
	Point(int, int);
	Point(int, int, int);
	virtual ~Point();
	int getX() {
		return x;
	}
	int getY() {
		return y;
	}
	int getVal() {
		return val;
	}
	void setX(int);
	void setY(int);
	void setVal(int);
	virtual void DrawS(){}
};