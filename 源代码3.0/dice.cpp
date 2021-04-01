#include "dice.h"

dice::dice()
{
	loadimage(&dice_t, _T("dice.png"));
	IMAGE dice_1, dice_2, dice_3, dice_4, dice_5, dice_6;
	loadimage(&dice_1, _T("dice_1.png"));
	loadimage(&dice_2, _T("dice_2.png"));
	loadimage(&dice_3, _T("dice_3.png"));
	loadimage(&dice_4, _T("dice_4.png"));
	loadimage(&dice_5, _T("dice_5.png"));
	loadimage(&dice_6, _T("dice_6.png"));

	point[1] = dice_1;
	point[2] = dice_2;
	point[3] = dice_3;
	point[4] = dice_4;
	point[5] = dice_5;
	point[6] = dice_6;

	location_t = { 851, 206 };
	location_p = { 950, 220 };
}

size_t dice::throw_dice()
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<size_t> u(1, 6);
	return u(e);
}