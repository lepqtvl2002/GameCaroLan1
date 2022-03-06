#include "play.h"
Game g;
int countdown;
int main(int argc, char** argv) {
	glutInit(&argc, argv);
	int mode = GLUT_SINGLE | GLUT_RGB;
	glutInitDisplayMode(mode);
	glutInitWindowSize(WIDTH, HEIGHT);
	int POS_X = (glutGet(GLUT_SCREEN_WIDTH) - WIDTH) / 2;
	int POS_Y = (glutGet(GLUT_SCREEN_HEIGHT) - HEIGHT) / 2;
	glutInitWindowPosition(POS_X, POS_Y);
	glutCreateWindow("Game Caro");

	PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
	initGL();
	
	glutMouseFunc(mouse);
	glutReshapeFunc(ReShape);
	glutDisplayFunc(myDisplay);
	glutPassiveMotionFunc(passive);
	glutTimerFunc(0, Timer, 0);
	glutMainLoop();	
}