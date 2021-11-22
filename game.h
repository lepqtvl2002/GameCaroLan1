#pragma once
//#include "draw.h"
#include "bot.h"
extern Board b;
enum class GameState {
	Running,	// Playing
	PlayWith,   // PvP or PvC
	Guide,      // guide for player
	History,    // history
	About,		// information about game
	Replay,		// show name winner
	GameOver                // game is over
};

enum class GameGenre {
	PvP,      // Play with orther player
	PvC,	  // Play with computer
};

static int xx, yy;
static int X, Y;
static int _x, _y;
static int varTimer = 1;

static int round_of_play = 0;
static int score1 = 0, score2 = 0;
//
int Fix(int xx);
//
void mouse(int button, int state, int mouse_x, int mouse_y);
//
void drawBackground(int w, int h);
void displayStartScreen();
void aboutGame();
void playHistory();
void guideGame();
void playWith();
//
void mydisplay();
void Timer(int value);
//
void passive(int x, int y);
void writeToFile(int r, const char* string);
void readFromFile();
void lineCountdown(int x, int y); 