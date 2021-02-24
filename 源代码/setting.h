#pragma once

#include<vector>
#include<string>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include<iostream>
#include<fstream>
#include"caption.h"
using namespace std;
class setting
{
public:
	setting();
	~setting() {}

	void setting_main();

	int get_round()
	{
		return largest_round;
	}
	int get_player_num()
	{
		return player_num;
	}
	vector<int> get_kinds()
	{
		return kind;
	}
	int get_start_money()
	{
		return start_money;
	}

private:
	vector<int> kind;
	int largest_round;
	int player_num;
	int start_money;
	
	IMAGE arrow;
	IMAGE background;
	vector<IMAGE> figures;
	int arrow_x;

	void refresh();
	void round_set();
	void start_money_set();
	void player_num_set();
	void figure_set();
};

