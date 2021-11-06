#include "draw.h"
//init GL
void initGL()
{
	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
	gluOrtho2D(0, WIDTH, 0, HEIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glViewport(0, 0, WIDTH, HEIGHT);
	glMatrixMode(GL_MODELVIEW);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_LINE_SMOOTH);
	glEnable(GL_POINT_SMOOTH);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}
// print string in screen
void vprint(int x, int y, void* font, const char* string, ...)
{
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);

	glRasterPos2f(x, y);
	int len = (int)strlen(str);
	for (int i = 0; i < len; i++)
	{
		glutBitmapCharacter(font, str[i]);
	}
}
void vprint2(int x, int y, float size, const char* string, ...) {
	va_list ap;
	va_start(ap, string);
	char str[1024];
	vsprintf_s(str, string, ap);
	va_end(ap);
	
	glPushMatrix();
	glTranslatef(x, y, 0);
	glScalef(size, size, 1);

	int len = (int)strlen(str);
	for (int i = 0; i < len; i++)
	{
		glutStrokeCharacter(GLUT_STROKE_ROMAN, str[i]);
	}
	glPopMatrix();
}
// draw line 
void drawLine(int x1, int y1, int x2, int y2) {
	glBegin(GL_LINES);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glEnd();
}
// draw time line
void drawTimeLine(int x, int y) {
	for (int i = 1; i < 10; i++) {
		drawLine(x, y - i, x + 150, y - i);
	}
}
// draw win line
void drawWinLine(int x1, int y1, int x2, int y2, int ch) {
	if (x1 == x2) {
		for (int k = y1; k <= y2; k += 25) {
			glColor3f(1.0f, 0.0f, 1.0f);
			glRectf(x1 - 12, k + 12, x1 + 12, k - 12);
			if (ch == 'O') drawChessmanO(x1, k, SIZE);
			else drawChessmanX(x1, k, SIZE);
		}
	}
	else if (y1 == y2) {
		for (int k = x2; k <= x1; k += 25) {
			glColor3f(1.0f, 0.0f, 1.0f);
			glRectf(k - 12, y1 + 12, k + 12, y1 - 12);
			if (ch == 'O') drawChessmanO(k, y1, SIZE);
			else drawChessmanX(k, y1, SIZE);
		}

	}
	else if (y1 > y2) {
		for (int k = 0; y1 - k * 25 >= y2; k++) {
			int x = x1 + k * 25;
			int y = y1 - k * 25;
			glColor3f(1.0f, 0.0f, 1.0f);
			glRectf(x - 12, y + 12, x + 12, y - 12);
			if (ch == 'O') drawChessmanO(x, y, SIZE);
			else drawChessmanX(x, y, SIZE);
		}
	
	}
	else {
		for (int k = 0; y2 - k * 25 >= y1; k++) {
			int x = x1 + k * 25;
			int y = y1 + k * 25;
			glColor3f(1.0f, 0.0f, 1.0f);
			glRectf(x - 12, y + 12, x + 12, y - 12);
			if (ch == 'O') drawChessmanO(x, y, SIZE);
			else drawChessmanX(x, y, SIZE);
		}

	}
	glFlush();
}
//draw o
void draw8point(int xc, int yc, int x, int y)
{
	glViewport(0, 0, WIDTH, HEIGHT);
	//glColor3f(1.0f, 0.0f, 0.0f);
	glBegin(GL_POINTS);
	glVertex2i(xc + x, yc + y);
	glVertex2i(xc + y, yc + x);
	glVertex2i(xc + y, yc - x);
	glVertex2i(xc + x, yc - y);
	glVertex2i(xc - x, yc - y);
	glVertex2i(xc - y, yc - x);
	glVertex2i(xc - y, yc + x);
	glVertex2i(xc - x, yc + y);
	glEnd();
}
void CircleBres(int xc, int yc, int R)
{
	int p;
	int y = R;
	int x = 0;
	p = 3 - 2 * R;
	glViewport(0, 0, WIDTH, HEIGHT);
	draw8point(xc, yc, x, y);
	while (x < y)
	{
		if (p < 0)
			p += 4 * x + 6;
		else
		{
			p += 4 * (x - y) + 10;
			y--;
		}
		x++;
		draw8point(xc, yc, x, y);
	}
}
void drawChessmanO(int x, int y, int R) {
	glColor3f(1.0f, 0.0f, 0.0f);
	for (int i = 0; i < 3; i++) {
		R--;
		CircleBres(x, y, R);
	}
}
// draw X
void drawX(int x, int y, int r) {
	drawLine(x - r, y + r, x + r, y - r);
	drawLine(x - r, y - r, x + r, y + r);
}
void drawChessmanX(int x, int y, int R) {
	glViewport(0, 0, WIDTH, HEIGHT);
	glColor3f(0, 0, 1);
	for (int i = 0; i < 3; i++) {
		x--; R--;
		drawX(x, y, R);
	}
	//glFlush();
}
void drawBorder(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) {
	glBegin(GL_LINE_LOOP);
	glVertex2i(x1, y1);
	glVertex2i(x2, y2);
	glVertex2i(x3, y3);
	glVertex2i(x4, y4);
	glEnd();
}
