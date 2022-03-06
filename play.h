#pragma once
#include "game.h"
extern Game g;
// Thực hiện tương tác với chuột (khi nhấn chuột trái)
void mouse(int button, int state, int mouse_x, int mouse_y);
// Tương tác với màn hình
void myDisplay();
// Thực hiện hoạt ảnh
void ReShape(int, int);
void Timer(int value);
// Lấy tọa độ chuột (lúc di chuyển)
void passive(int x, int y);