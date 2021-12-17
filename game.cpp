#include "game.h"
Game::Game() {
	xx = 0;
	yy = 0;
	X = 0;
	Y = 0;
	_x = 0; 
	_y = 0;
	varTimer = 1;
	round_of_play = 0;
	score1 = 0;
	score2 = 0;
	sound = true;
	gameState = GameState::GameOver; // start with state GameOver
	gameGenre = GameGenre::PvP;
}
Game::~Game() {

}

//fix location
int Game::Fix(int x) {
	return (x - x % 25 + 12);
}

// draw boar
void Game::drawBackground(int w, int h)
{
	glViewport(0, 0, w, h);
	glColor3f(1.0f, 0.8f, 0.9f);
	glRectf(0, 0, w, h);
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, 0, w, h - 70);
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(25, 25, w - 25, h - 75);
	// ve bang
	glColor3f(0.8f, 0.8f, 0.8f);
	glViewport(0, 0, WIDTH, HEIGHT);
	for (int i = 1; i <= size_of_board + 1; i++) {
		drawLine(i * 25, 25, i * 25, (size_of_board + 1) * 25);
		drawLine(25, i * 25, (size_of_board + 1) * 25, i * 25);
	}
	// print score
	glColor3f(1.0f, 1.0f, 1.0f);
	vprint(224, 550, GLUT_BITMAP_TIMES_ROMAN_24, "%d      :      %d", score1, score2); // print score
	//
	if (gameGenre == GameGenre::PvP) {
		if (b.STT == round_of_play)
			if (b.STT % 2 == 0) {
				glColor3f(1.0f, 0.0f, 0.0f);
				vprint2(10, 350, 0.5, "PLAYER1'S TURN");
			}
			else {
				glColor3f(0.0f, 0.0f, 1.0f);
				vprint2(10, 350, 0.5, "PLAYER2'S TURN");
			}

		// print player's turn
		if (b.STT > 0) {
			if (b.STT % 2 == 1) {
				glColor3f(0.0f, 0.0f, 1.0f);
				vprint(370, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 2'S TURN");
				lineCountdown(375, 550);
				glColor3f(1.0f, 0.9f, 0.9f);
				vprint(25, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 1'S TURN");
				//drawTimeLine(25, 550);

			}
			else if (b.STT % 2 == 0) {
				glColor3f(1.0f, 0.0f, 0.0f);
				vprint(25, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 1'S TURN");
				lineCountdown(25, 550);
				glColor3f(0.9f, 0.9f, 1.0f);
				vprint(370, 555, GLUT_BITMAP_HELVETICA_18, "PLAYER 2'S TURN");
				//drawTimeLine(375, 550);

			}
		}
	}
	else {
		if ((b.STT == round_of_play))
			if ((b.STT % 2 == 1)) {
				glColor3f(0.0f, 0.0f, 1.0f);
				vprint2(50, 350, 0.3, "CLICK TO BOT START", round_of_play);
			}
			else {
				glColor3f(1.0f, 0.0f, 0.0f);
				vprint2(50, 350, 0.5, "YOUR TURN");
			}
		
		// print player's turn
		if (b.STT > 0) {
			/*if (b.STT % 2 == 1)*/ {
				glColor3f(0.0f, 0.0f, 1.0f);                
				vprint(375, 555, GLUT_BITMAP_HELVETICA_18, "COMPUTER");
				drawTimeLine(375, 550);
				glColor3f(1.0f, 0.0f, 0.0f);
				vprint(130, 555, GLUT_BITMAP_HELVETICA_18, "YOU");
				drawTimeLine(25, 550);

			}
		}
	}
	// print border mouse
	if (b.checkArea(X / 25, Y / 25)) {
		if (b.STT % 2) glColor3f(0.2f, 0.2f, 1.0f);
		else glColor3f(1.0f, 0.2f, 0.2f);		
		drawBorder(X - 12, Y + 12, X - 12, Y - 12, X + 12, Y - 12, X + 12, Y + 12);
	}
	// print quan co vua danh
	if (b.STT != round_of_play) {
		glColor3f(1.0f, 0.6f, 0.8f);
		glRectf(_x - 12, _y - 12, _x + 12, _y + 12);
	}
	// print chessman
	for (int i = 1; i <= size_of_board; i++)
		for (int j = 1; j <= size_of_board; j++)
			b.drawChessman(i, j);
	glFlush();
}
void Game::displayStartScreen()
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glRectf(0, HEIGHT, WIDTH, 0);

	glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);

	drawBorder(90, 350, 460, 350, 460, 500, 90, 500);
	
	drawBorder(140, 290, 250, 290, 250, 340, 140, 340);
	
	drawBorder(140, 190, 250, 190, 250, 240, 140, 240);

	if (b.STT != 0) {
		char ch;
		if (b.STT - round_of_play == MAX) ch = 'D';
		else if (b.STT % 2) ch = 'O';
		else ch = 'X';
		vprint2(100, 400, 0.5, "Play again");
		vprint2(150, 300, 0.3, "Menu");
		vprint2(150, 200, 0.3, "Quit");
		vprint2(200, 90, 0.2, "Tong so buoc da di: %d", b.STT - round_of_play);
		glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);
		if (ch == 'D') vprint2(300, 200, 0.6, "DRAW");
		else {
			if (ch == 'X') drawX(330, 240, 50);
			else CircleBres(330, 240, 50);
			if (varTimer > 4) vprint2(400, 200, 0.4, "WON!!!");
			else vprint2(400, 200, 0.2, "WON!!!");
		}
	}
	else {
		//glColor3f(1.0f, 1.0f, 1.0f);
		glColor3f((rand() % 250) / 255.0, (rand() % 250) / 255.0, (rand() % 250) / 255.0);
		vprint2(100, 400, 0.5, "Start game");
		vprint2(150, 300, 0.3, "Guide");
		vprint2(150, 200, 0.25, "History");
		vprint2(150, 100, 0.3, "About");
		drawBorder(140, 90, 250, 90, 250, 140, 140, 140);
		// draw speaker
		drawBorder(440, 560, 460, 560, 460, 520, 440, 520);	
		drawLine(460, 520, 480, 500);
		drawLine(460, 560, 480, 580);
		drawLine(480, 500, 480, 580);
		if (!sound) drawX(510, 540, 20);

		// draw +
		drawLine(310, 200, 510, 200);
		drawLine(410, 100, 410, 300);
		// draw x
		drawX(355, 255, 50);
		// draw o
		CircleBres(460, 150, 45);
	}

}
void Game::aboutGame() {
	glColor3f(0.6f, 0.8f, 0.85f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1, 1, 1);
	vprint2(200, 500, 0.2, "Game Caro");
	vprint2(50, 400, 0.2, "Nhom 7");
	vprint2(50, 350, 0.2, "Hoc sinh thuc hien:");
	vprint2(150, 300, 0.2, "Tran Duc Thang");
	vprint2(150, 250, 0.2, "Hoang Le Thanh Phuong");
	vprint2(50, 200, 0.2, "GVHD: Le Thi My Hanh");
}
void Game::guideGame() {
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	vprint2(20, 350, 0.2, "Place 5 pieces in a row, column ");
	vprint2(20, 300, 0.2, "or diagonally to win! :D");
	vprint2(20, 250, 0.2, "! Play with computer don't need time");
}
void Game::playHistory() {
	glColor3f(0.4f, 0.8f, 0.4f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	readFromFile();
}
void Game::playWith() {
	glColor3f(1.0f, 0.6f, 0.8f);
	glRectf(0, HEIGHT, WIDTH, 0);
	glColor3f(1.0f, 1.0f, 1.0f);
	drawBorder(90, 350, 460, 350, 460, 500, 90, 500);
	vprint2(100, 400, 0.5, "1 Player");
	drawBorder(90, 150, 460, 150, 460, 300, 90, 300);
	vprint2(100, 200, 0.5, "2 Player");
}

void Game::writeToFile(int r, const char* string) {
	FILE* fptr;
	fptr = fopen(filePath, "a");
	if (fptr == NULL) {
		printf("Error! opening file");
		exit(1);
	}
	time_t now = time(0);
	char* time_over_game = ctime(&now);
	char* list = (char*)malloc(sizeof(char)*50);
	sprintf(list, "*Round %i * %s / %s", r, string, time_over_game);
	fprintf(fptr, "%s", list);
	free(list);
	fseek(fptr, 0, SEEK_SET);
	fclose(fptr);
}
void Game::readFromFile() {
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
		vprint2(50, 50 + 35 * i, 0.13, list);
	}
	free(list);
	fclose(fptr);
}