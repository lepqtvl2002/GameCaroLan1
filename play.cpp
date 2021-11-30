#include "play.h"
//mouse
void mouse(int button, int state, int mouse_x, int mouse_y) {
	if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
		// Game Over
		switch (g.gameState) {
		case Game::GameState::GameOver: {
			// Play Again
			if (g.b.STT != 0) {
				// button Play Again
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					g.b.STT = g.round_of_play;
					countdown = 0;
					g.b.reset();
					g.gameState = Game::GameState::Running;
					//drawBackground(WIDTH, HEIGHT);
				}
				// button Quit
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y < 410 && mouse_y > 360) {
					exit(0);
				}
				// button Menu
				else {
					g.b.STT = 0;
					g.displayStartScreen();
					g.round_of_play = 0;
					g.score1 = 0;
					g.score2 = 0;
				}
			}
			// Start Game
			else {
				// button Start Game
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					g.b.reset();
					g.gameState = Game::GameState::PlayWith;
					g.playWith();
				}
				// button Music
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y < 410 && mouse_y > 360) {
					g.gameState = Game::GameState::History;
					g.playHistory();
				}
				// button About
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 460 && mouse_y < 510) {
					g.gameState = Game::GameState::About;
					g.aboutGame();
				}
				// button Guide
				else if (mouse_x > 140 && mouse_x < 250 && mouse_y > 260 && mouse_y < 310) {
					g.gameState = Game::GameState::Guide;
					g.guideGame();
				}
				// button Speaker
				else if (mouse_x > 440 && mouse_x < 480 && mouse_y > 20 && mouse_y < 120) {
					PlaySound(TEXT("poc"), NULL, SND_ASYNC);
					if (g.sound) g.sound = false;
					else g.sound = true;
				}
			}
		};
								break;
			// Running
		case Game::GameState::Running: {
				if (g.gameGenre == Game::GameGenre::PvP) {
					// doi tao do chuot -> tao do man hinh de in ra
					g.xx = mouse_x;
					g.yy = HEIGHT - mouse_y;
					// dua toa do man hinh -> tao do tam cac o vuong
					g.xx = g.Fix(g.xx);
					g.yy = g.Fix(g.yy);
					// tao do tam o vuong -> tao do tren ban co
					int i = g.xx / 25;
					int j = g.yy / 25;
					// neu nhan vao trong ban co
					if (g.b.checkArea(i, j)) {
						// phat ra tieng "poc"
						if (g.sound) PlaySound(TEXT("poc"), NULL, SND_ASYNC);
						if (g.b.check(i, j)) { // kiem tra da danh hay chua
							g.b.STT++;
							g._x = i * 25 + 12;
							g._y = j * 25 + 12;
							countdown = 0;
							if (g.b.STT > 0)
								if (g.b.STT % 2) g.b.input(i, j, 'O');
								else g.b.input(i, j, 'X');
							glutPostRedisplay();
							if (g.b.STT > 8)
								if (g.b.checkWin(i, j)) {
									g.round_of_play++;
									if (g.b.STT % 2) {
										g.score1++;
										g.writeToFile(g.round_of_play, "Player 1");
									}
									else {
										g.score2++;
										g.writeToFile(g.round_of_play, "Player 2");
									}
									Sleep(2000);
									if (g.sound) PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
									g.gameState = Game::GameState::GameOver;
								}
						}
						else {
							printf("Da dien roi!!!\n");
						}
					}
				}
				else {
					if (g.b.STT % 2 == 0) {
						// doi tao do chuot -> tao do man hinh de in ra
						g.xx = mouse_x;
						g.yy = HEIGHT - mouse_y;
						// dua toa do man hinh -> tao do tam cac o vuong
						g.xx = g.Fix(g.xx);
						g.yy = g.Fix(g.yy);
						// tao do tam o vuong -> tao do tren ban co
						int i = g.xx / 25;
						int j = g.yy / 25;
						// neu nhan vao trong ban co
						if (g.b.checkArea(i, j)) {
							// phat ra tieng "poc"
							if (g.sound) PlaySound(TEXT("poc"), NULL, SND_ASYNC);
							if (g.b.check(i, j)) { // kiem tra da danh hay chua
								g.b.STT++;
								g._x = i * 25 + 12;
								g._y = j * 25 + 12;
								if (g.b.STT > 0)
									g.b.input(i, j, 'O');
								g.b.drawChessman(i, j);
								glutPostRedisplay();

								if (g.b.STT > 8)
									if (g.b.checkWin(i, j)) {
										g.round_of_play++;
										{
											g.score1++;
											g.writeToFile(g.round_of_play, "Player P");
										}
										Sleep(2000);
										if (g.sound) PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
										g.gameState = Game::GameState::GameOver;
									}
							}
						}
					}

					if (g.b.STT % 2) {
						if (g.b.STT == g.round_of_play) {
							g.b.input(10, 10, 'X');
							g._x = 10 * 25 + 12;
							g._y = 10 * 25 + 12;
							g.b.STT++;
						}
						else {
							Point P = g.b.timKiemNuocDi();
							int i = P.getX();
							int j = P.getY();
							g._x = i * 25 + 12;
							g._y = j * 25 + 12;
							g.b.STT++;
							if (g.b.STT > 8)
								if (g.b.checkWin(i, j) && g.gameState == Game::GameState::Running) {
									g.round_of_play++;
									{
										g.score2++;
										g.writeToFile(g.round_of_play, "Computer");
									}
									Sleep(2000);
									if (g.sound) PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
									g.gameState = Game::GameState::GameOver;

								}
						}
					}
				}
			};
								break;
			// About
			case Game::GameState::About: {
				g.gameState = Game::GameState::GameOver;
			};
									   break;
			// Guide
			case Game::GameState::Guide: {
				g.gameState = Game::GameState::GameOver;
			};
									   break;
			// play history
			case Game::GameState::History: {
				g.gameState = Game::GameState::GameOver;
			};
										 break;
			// play with ...
			case Game::GameState::PlayWith: {
				// code here 
				if (mouse_x > 90 && mouse_x < 460 && mouse_y < 250 && mouse_y > 100) {
					g.gameGenre = Game::GameGenre::PvC;
					g.gameState = Game::GameState::Running;
				}
				else if (mouse_x > 90 && mouse_x < 460 && mouse_y < 450 && mouse_y > 300) {
					g.gameGenre = Game::GameGenre::PvP;
					g.gameState = Game::GameState::Running;
				}
				else {
					g.gameState = Game::GameState::GameOver;
				}
			};
										  break;
		}
	}
}

