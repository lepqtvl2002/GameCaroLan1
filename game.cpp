#include "game.h"

GameState gameState = GameState::GameOver; // start with state GameOver
GameGenre gameGenre = GameGenre::PvP; 

bool sound = true;

//fix location
int Fix(int xx) {
	return (xx - xx % 25 + 12);
}
//mouse
void mouse(int button, int state, int mouse_x, int mouse_y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Game Over
		if ((gameState == GameState::GameOver)) {
			// Play Again
			if (b.STT != 0) {
				// button Play Again
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					b.STT = round_of_play;
					b.reset();
					gameState = GameState::Running;
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
					round_of_play = 0;
					score1 = 0;
					score2 = 0;
				}
			}
			// Start Game
			else {
				// button Start Game
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					b.reset();
					gameState = GameState::PlayWith;
					playWith();
				}
				// button Music
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y < 410 && mouse_y > 360) {
					gameState = GameState::History;
					playHistory();
				}
				// button About
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 460 && mouse_y < 510) {
					gameState = GameState::About;
					aboutGame();
				}
				// button Guide
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 260 && mouse_y < 310) {
					gameState = GameState::Guide;
					guideGame();
				}
				// button Sound
				else if (mouse_x > 290 && mouse_x < 410 && mouse_y > 460 && mouse_y < 510) {
					PlaySound(TEXT("poc"), NULL, SND_ASYNC);
					if (sound) sound = false;
					else sound = true;
				}
			}
		}
		// Running
		else  if (gameState == GameState::Running) {
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
				if (sound) PlaySound(TEXT("poc"), NULL, SND_ASYNC);
				if (b.check(i, j)) { // kiem tra da danh hay chua
					b.STT++;
					b.setLocation(i, j);
					if (b.STT > 0)
						if (b.STT % 2) b.input(i, j, 'O');
						else b.input(i, j, 'X');
					glutPostRedisplay();
				}
				else {
					printf("Da dien roi!!!\n");
				}
			}
		}
		// About
		else if (gameState == GameState::About) {
			gameState = GameState::GameOver;
		}
		// Guide
		else if (gameState == GameState::Guide) {
			gameState = GameState::GameOver;
		}
		// play history
		else if (gameState == GameState::History) {
			gameState = GameState::GameOver;
		}
		// play with ...
		else if (gameState == GameState::PlayWith) {
			// code here 
			if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
				gameGenre = GameGenre::PvC;
				gameState = GameState::Running;
			}
			else if (mouse_x > 90 && mouse_x < 460 && mouse_y < 450 && mouse_y > 300) {
				gameGenre = GameGenre::PvP;
				gameState = GameState::Running;
			}
		}
	}
}


