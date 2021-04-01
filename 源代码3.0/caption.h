#pragma once
#include<string>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
using namespace std;

/*
class caption
{
public:
	caption(){}
	~caption(){}
	void cap_write(int kind,string text);
private:
	
};
*/

void caption_write(int kind, string text);
void caption_write_r(string text);
void caption_write_money_show(string text);

void setting_caption_round(string text);
void setting_caption_name(string text, int i);

