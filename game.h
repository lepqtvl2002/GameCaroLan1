#pragma once
#include "draw.h"
class Game {
public:
	enum class GameState {
		Running,	// Playing
		PlayWith,   // PvP or PvC
		Guide,      // guide for player
		History,    // history
		About,		// information about game
		Replay,		// show name winner
		GameOver    // game is over
	};

	enum class GameGenre {
		PvP,      // Play with orther player
		PvC,	  // Play with computer
	};
public:
	Board b;
	int xx, yy; // Tọa độ trên màn hình
	int X, Y; // Tọa độ chuột trên màn hình
	int _x, _y; // Tọa độ quân cờ vừa đi
	int varTimer;  // Biến thời gian
	int round_of_play; // Vòng chơi
	int score1, score2; // Điểm của 2 người chơi
	bool sound; // Âm thanh ( false là im lặng)
	GameState gameState; // Trạng thái trò chơi
	GameGenre gameGenre; // Chế độ chơi

public:
	Game();
	~Game();
	// Làm trò tọa độ
	int Fix(int xx);
	// Thực hiện trò chơi
	void drawBackground(int w, int h); // Vẽ bàn cờ, quân cờ, ...
	void displayStartScreen(); // Màn hình trò chơi lúc bắt đầu game hoặc lúc chơi lại
	void aboutGame(); // Thông tin về trò chơi
	void playHistory(); // Lịch sử 10 trận đấu gần nhất
	void guideGame(); // Hướng dẫn chơi
	void playWith(); // Lựa chọn chế độ chơi
	// Đọc ghi lịch sử đấu với file
	void writeToFile(int r, const char* string);
	void readFromFile();
};