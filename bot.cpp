#include "bot.h"
long SoDiemTanCong_DuyetDoc(long Dong, long Cot) {
	{
		long iScoreTempDoc = 0;
		long iScoreAttack = 0;
		int iSoQuanTa = 0;
		int iSoQuanDich = 0;
		int iSoQuanTa2 = 0;
		int iSoQuanDich2 = 0;
		for (int iDem = 1; iDem < 6 && Dong + iDem <= size_of_board; iDem++)
		{
			if (b(Dong + iDem, Cot) == 'X')
				iSoQuanTa++;
			if (b(Dong + iDem, Cot) == 'O')
			{
				iSoQuanDich++;
				break;
			}
			if (b(Dong + iDem, Cot) == 0)
			{
				for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 <= size_of_board; iDem2++)
				{
					if (b(Dong + iDem2, Cot) == 'X')
						iSoQuanTa2++;
					if (b(Dong + iDem2, Cot) == 'O')
					{
						iSoQuanDich2++;
						break;
					}
					if (b(Dong + iDem2, Cot) == 0)
						break;
				}
				break;
			}

		}
		//iScoreAttack += Attack_Score[iSoQuanTa];
		//iSoQuanTa = 0;

		for (int iDem = 1; iDem < 6 && Dong - iDem > 0; iDem++)
		{
			if (b(Dong - iDem, Cot) == 'X')
				iSoQuanTa++;
			if (b(Dong - iDem, Cot) == 'O')
			{
				iSoQuanDich++;
				break;
			}
			if (b(Dong - iDem, Cot) == 0)
			{
				for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 > 0; iDem2++)
				{
					if (b(Dong - iDem2, Cot) == 'X')
						iSoQuanTa2++;
					if (b(Dong - iDem2, Cot) == 'O')
					{
						iSoQuanDich2++;
						break;
					}
					if (b(Dong - iDem2, Cot) == 0)
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
long SoDiemTanCong_DuyetNgang(long Dong, long Cot) {
	long iScoreTempNgang = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board; iDem++)
	{
		if (b(Dong, Cot + iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong, Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong, Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong, Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong, Cot + iDem2) == 0)
					break;
			}
			break;
		}
	}
	//iScoreAttack += Attack_Score[iSoQuanTa];
	//iSoQuanTa = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0; iDem++)
	{
		if (b(Dong, Cot - iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong, Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0; iDem2++)
			{
				if (b(Dong, Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong, Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong, Cot - iDem2) == 0)
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
long SoDiemTanCong_DuyetCheo1(long Dong, long Cot) {
	long iScoreTempCheoNguoc = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong + iDem <= size_of_board; iDem++)
	{
		if (b(Dong + iDem, Cot + iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong + iDem, Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong + iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong + iDem2, Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong + iDem2, Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong + iDem2, Cot + iDem2) == 0)
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
		if (b(Dong - iDem, Cot - iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong - iDem, Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong - iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong - iDem2 > 0; iDem2++)
			{
				if (b(Dong - iDem2, Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong - iDem2, Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong - iDem2, Cot - iDem2) == 0)
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
long SoDiemTanCong_DuyetCheo2(long Dong, long Cot) {
	long iScoreTempCheoXuoi = 0;
	long iScoreAttack = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa2 = 0;
	int iSoQuanDich2 = 0;
	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong + iDem <= size_of_board; iDem++)
	{
		if (b(Dong + iDem, Cot - iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong + iDem, Cot - iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong + iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong + iDem2, Cot - iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong + iDem2, Cot - iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong + iDem2, Cot - iDem2) == 0)
					break;
			}
			break;
		}
	}
	//iScoreAttack += Attack_Score[iSoQuanTa];
	//iSoQuanTa = 0;

	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong - iDem > 0; iDem++)
	{
		if (b(Dong - iDem, Cot + iDem) == 'X')
			iSoQuanTa++;
		if (b(Dong - iDem, Cot + iDem) == 'O')
		{
			iSoQuanDich++;
			break;
		}
		if (b(Dong - iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong - iDem2 > 0; iDem2++)
			{
				if (b(Dong - iDem2, Cot + iDem2) == 'X')
					iSoQuanTa2++;
				if (b(Dong - iDem2, Cot + iDem2) == 'O')
				{
					iSoQuanDich2++;
					break;
				}
				if (b(Dong - iDem2, Cot + iDem2) == 0)
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
long SoDiemPhongThu_DuyetDoc(long Dong, long Cot) {
	long iScoreTempDoc = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Dong + iDem <= size_of_board; iDem++)
	{
		if (b(Dong + iDem, Cot) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong + iDem, Cot) == 'O')
			iSoQuanDich++;
		if (b(Dong + iDem, Cot) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong + iDem2, Cot) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong + iDem2, Cot) == 'O')
					iSoQuanDich2++;
				if (b(Dong + iDem2, Cot) == 0)
					break;
			}
			break;
		}
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Dong - iDem > 0; iDem++)
	{
		if (b(Dong - iDem, Cot) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong - iDem, Cot) == 'O')
			iSoQuanDich++;
		if (b(Dong - iDem, Cot) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Dong - iDem2 > 0; iDem2++)
			{
				if (b(Dong - iDem2, Cot) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong - iDem2, Cot) == 'O')
					iSoQuanDich2++;
				if (b(Dong - iDem2, Cot) == 0)
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

long SoDiemPhongThu_DuyetNgang(long Dong, long Cot) {
	long iScoreTempNgang = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board; iDem++)
	{
		if (b(Dong, Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong, Cot + iDem) == 'O')
			iSoQuanDich++;
		if (b(Dong, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong, Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong, Cot + iDem2) == 'O')
					iSoQuanDich2++;
				if (b(Dong, Cot + iDem2) == 0)
					break;
			}
			break;
		}
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0; iDem++)
	{
		if (b(Dong, Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0; iDem2++)
			{
				if (b(Dong, Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong, Cot - iDem2) == 0)
					break;
				if (b(Dong, Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (b(Dong, Cot - iDem) == 'O')
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
long SoDiemPhongThu_DuyetCheo1(long Dong, long Cot) {

	long iScoreTempCheoNguoc = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong + iDem <= size_of_board; iDem++)
	{
		if (b(Dong + iDem, Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong + iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong + iDem2, Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong + iDem2, Cot + iDem2) == 0)
					break;
				if (b(Dong + iDem2, Cot + iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (b(Dong + iDem, Cot + iDem) == 'O')
			iSoQuanDich++;
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong - iDem > 0; iDem++)
	{
		if (b(Dong - iDem, Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}

		if (b(Dong - iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong - iDem2 > 0; iDem2++)
			{
				if (b(Dong - iDem2, Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}

				if (b(Dong - iDem2, Cot - iDem2) == 0)
					break;
				if (b(Dong - iDem2, Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (b(Dong - iDem, Cot - iDem) == 'O')
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

long SoDiemPhongThu_DuyetCheo2(long Dong, long Cot) {
	long iScoreTempCheoXuoi = 0;
	long iScoreDefend = 0;
	int iSoQuanDich = 0;
	int iSoQuanTa = 0;
	int iSoQuanDich2 = 0;
	int iSoQuanTa2 = 0;
	for (int iDem = 1; iDem < 6 && Cot - iDem > 0 && Dong + iDem <= size_of_board; iDem++)
	{
		if (b(Dong + iDem, Cot - iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong + iDem, Cot - iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot - iDem2 > 0 && Dong + iDem2 <= size_of_board; iDem2++)
			{
				if (b(Dong + iDem2, Cot - iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong + iDem2, Cot - iDem2) == 0)
					break;
				if (b(Dong + iDem2, Cot - iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (b(Dong + iDem, Cot - iDem) == 'O')
			iSoQuanDich++;
	}
	//iScoreDefend += Defend_Score[iSoQuanDich];
	//iSoQuanDich = 0;

	for (int iDem = 1; iDem < 6 && Cot + iDem <= size_of_board && Dong - iDem > 0; iDem++)
	{
		if (b(Dong - iDem, Cot + iDem) == 'X')
		{
			iSoQuanTa++;
			break;
		}
		if (b(Dong - iDem, Cot + iDem) == 0)
		{
			for (int iDem2 = 2; iDem2 < 7 && Cot + iDem2 <= size_of_board && Dong - iDem2 > 0; iDem2++)
			{
				if (b(Dong - iDem2, Cot + iDem2) == 'X')
				{
					iSoQuanTa2++;
					break;
				}
				if (b(Dong - iDem2, Cot + iDem2) == 0)
					break;
				if (b(Dong - iDem2, Cot + iDem2) == 'O')
					iSoQuanDich2++;
			}
			break;
		}
		if (b(Dong - iDem, Cot + iDem) == 'O')
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
Point timKiemNuocDi() {
	int dong = 1, cot = 1;
	long Diem = 0;
	for (int i = 1; i <= size_of_board; i++)
	{
		for (int j = 1; j <= size_of_board; j++)
		{
			long DiemTanCong = 0;
			long DiemPhongThu = 0;
			if (b(i, j) == 0)
			{
				DiemTanCong += SoDiemTanCong_DuyetDoc(i, j);
				DiemTanCong += SoDiemTanCong_DuyetNgang(i, j);
				DiemTanCong += SoDiemTanCong_DuyetCheo1(i, j);
				DiemTanCong += SoDiemTanCong_DuyetCheo2(i, j);

				DiemPhongThu += SoDiemPhongThu_DuyetDoc(i, j);
				DiemPhongThu += SoDiemPhongThu_DuyetNgang(i, j);
				DiemPhongThu += SoDiemPhongThu_DuyetCheo1(i, j);
				DiemPhongThu += SoDiemPhongThu_DuyetCheo2(i, j);

				if (DiemTanCong > DiemPhongThu)
				{
					if (Diem < DiemTanCong)
					{
						Diem = DiemTanCong;
						dong = i;
						cot = j;
					}
				}
				else
				{
					if (Diem < DiemPhongThu)
					{
						Diem = DiemPhongThu;
						dong = i;
						cot = j;
					}
				}
			}
		}
	}
	b.input(dong, cot, 'X');
	Point ChessPoint(dong, cot, 'X');
	return ChessPoint;
}