void mydisplay() {
	glViewport(0, 0, WIDTH, HEIGHT);

	if (g.gameState == Game::GameState::Running) g.drawBackground(WIDTH, HEIGHT);

	if (g.gameState == Game::GameState::GameOver) {
		g.displayStartScreen();
	}

	if (countdown == 150 && g.gameState == Game::GameState::Running && g.gameGenre == Game::GameGenre::PvP) {
		g.round_of_play++;
		if (g.b.STT % 2) {
			g.score1++;
			g.writeToFile(g.round_of_play, "Player 1");
		}
		else {
			g.score2++;
			g.writeToFile(g.round_of_play, "Player 2");
		}
		Sleep(2000);
		if (g.sound) PlaySound(TEXT("AmazingWorld"), NULL, SND_ASYNC);
		g.gameState = Game::GameState::GameOver;
	}

	glFlush();
}
void Timer(int value) {
	g.varTimer = (g.varTimer + 1) % 10;
	countdown++;
	//printf("%d\n", countdown);
	mydisplay();
	glutPostRedisplay();

	glutTimerFunc(INTERVAL, Timer, 0);

}
// tao do chuot
void passive(int x, int y) {
	g.X = x;
	g.Y = HEIGHT - y;
	g.X = g.Fix(g.X);
	g.Y = g.Fix(g.Y);
}