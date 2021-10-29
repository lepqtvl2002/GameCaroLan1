#include "game.h"

enum GameState {
	Running,	//no input is given
	Guide,      // guide for player
	About,		// information about game
	Replay,		// show name winner
	GameOver                // game is over
};

GameState gameState = GameOver; // start with state GameOver


//fix location
int Fix(int xx) {
	return (xx - xx % 25 + 12);
}
//mouse
void mouse(int button, int state, int mouse_x, int mouse_y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Game Over
		if ((gameState == GameOver)) {
			// Play Again
			if (b.STT != 0) {
				// button Play Again
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					b.STT = 0;
					b.reset();
					gameState = Running;
					drawBackground(WIDTH, HEIGHT);
				}
				// button Quit
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y < 410 && mouse_y > 360) {
					exit(0);
				}
				// button Menu
				else {
					b.STT = 0;
					displayStartScreen();
				}
			}
			// Start Game
			else {
				// button Start Game
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					b.reset();
					gameState = Running;
					drawBackground(WIDTH, HEIGHT);
				}
				// button Music
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y < 410 && mouse_y > 360) {
					PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
				}
				// button About
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 460 && mouse_y < 510) {
					gameState = About;
					aboutGame();
				}
				// button Guide
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 260 && mouse_y < 310) {
					gameState = Guide;
					guideGame();
				}
				// button ...
				else {
				}
			}
		}
		// Running
		else  if (gameState == Running) {
			// doi tao do chuot -> tao do man hinh de in ra
			xx = mouse_x;
			yy = HEIGHT - mouse_y;
			// dua toa do man hinh -> tao do tam cac o vuong
			xx = Fix(xx);
			yy = Fix(yy);
			// tao do tam o vuong -> tao do tren ban co
			int i = xx / 25;
			int j = yy / 25;
			// neu nhan vao trong ban co
			if (b.checkArea(i, j)) {
				// phat ra tieng "poc"
				PlaySound(TEXT("poc"), NULL, SND_ASYNC);
				if (b.check(i, j)) { // kiem tra da danh hay chua
					b.STT++;
					b.setLocation(i, j);
					if (b.STT > 0)
						if (b.STT % 2) b.input(i, j, 'O');
						else b.input(i, j, 'X');
					glutPostRedisplay();
				}
				else {
					printf("STT %d no co gia tri la %c, vi tri %d %d !!!\n", b.STT, b(i, j), i, j);
				}
			}
		}
		// About
		else if (gameState == About) {
			gameState = GameOver;
		}
		// Guide
		else if (gameState == Guide) {
			gameState = GameOver;
		}
	}
}


