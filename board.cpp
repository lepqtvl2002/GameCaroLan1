#include "board.h"
#include "o.h"
#include "x.h"
// Mảng phòng thủ cho máy
const static long Defend_Score[6] = { 0, 8, 512, 32768, 2097152, 134217728 };
// Mảng tấn công cho máy
const static long Attack_Score[6] = { 0, 64, 4096, 262144, 16777216, 1073741824 };
Board::Board() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			board[i][j] = new Point(i, j);
}
Board::~Board() {
	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++)
			delete board[i][j];
}
int Board::getSize() {
	return n;
}
void Board::reset() {

	for (int i = 1; i <= n; i++)
		for (int j = 1; j <= n; j++) {
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
	if (i < 1 || i > this->n) return false;
	if (j < 1 || j > this->n) return false;
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

// Tìm kiếm nước đi cho máy
long Board::SoDiemTanCong_DuyetDoc(long Dong, long Cot) {
	{
		long iScoreTempDoc = 0;
		long iScoreAttack = 0;
		int iSoQuanTa = 0;
		int iSoQuanDich = 0;
		int iSoQuanTa2 = 0;
		int iSoQuanDich2 = 0;
		for (int iDem = 1; iDem < 6 && Dong + iDem <= size_of_board; iDem++)
		{
			if (this->getVal(Dong + iDem, Cot) == 'X')
				iSoQuanTa++;
			if (this->getVal(Dong + iDem, Cot) == 'O')
			{
				iSoQuanDich++;
				break;
			}
			if (this->getVal(Dong + iDem, Cot) == 0)
			{
				for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 <= size_of_board; iDem2++)
				{
					if (this->getVal(Dong + iDem2, Cot) == 'X')
						iSoQuanTa2++;
					if (this->getVal(Dong + iDem2, Cot) == 'O')
					{
						iSoQuanDich2++;
						break;
					}
					if (this->getVal(Dong + iDem2, Cot) == 0)
						break;
				}
				break;
			}

		}
		//iScoreAttack += Attack_Score[iSoQuanTa];
		//iSoQuanTa = 0;

		for (int iDem = 1; iDem < 6 && Dong - iDem > 0; iDem++)
		{
			if (this->getVal(Dong - iDem, Cot) == 'X')
				iSoQuanTa++;
			if (this->getVal(Dong - iDem, Cot) == 'O')
			{
				iSoQuanDich++;
				break;
			}
			if (this->getVal(Dong - iDem, Cot) == 0)
			{
				for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 > 0; iDem2++)
				{
					if (this->getVal(Dong - iDem2, Cot) == 'X')
						iSoQuanTa2++;
					if (this->getVal(Dong - iDem2, Cot) == 'O')
					{
						iSoQuanDich2++;
						break;
					}
					if (this->getVal(Dong - iDem2, Cot) == 0)
					{
						break;
					}
				}
				break;
			}
		}

		if (iSoQuanDich == 2)
			return 0;
		if (iSoQuanDich == 0)
			iScoreTempDoc += Attack_Score[iSoQuanTa] * 2;
		else
			iScoreTempDoc += Attack_Score[iSoQuanTa];
		if (iSoQuanDich2 == 0)
			iScoreTempDoc += Attack_Score[iSoQuanTa2] * 2;
		else
			iScoreTempDoc += Attack_Score[iSoQuanTa2];

		if (iSoQuanTa >= iSoQuanTa2)
			iScoreTempDoc -= 1;
		else
			iScoreTempDoc -= 2;
		if (iSoQuanTa == 4)
			iScoreTempDoc *= 2;
		if (iSoQuanTa == 0)
			iScoreTempDoc += Defend_Score[iSoQuanDich] * 2;
		else
			iScoreTempDoc += Defend_Score[iSoQuanDich];
		if (iSoQuanTa2 == 0)
			iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
		else
			iScoreTempDoc += Defend_Score[iSoQuanDich2];
		return iScoreTempDoc;
	}

}
long Board::SoDiemTanCong_DuyetNgang(long Dong, long Cot) {
	long iScoreTempNgang = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong , Cot + iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong , Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong , Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong , Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong , Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong , Cot + iDem2) == 0)
					break;
			}
			break;
		}
	}

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0; iDem++)
	{
		if (this->getVal(Dong , Cot - iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong , Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong , Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong , Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong , Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong , Cot - iDem2) == 0)
					break;
			}
			break;
		}
	}
	if (iSoQuanDich == 2)
		return 0;
	if (iSoQuanDich == 0)
		iScoreTempNgang += Attack_Score[iSoQuanTa] * 2;
	else
		iScoreTempNgang += Attack_Score[iSoQuanTa];
	if (iSoQuanDich2 == 0)
		iScoreTempNgang += Attack_Score[iSoQuanTa2] * 2;
	else
		iScoreTempNgang += Attack_Score[iSoQuanTa2];

	if (iSoQuanTa >= iSoQuanTa2)
		iScoreTempNgang -= 1;
	else
		iScoreTempNgang -= 2;
	if (iSoQuanTa == 4)
		iScoreTempNgang *= 2;
	if (iSoQuanTa == 0)
		iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempNgang += Defend_Score[iSoQuanDich];
	if (iSoQuanTa2 == 0)
		iScoreTempNgang += Defend_Score[iSoQuanDich2] * 2;
	else
		iScoreTempNgang += Defend_Score[iSoQuanDich2];
	return iScoreTempNgang;
}
long Board::SoDiemTanCong_DuyetCheo1(long Dong, long Cot) {
	long iScoreTempCheoNguoc = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong + iDem, Cot + iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong + iDem, Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong + iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 0)
				{
					break;
				}
			}
			break;
		}
	}
	//iScoreAttack += Attack_Score[iSoQuanTa];
	//iSoQuanTa = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong - iDem > 0; iDem++)
	{
		if (this->getVal(Dong - iDem, Cot - iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong - iDem, Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong - iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong - iDem2, Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong - iDem2, Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong - iDem2, Cot - iDem2) == 0)
					break;
			}
			break;
		}
	}
	if (iSoQuanDich == 2)
		return 0;
	if (iSoQuanDich == 0)
		iScoreTempCheoNguoc += Attack_Score[iSoQuanTa] * 2;
	else
		iScoreTempCheoNguoc += Attack_Score[iSoQuanTa];
	if (iSoQuanDich2 == 0)
		iScoreTempCheoNguoc += Attack_Score[iSoQuanTa2] * 2;
	else
		iScoreTempCheoNguoc += Attack_Score[iSoQuanTa2];

	if (iSoQuanTa >= iSoQuanTa2)
		iScoreTempCheoNguoc -= 1;
	else
		iScoreTempCheoNguoc -= 2;
	if (iSoQuanTa == 4)
		iScoreTempCheoNguoc *= 2;
	if (iSoQuanTa == 0)
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich];
	if (iSoQuanTa2 == 0)
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich2] * 2;
	else
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich2];
	return iScoreTempCheoNguoc;
}
long Board::SoDiemTanCong_DuyetCheo2(long Dong, long Cot) {
	long iScoreTempCheoXuoi = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong + iDem, Cot - iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong + iDem, Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong + iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 0)
					break;
			}
			break;
		}
	}
	//iScoreAttack += Attack_Score[iSoQuanTa];
	//iSoQuanTa = 0;

	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong - iDem > 0; iDem++)
	{
		if (this->getVal(Dong - iDem, Cot + iDem) == 'X')
			iSoQuanTa++;
		if (this->getVal(Dong - iDem, Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (this->getVal(Dong - iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 0)
					break;
			}
			break;
		}
	}
	if (iSoQuanDich == 2)
		return 0;
	if (iSoQuanDich == 0)
		iScoreTempCheoXuoi += Attack_Score[iSoQuanTa] * 2;
	else
		iScoreTempCheoXuoi += Attack_Score[iSoQuanTa];
	if (iSoQuanDich2 == 0)
		iScoreTempCheoXuoi += Attack_Score[iSoQuanTa2] * 2;
	else
		iScoreTempCheoXuoi += Attack_Score[iSoQuanTa2];

	if (iSoQuanTa >= iSoQuanTa2)
		iScoreTempCheoXuoi -= 1;
	else
		iScoreTempCheoXuoi -= 2;
	if (iSoQuanTa == 4)
		iScoreTempCheoXuoi *= 2;
	if (iSoQuanTa == 0)
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich];
	if (iSoQuanTa2 == 0)
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich2] * 2;
	else
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich2];
	return iScoreTempCheoXuoi;
}
long Board::SoDiemPhongThu_DuyetDoc(long Dong, long Cot) {
	long iScoreTempDoc = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Dong + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong + iDem, Cot) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong + iDem, Cot) == 'O')
			iSoQuanDich++;
		if (this->getVal(Dong + iDem, Cot) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong + iDem2, Cot) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong + iDem2, Cot) == 'O')
					iSoQuanDich2++;
				if (this->getVal(Dong + iDem2, Cot) == 0)
					break;
			}
			break;
		}
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Dong - iDem > 0; iDem++)
	{
		if (this->getVal(Dong - iDem, Cot) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong - iDem, Cot) == 'O')
			iSoQuanDich++;
		if (this->getVal(Dong - iDem, Cot) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong - iDem2, Cot) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong - iDem2, Cot) == 'O')
					iSoQuanDich2++;
				if (this->getVal(Dong - iDem2, Cot) == 0)
					break;
			}
			break;
		}
	}


	if (iSoQuanTa == 2)
		return 0;
	if (iSoQuanTa == 0)
		iScoreTempDoc += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempDoc += Defend_Score[iSoQuanDich];
	/*
	if (iSoQuanTa == 0)
	iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
	else
	iScoreTempDoc += Defend_Score[iSoQuanDich2];
	*/
	if (iSoQuanDich >= iSoQuanDich2)
		iScoreTempDoc -= 1;
	else
		iScoreTempDoc -= 2;
	if (iSoQuanDich == 4)
		iScoreTempDoc *= 2;
	return iScoreTempDoc;
}

