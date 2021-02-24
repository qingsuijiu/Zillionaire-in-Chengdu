#pragma once
#include"dfwmap.h"
#include"site.h"
#include"person.h"
#include"dice.h"
#include"destiny.h"
#include"caption.h"

#include<vector>
#include<memory>
#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include<stdlib.h>
#include <iostream>
#include<fstream>

#pragma comment(lib,"Winmm.lib")
#include <mmsystem.h>


using namespace std;

class dfw
{
public:
	dfw(vector<int> player, vector<int> robot, vector<string> names, int round, int s_money);
	~dfw(){}
	void dfw_main();

private:
	vector<shared_ptr<person>> players;
	dfwmap m;
	dice d;
	size_t largest_round;  //最大回合数
	size_t player_num;  //玩家数量
	size_t robot_num;  //机器人数量
	size_t start_money;  //起始资金

	IMAGE img;
	IMAGE background;  //背景图
	IMAGE dialog;  //对话框

	void init();
	void refresh_background();
	void refresh_background(int ignore_id);

	int throw_dice(int j);
	bool player_move(int player_id, int p);
	void operatate_estate( shared_ptr<site> current_site,int j);
	void count_property();
	void go_to_prison(int player_id);
	void step_on_shirt(int player_id, shared_ptr<site> s);
	void judge_bankruptcy(int player_id);
	void build_something(shared_ptr<site> s, int player_id, int kind);
};

void init_music();