// draw boar
void drawBackground(int w, int h)
{
	glViewport(0, 0, w, h);
	glColor3f(1.0f, 0.8f, 0.9f);
	drawRectangular(0, 0, w, 0, w, h, 0, h);
	glColor3f(1.0f, 0.6f, 0.8f);
	drawRectangular(0, 0, w, 0, w, h - 70, 0, h - 70);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawRectangular(25, 25, w - 75, 25, w - 75, h - 75, 25, h - 75);
	// ve bang
	glColor3f(0.8f, 0.8f, 0.8f);
	glViewport(0, 0, WIDTH, HEIGHT);
	for (int i = 1; i <= size + 1; i++) {
		drawLine(i * 25, 25, i * 25, (size + 1) * 25);
		drawLine(25, i * 25, (size + 1) * 25, i * 25);
	}
	if (!b.STT) {
		glColor3f(1.0f, 0.0f, 0.0f);
		vprint2(10, 350, 0.5, "PLAYER1'S TURN");

	}
	if (b.STT > 0) {
		if (b.STT % 2 == 1) {
			glColor3f(0.0f, 0.0f, 1.0f);
			vprint(325, 555, GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 2'S TURN");
			drawTimeLine(375, 550);
			glColor3f(1.0f, 0.9f, 0.9f);
			vprint(25, 555, GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 1'S TURN");
			drawTimeLine(25, 550);

		}
		else if (b.STT % 2 == 0) {
			glColor3f(1.0f, 0.0f, 0.0f);
			vprint(25, 555, GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 1'S TURN");
			drawTimeLine(25, 550);
			glColor3f(0.9f, 0.9f, 1.0f);
			vprint(325, 555, GLUT_BITMAP_TIMES_ROMAN_24, "PLAYER 2'S TURN");
			drawTimeLine(375, 550);

		}
	}

	if (b.checkArea(X / 25, Y / 25)) {
		if (b.STT % 2) glColor3f(0.2f, 0.2f, 1.0f);
		else glColor3f(1.0f, 0.2f, 0.2f);		
		drawBorder(X - 12, Y + 12, X - 12, Y - 12, X + 12, Y - 12, X + 12, Y + 12);
	}

	for (int i = 1; i <= size; i++)
		for (int j = 1; j <= size; j++)
			b.DrawS(i, j);
	glFlush();
}
void displayStartScreen()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(0, HEIGHT, WIDTH, 0);

	glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);

	drawBorder(90, 350, 460, 350, 460, 500, 90, 500);
	
	drawBorder(140, 290, 250, 290, 250, 340, 140, 340);
	
	drawBorder(140, 190, 250, 190, 250, 240, 140, 240);

	if (b.STT != 0) {
		char ch;
		if (b.STT % 2) ch = 'O';
		else ch = 'X';
		vprint2(100, 400, 0.5, "Play again");
		vprint2(150, 300, 0.3, "Menu");
		vprint2(150, 200, 0.3, "Quit");
		vprint2(200, 90, 0.2, "Tong so buoc da di: %d", b.STT);
		glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);
		if (ch == 'X') vprint2(300, 180, 1, "%c", ch);
		else CircleBres(330, 240, 50);
		if (varTimer > 4) vprint2(400, 200, 0.4, "WON!!!");
		else vprint2(400, 200, 0.2, "WON!!!");
	}
	else {
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);
		vprint2(100, 400, 0.5, "Start game");
		vprint2(150, 300, 0.3, "Guide");
		vprint2(150, 200, 0.3, "Music");
		vprint2(150, 100, 0.3, "About");
		
		drawBorder(140, 90, 250, 90, 250, 140, 140, 140);

		// draw +
		drawLine(380, 200, 580, 200);
		drawLine(480, 100, 480, 300);
		// draw x
		drawX(425, 255, 50);
		// draw o
		CircleBres(530, 150, 45);
	}

}
void aboutGame() {
	glColor3f(0.6f, 0.8f, 1.0f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1, 1, 1);
	vprint2(200, 500, 0.2, "Game Caro");
	vprint2(100, 400, 0.2, "Nhom 7");
	vprint2(100, 350, 0.2, "Hoc sinh thuc hien:");
	vprint2(200, 300, 0.2, "Tran Duc Thang");
	vprint2(200, 250, 0.2, "Hoang Le Thanh Phuong");
	vprint2(100, 200, 0.2, "GVHD: Le Thi My Hanh");
}
void guideGame() {
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1, 1, 1);
	vprint2(100, 350, 0.2, "Place 5 pieces in a row, column ");
	vprint2(100, 300, 0.2, "or diagonally to win! :D");
	vprint2(100, 250, 0.2, "Is it easy?");
}
void mydisplay() {
	glViewport(0, 0, WIDTH, HEIGHT);

	if (gameState == Running) drawBackground(WIDTH, HEIGHT);

	if (b.STT > 8 && gameState == Running)
		if (b.checkArea(xx / 25, yy / 25) && b.checkWin(xx / 25, yy / 25)) {
			Sleep(2000);
			PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
			gameState = GameOver;
		}
	if (gameState == GameOver) {
		displayStartScreen();
	}

	glFlush();
}
void Timer(int value) {
	varTimer = (varTimer + 1) % 10;
	mydisplay();
	glutPostRedisplay();

	glutTimerFunc(INTERVAL, Timer, 0);

}
// tao do chuot
void passive(int x, int y) {
	X = x;
	Y = HEIGHT - y;
	X = Fix(X);
	Y = Fix(Y);
}

