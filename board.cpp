#include "board.h"
#include "o.h"
#include "x.h"
Board::Board() {
	for (int i = 1; i < n; i++)
		for (int j = 1; j < n; j++)
			board[i][j] = new Point(i, j);
}
Board::~Board() {
}
int Board::getSize() {
	return n - 1;
}
void Board::reset() {
	for (int i = 0; i < n; i++)
		for (int j = 0; j < n; j++) {
			this->board[i][j] = new Point(i, j, 0);
		}
}
int Board::operator () (int i, int j) {
	return this->board[i][j]->getVal();
}
int Board::getVal(int i, int j) {
	return this->board[i][j]->getVal();
}
void Board::input(int i, int j, int ch) {
	if (ch == 'O') board[i][j] = new O(i, j, ch);
	else if (ch == 'X') board[i][j] = new X(i, j, ch);
	else board[i][j] = new Point(i, j);
}
void Board::setLocation(int i, int j) {
	this->board[i][j]->setX(i);
	this->board[i][j]->setY(j);
}
int Board::getX(int i, int j) {
	return this->board[i][j]->getX();
}
int Board::getY(int i, int j) {
	return this->board[i][j]->getY();
}
bool Board::check(int i, int j) {
	if (this->getVal(i, j) == 0) return true;
	else return false;
}
bool Board::checkArea(int i, int j) {
	if (i < 1 || i >= this->n) return false;
	if (j < 1 || j >= this->n) return false;
	return true;
}
//

// checkWin
bool Board::checkWinCol(int x, int y) {
	int x1 = x * 25 + 12, x2 = x * 25 + 12, y1, y2;
	int j = y - 1, count = 1;
	int a = this->getVal(x, y);
	while (j > 0 && this->getVal(x, j) == a) {
		j--;
		count++;
	}
	y1 = 25 * (j + 1) + 12;
	j = y + 1;
	while (j <= size_of_board && this->getVal(x, j) == a) {
		j++;
		count++;
	}
	y2 = 25 * (j - 1) + 12;
	if (count >= 5) {
		drawWinLine(x1, y1, x2, y2, a);
		return true;
	}
	return false;
}
bool Board::checkWinRow(int x, int y) {
	int x1, x2, y1 = y * 25 + 12, y2 = y * 25 + 12;
	int i = x + 1, count = 1;
	int a = this->getVal(x, y);
	while (i <= size_of_board && this->getVal(i, y) == a) {
		i++;
		count++;
	}
	x1 = 25 * (i - 1) + 12;
	i = x - 1;
	while (i > 0 && this->getVal(i, y) == a) {
		i--;
		count++;
	}
	x2 = 25 * (i + 1) + 12;
	if (count >= 5) {
		drawWinLine(x1, y1, x2, y2, a);
		return true;
	}
	return false;
}
bool Board::checkWinFirstDiagonaly(int x, int y) {
	int x1, x2, y1, y2;
	int i = x - 1, j = y - 1, count = 1;
	int a = this->getVal(x, y);
	while (i > 0 && j >= 0 && this->getVal(i, j) == a) {
		i--;
		j--;
		count++;
	}
	x1 = 25 * (i + 1) + 12; y1 = 25 * (j + 1) + 12;
	i = x + 1;
	j = y + 1;
	while (i <= size_of_board && j < size_of_board && this->getVal(i, j) == a) {
		i++;
		j++;
		count++;
	}
	x2 = 25 * (i - 1) + 12; y2 = 25 * (j - 1) + 12;
	if (count >= 5) {
		drawWinLine(x1, y1, x2, y2, a);
		return true;
	}
	return false;
}
bool Board::checkWinSecDiagonaly(int x, int y) {
	int x1, x2, y1, y2;
	int i = x - 1, j = y + 1, count = 1;
	int a = this->getVal(x, y);
	while (i > 0 && j <= size_of_board && this->getVal(i, j) == a) {
		i--;
		j++;
		count++;
	}
	x1 = 25 * (i + 1) + 12; y1 = 25 * (j - 1) + 12;
	i = x + 1;
	j = y - 1;
	while (i <= size_of_board && j > 0 && this->getVal(i, j) == a) {
		i++;
		j--;
		count++;
	}
	x2 = 25 * (i - 1) + 12; y2 = 25 * (j + 1) + 12;
	if (count >= 5) {
		drawWinLine(x1, y1, x2, y2, a);
		return true;
	}
	return false;
}

bool Board::checkWin(int i, int j) {
	if (checkWinCol(i, j)) return true;
	if (checkWinRow(i, j)) return true;
	if (checkWinFirstDiagonaly(i, j)) return true;
	if (checkWinSecDiagonaly(i, j)) return true;
	return false;
}

void Board::drawChessman(int i, int j) {
	this->board[i][j]->drawChessman();
}