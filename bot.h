#pragma once
#include "draw.h"
extern Board b;
const static long Defend_Score[6] = {0, 8, 512, 32768, 2097152, 134217728};
const static long Attack_Score[6] = {0, 64, 4096, 262144, 16777216, 1073741824};

long SoDiemTanCong_DuyetDoc(long, long);
long SoDiemTanCong_DuyetNgang(long, long);
long SoDiemTanCong_DuyetCheo1(long, long);
long SoDiemTanCong_DuyetCheo2(long, long);
long SoDiemPhongThu_DuyetDoc(long, long);
long SoDiemPhongThu_DuyetNgang(long, long);
long SoDiemPhongThu_DuyetCheo1(long, long);
long SoDiemPhongThu_DuyetCheo2(long, long);

Point timKiemNuocDi();