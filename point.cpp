#include "point.h"
Point::Point() {
	val = 0;
	x = 0; 
	y = 0;
}
Point::Point(int i, int j) {
	x = i;
	y = j;
	val = 0;
}
Point::Point(int i, int j, int v) {
	x = i;
	y = j;
	val = v;
}
Point::~Point() {

}
void Point::setX(int x) {
	this->x = x;
}
void Point::setY(int y) {
	this->y = y;
}
void Point::setVal(int val) {
	this->val = val;
}