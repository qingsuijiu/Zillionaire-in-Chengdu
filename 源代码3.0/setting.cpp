#include "setting.h"

vector<string> setting::names = { "屁宝羊崽","黑客fy","屎宝樊人精","萌宝洋芋","盲盒少女" };
vector<int> setting::figure_xs = { 100,200,300,400,500 };
int setting::figure_y = 450;
int setting::arrow_x_change = 100;

setting::setting() 
{ 
	figures.resize(5);
	loadimage(&background, _T("setting_background.png")); 
	loadimage(&arrow, _T("arrow.png"));

	loadimage(&figures[0], _T("cartoon_gy.png"));
	loadimage(&figures[1], _T("cartoon_fy.png"));
	loadimage(&figures[2], _T("cartoon_frj.png"));
	loadimage(&figures[3], _T("cartoon_yy.png"));
	loadimage(&figures[4], _T("blindboxgirl.png"));

	largest_round = 20;
	player_num = 2;
	start_money = 10000;
}

void setting::setting_main()
{
	// 绘图窗口初始化
	initgraph(718, 631);
	refresh();

	round_set();
	start_money_set();
	player_num_set();
	figure_set();

	setting_caption_round("按任意键进入游戏界面");
	_getch();
	closegraph();
}

void setting::refresh()
{
	putimage(0, 0, &background);

	for (int i = 0; i < figures.size(); i++)
	{
		setting_caption_name(names[i], i);
		putimage(figure_xs[i], figure_y, &figures[i]);
	}

}

void setting::round_set()
{
	refresh();
	string temp = "最大回合数：";
	temp += to_string(largest_round);
	temp += "\n按←减少，按→增加,回车表示确定";
	setting_caption_round(temp);

	while (1)
	{
		//_getch();
		int c = _getch();
		//c = _getch();
		if (c == 77)  //right key
		{
			largest_round += 5;

			refresh();
			string temp = "最大回合数：";
			temp += to_string(largest_round);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 75)  //left key
		{
			if(largest_round >= 5)
				largest_round -= 5;

			refresh();
			string temp = "最大回合数：";
			temp += to_string(largest_round);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 13)  //回车
		{

			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

void setting::start_money_set()
{
	refresh();
	string temp = "起始资金：";
	temp += to_string(start_money);
	temp += "\n按←减少，按→增加,回车表示确定";
	setting_caption_round(temp);

	while (1)
	{
		//_getch();
		int c = _getch();
		//c = _getch();
		if (c == 77)  //right key
		{
			start_money += 1000;

			refresh();
			string temp = "起始资金：";
			temp += to_string(start_money);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 75)  //left key
		{
			if (start_money > 0)
				start_money -= 1000;

			refresh();
			string temp = "起始资金：";
			temp += to_string(start_money);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 13)  //回车
		{
			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}


void setting::player_num_set()
{
	refresh();
	string temp = "玩家数：";
	temp += to_string(player_num);
	temp += "\n按←减少，按→增加,回车表示确定";
	setting_caption_round(temp);

	while (1)
	{
		//_getch();
		int c = _getch();
		//c = _getch();
		if (c == 77)  //right key
		{
			player_num++;

			refresh();
			string temp = "玩家数：";
			temp += to_string(player_num);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 75)  //left key
		{
			if (player_num >= 1)
				player_num--;

			refresh();
			string temp = "玩家数：";
			temp += to_string(player_num);
			temp += "\n按←减少，按→增加,回车表示确定";
			setting_caption_round(temp);
		}
		else if (c == 13)  //回车
		{
			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

void setting::figure_set_inf(int i)
{
	string temp = "现在由玩家";
	temp += to_string(i);
	temp += "选择人物角色";
	temp += "\n按←左移，按→右移,回车表示确定";
	setting_caption_round(temp);
}

void setting::figure_set()
{
	for (int i = 0; i < player_num; i++)
	{
		refresh();

		//显示初始箭头
		arrow_x = figure_xs[0];
		const int arrow_y = 370;
		const int arrow_x_offset = 20;
		putimage(arrow_x + arrow_x_offset, arrow_y, &arrow);

		//提示人物选择方式
		figure_set_inf(i + 1);
	
		while (1)
		{
			//_getch();
			int c = _getch();
			//c = _getch();
			if (c == 77)  //right key
			{
				refresh();
				if (arrow_x < figure_xs[figure_xs.size()-1])
					arrow_x += arrow_x_change;
				putimage(arrow_x + arrow_x_offset, arrow_y, &arrow);
				figure_set_inf(i + 1);
			}
			else if (c == 75)  //left key
			{
				refresh();
				if (arrow_x > figure_xs[0])
					arrow_x -= arrow_x_change;
				putimage(arrow_x + arrow_x_offset, arrow_y, &arrow);
				figure_set_inf(i + 1);
			}
			else if (c == 13)  //回车
			{
				kind.push_back((arrow_x - figure_xs[0]) / arrow_x_change + 1);
				refresh();
				break;
			}
			else//异常输入的处理
			{
				//caption_write(1, "输入错误，请输入y/n");
			}
		}

	}
}