long Board::SoDiemPhongThu_DuyetNgang(long Dong, long Cot) {
	long iScoreTempNgang = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong , Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong , Cot + iDem) == 'O')
			iSoQuanDich++;
		if (this->getVal(Dong , Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong , Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong , Cot + iDem2) == 'O')
					iSoQuanDich2++;
				if (this->getVal(Dong , Cot + iDem2) == 0)
					break;
			}
			break;
		}
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0; iDem++)
	{
		if (this->getVal(Dong , Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong , Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong , Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong , Cot - iDem2) == 0)
					break;
				if (this->getVal(Dong , Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (this->getVal(Dong , Cot - iDem) == 'O')
			iSoQuanDich++;
	}

	if (iSoQuanTa == 2)
		return 0;
	if (iSoQuanTa == 0)
		iScoreTempNgang += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempNgang += Defend_Score[iSoQuanDich];
	/*
	if (iSoQuanTa == 0)
	iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
	else
	iScoreTempDoc += Defend_Score[iSoQuanDich2];
	*/
	if (iSoQuanDich >= iSoQuanDich2)
		iScoreTempNgang -= 1;
	else
		iScoreTempNgang -= 2;
	if (iSoQuanDich == 4)
		iScoreTempNgang *= 2;
	return iScoreTempNgang;
}
long Board::SoDiemPhongThu_DuyetCheo1(long Dong, long Cot) {

	long iScoreTempCheoNguoc = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong + iDem, Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong + iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 0)
					break;
				if (this->getVal(Dong + iDem2, Cot + iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (this->getVal(Dong + iDem, Cot + iDem) == 'O')
			iSoQuanDich++;
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong - iDem > 0; iDem++)
	{
		if (this->getVal(Dong - iDem, Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}

		if (this->getVal(Dong - iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong - iDem2, Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}

				if (this->getVal(Dong - iDem2, Cot - iDem2) == 0)
					break;
				if (this->getVal(Dong - iDem2, Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (this->getVal(Dong - iDem, Cot - iDem) == 'O')
			iSoQuanDich++;
	}
	if (iSoQuanTa == 2)
		return 0;
	if (iSoQuanTa == 0)
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempCheoNguoc += Defend_Score[iSoQuanDich];
	/*
	if (iSoQuanTa == 0)
	iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
	else
	iScoreTempDoc += Defend_Score[iSoQuanDich2];
	*/
	if (iSoQuanDich >= iSoQuanDich2)
		iScoreTempCheoNguoc -= 1;
	else
		iScoreTempCheoNguoc -= 2;
	if (iSoQuanDich == 4)
		iScoreTempCheoNguoc *= 2;
	return iScoreTempCheoNguoc;
}

long Board::SoDiemPhongThu_DuyetCheo2(long Dong, long Cot) {
	long iScoreTempCheoXuoi = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong + iDem <= size_of_board; iDem++)
	{
		if (this->getVal(Dong + iDem, Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong + iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 0)
					break;
				if (this->getVal(Dong + iDem2, Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (this->getVal(Dong + iDem, Cot - iDem) == 'O')
			iSoQuanDich++;
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong - iDem > 0; iDem++)
	{
		if (this->getVal(Dong - iDem, Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (this->getVal(Dong - iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong - iDem2 > 0; iDem2++)
			{
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 0)
					break;
				if (this->getVal(Dong - iDem2, Cot + iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (this->getVal(Dong - iDem, Cot + iDem) == 'O')
			iSoQuanDich++;
	}


	if (iSoQuanTa == 2)
		return 0;
	if (iSoQuanTa == 0)
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich] * 2;
	else
		iScoreTempCheoXuoi += Defend_Score[iSoQuanDich];
	/*
	if (iSoQuanTa == 0)
	iScoreTempDoc += Defend_Score[iSoQuanDich2] * 2;
	else
	iScoreTempDoc += Defend_Score[iSoQuanDich2];
	*/
	if (iSoQuanDich >= iSoQuanDich2)
		iScoreTempCheoXuoi -= 1;
	else
		iScoreTempCheoXuoi -= 2;
	if (iSoQuanDich == 4)
		iScoreTempCheoXuoi *= 2;
	return iScoreTempCheoXuoi;
}
Point Board::timKiemNuocDi() {
	int dong = 1, cot = 1;
	long Diem = 0;
	for (int i = 1; i <= size_of_board; i++) {
		for (int j = 1; j <= size_of_board; j++) {
			long DiemTanCong = 0;
			long DiemPhongThu = 0;
			if (this->getVal(i, j) == 0) {
				DiemTanCong += SoDiemTanCong_DuyetDoc(i, j) + SoDiemTanCong_DuyetNgang(i, j) 
					+ SoDiemTanCong_DuyetCheo1(i, j) + SoDiemTanCong_DuyetCheo2(i, j);
				DiemPhongThu += SoDiemPhongThu_DuyetDoc(i, j) + SoDiemPhongThu_DuyetNgang(i, j)
				+ SoDiemPhongThu_DuyetCheo1(i, j) + SoDiemPhongThu_DuyetCheo2(i, j);
				if (DiemTanCong > DiemPhongThu)	{
					if (Diem < DiemTanCong) {
						Diem = DiemTanCong;
						dong = i;
						cot = j;
					}
				}
				else {
					if (Diem < DiemPhongThu) {
						Diem = DiemPhongThu;
						dong = i;
						cot = j;
					}
				}
			}
		}
	}
	this->input(dong, cot, 'X');
	Point ChessPoint(dong, cot, 'X');
	return ChessPoint;
}
