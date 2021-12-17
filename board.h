#pragma once
#include "point.h"
class Board {
	const int n = 20;				// Kích thước của bảng 20 x 20
	Point* board[21][21];			// Mảng hai chiều chứa dữ liệu các điểm
public:
	Board();
	virtual ~Board();
	
	int STT = 0;					// Số bước đi
	int getSize();					// Đưa ra kích thước bàn cờ	
	void reset();					// Đặt lại giá trị cho các điểm trên bàn cờ
	int operator () (int, int);		// Lấy ra giá trị điểm trên bàn cờ theo dạng b(i, j)
	int getVal(int, int);			// Lấy ra giá trị điểm trên bàn cờ
	void input(int, int, int);		// Gán giá trị A cho một điểm có tọa độ i, j theo dạng b.input(i, j, A) 
	void setLocation(int, int);		// Gán giá trị tọa độ	
	// Gán giá trị tọa độ
	int getX(int, int);
	int getY(int, int);
	// Kiểm tra đã đánh hay chưa, nếu chưa trả về true
	bool check(int, int);
	// Kiểm tra có nằm trong vùng bàn cờ hay không, nếu không trả về false
	bool checkArea(int, int);
	// Kiểm tra đã thắng hay chưa
	bool checkWin(int, int);
	bool checkWinRow(int, int);
	bool checkWinCol(int, int);
	bool checkWinFirstDiagonaly(int, int);
	bool checkWinSecDiagonaly(int, int);
	// Vẽ ra quân cờ
	void drawChessman(int, int);
	// Tìm kiếm nước đi cho máy
	long SoDiemTanCong_DuyetDoc(long, long);
	long SoDiemTanCong_DuyetNgang(long, long);
	long SoDiemTanCong_DuyetCheo1(long, long);
	long SoDiemTanCong_DuyetCheo2(long, long);
	long SoDiemPhongThu_DuyetDoc(long, long);
	long SoDiemPhongThu_DuyetNgang(long, long);
	long SoDiemPhongThu_DuyetCheo1(long, long);
	long SoDiemPhongThu_DuyetCheo2(long, long);

	Point timKiemNuocDi();
};