// draw boar
void drawBackground(int w, int h)
{
	glViewport(0, 0, w, h);
	glColor3f(1.0f, 0.8f, 0.9f);
	glRectf(0, 0, w, h);
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, 0, w, h - 70);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(25, 25, w - 75, h - 75);
	// ve bang
	glColor3f(0.8f, 0.8f, 0.8f);
	glViewport(0, 0, WIDTH, HEIGHT);
	for (int i = 1; i <= size_of_board + 1; i++) {
		drawLine(i * 25, 25, i * 25, (size_of_board + 1) * 25);
		drawLine(25, i * 25, (size_of_board + 1) * 25, i * 25);
	}
	// print score
	glColor3f(1.0f, 1.0f, 1.0f);
	vprint(224, 550, GLUT_BITMAP_TIMES_ROMAN_24, "%d      :      %d", score1, score2);
	//
	if (!b.STT) {
		glColor3f(1.0f, 0.0f, 0.0f);
		vprint2(10, 350, 0.5, "PLAYER1'S TURN");

	}
	// print player's turn
	if (b.STT > 0) {
		if (b.STT % 2 == 1) {
			glColor3f(0.0f, 0.0f, 1.0f);
			vprint(370, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 2'S TURN");
			drawTimeLine(375, 550);
			glColor3f(1.0f, 0.9f, 0.9f);
			vprint(25, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 1'S TURN");
			drawTimeLine(25, 550);

		}
		else if (b.STT % 2 == 0) {
			glColor3f(1.0f, 0.0f, 0.0f);
			vprint(25, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 1'S TURN");
			drawTimeLine(25, 550);
			glColor3f(0.9f, 0.9f, 1.0f);
			vprint(370, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 2'S TURN");
			drawTimeLine(375, 550);

		}
	}
	// print border mouse
	if (b.checkArea(X / 25, Y / 25)) {
		if (b.STT % 2) glColor3f(0.2f, 0.2f, 1.0f);
		else glColor3f(1.0f, 0.2f, 0.2f);		
		drawBorder(X - 12, Y + 12, X - 12, Y - 12, X + 12, Y - 12, X + 12, Y + 12);
	}
	// print chessman
	for (int i = 1; i <= size_of_board; i++)
		for (int j = 1; j <= size_of_board; j++)
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
		if (ch == 'X') drawX(330, 240, 50);
		else CircleBres(330, 240, 50);
		if (varTimer > 4) vprint2(400, 200, 0.4, "WON!!!");
		else vprint2(400, 200, 0.2, "WON!!!");
	}
	else {
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);
		vprint2(100, 400, 0.5, "Start game");
		vprint2(150, 300, 0.3, "Guide");
		vprint2(150, 200, 0.25, "History");
		vprint2(150, 100, 0.3, "About");
		drawBorder(140, 90, 250, 90, 250, 140, 140, 140);
		vprint2(300, 100, 0.3, "Sound");
		drawBorder(290, 90, 410, 90, 410, 140, 290, 140);	
		if (!sound) drawX(435, 115, 20);

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
	glColor3f(0.6f, 0.8f, 0.85f);
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
	glColor3f(1.0f, 1.0f, 1.0f);
	vprint2(100, 350, 0.2, "Place 5 pieces in a row, column ");
	vprint2(100, 300, 0.2, "or diagonally to win! :D");
	vprint2(100, 250, 0.2, "Is it easy?");
}
void playHistory() {
	glColor3f(0.4f, 0.8f, 0.4f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	readFromFile();
}
void playWith() {
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawBorder(90, 350, 460, 350, 460, 500, 90, 500);
	vprint2(100, 400, 0.5, "1 Player");
	drawBorder(90, 150, 460, 150, 460, 300, 90, 300);
	vprint2(100, 200, 0.5, "2 Player");
}
void mydisplay() {
	glViewport(0, 0, WIDTH, HEIGHT);

	if (gameState == GameState::Running) drawBackground(WIDTH, HEIGHT);

	if (b.STT > 8 && gameState == GameState::Running)
		if (b.checkArea(xx / 25, yy / 25) && b.checkWin(xx / 25, yy / 25)) {
			round_of_play++;
			if (b.STT % 2) {
				score1++;
				writeToFile(round_of_play, "Player1");
			}
			else {
				score2++;
				writeToFile(round_of_play, "Player2");
			}
			Sleep(2000);
			if (sound) PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
			gameState = GameState::GameOver;
		}
	if (gameState == GameState::GameOver) {
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
void writeToFile(int r, const char* string) {
	FILE* fptr;
	fptr = fopen(filePath, "a");
	if (fptr == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	time_t now = time(0);
	char* time_over_game = ctime(&now);
	char* list = (char*)malloc(sizeof(char)*50);
	sprintf(list, "Round %i / %s W / %s", r, string, time_over_game);
	fprintf(fptr, "%s", list);
	free(list);
	fseek(fptr, 0, SEEK_SET);
	fclose(fptr);
}
void readFromFile() {
	FILE* fptr;
	fptr = fopen(filePath, "r");
	if (fptr == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	char* list = (char*)malloc(sizeof(char) * 50);
	vprint2(100, 500, 0.2, "THE LAST 10 GAMES:");
	for (int i = 1; i <= 10; i++) {
		fseek(fptr, -48 * i, SEEK_END);
		fgets(list, 50, fptr);
		vprint2(50, 100 + 30 * i, 0.15, list);
	}
	free(list);
	fclose(fptr);
}

