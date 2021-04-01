#include "caption.h"

void caption_write(int kind, string text)
{
	//将string转换为outtextxy可以接受的格式
	//string-->char[ ]-->LPCTSTR
	char s[100];
	int i;
	for (i = 0; i < text.length(); i++)
		s[i] = text[i];
	s[i] = '\0';
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t* wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	//设置统一的字体格式
	settextstyle(25, 0, _T("Consolas"));
	settextcolor(0x000000);
	setbkmode(TRANSPARENT);

	//选择输出位置，输出内容
	switch (kind)
	{
	case 1:
		outtextxy(200, 173, wide);
		break;
	case 2:
		outtextxy(200, 260, wide);
		break;
	case 3:
		outtextxy(300, 570, wide);
		break;
	case 4:
		outtextxy(820, 175, wide);
		break;
	case 5:
		outtextxy(1225, 335, wide);
		break;
	
	}
	Sleep(500);
}

void caption_write_money_show(string text)
{
	//设置统一的字体格式
	settextstyle(25, 0, _T("Consolas"));
	settextcolor(0x000000);
	setbkmode(TRANSPARENT);

	char s[100];
	int i;
	for (i = 0; i < text.length(); i++)
		s[i] = text[i];
	s[i] = '\0';
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t* wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	RECT r = { 300, 570, 850, 700 };
	drawtext(wide, &r, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
}

void caption_write_r(string text)
{
	IMAGE blank;
	loadimage(&blank, _T("blank.png"));
	putimage(1225, 335, &blank);

	//设置统一的字体格式
	settextstyle(25, 0, _T("Consolas"));
	settextcolor(0x000000);
	setbkmode(TRANSPARENT);

	char s[300];
	int i;
	for (i = 0; i < text.length(); i++)
		s[i] = text[i];
	s[i] = '\0';
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t* wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	RECT r = { 1225, 335, 1410, 670 };
	drawtext(wide, &r, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
	/*
	char s[17];
	int p_text = 0;
	while (p_text < text.size())
	{
		for (int i = 0; i < 14 && p_text < text.size(); i++)
		{
			s[i] = text[p_text];
			p_text++;
		}
		s[14] = '\0';
		int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
		wchar_t* wide = new wchar_t[n];
		MultiByteToWideChar(0, 0, s, -1, wide, n);
		outtextxy(1225, 335 + p_text * 2, wide);
	}
	*/
}

void setting_caption_round(string text)
{
	//设置统一的字体格式
	settextstyle(25, 0, _T("Consolas"));
	settextcolor(0x000000);
	setbkmode(TRANSPARENT);

	char s[100];
	int i;
	for (i = 0; i < text.length(); i++)
		s[i] = text[i];
	s[i] = '\0';
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t* wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	RECT r = { 150, 100, 550, 200 };
	drawtext(wide, &r, DT_CENTER | DT_VCENTER | DT_WORDBREAK);
}

void setting_caption_name(string text, int x)
{
	char s[100];
	int i;
	for (i = 0; i < text.length(); i++)
		s[i] = text[i];
	s[i] = '\0';
	int n = MultiByteToWideChar(0, 0, s, -1, NULL, 0);
	wchar_t* wide = new wchar_t[n];
	MultiByteToWideChar(0, 0, s, -1, wide, n);

	//设置统一的字体格式
	settextstyle(15, 0, _T("Consolas"));
	settextcolor(0x000000);
	setbkmode(TRANSPARENT);

	outtextxy(100 + x * 100, 430, wide);

}