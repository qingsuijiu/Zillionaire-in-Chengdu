#include "dfw.h"

vector<string> dfw::building_names = { "青年旅舍","宾馆","情侣酒店" };
vector<double> dfw::building_prices = { -0.3,-0.4,-0.5 };
vector<double> dfw::tolls = { 0.1, 0.2,0.35,0.55 };

dfw::dfw(vector<int> human, vector<int> robot, vector<string> names, int round,int s_money) 
	:largest_round(round),start_money(s_money)
{

	//下面两个变量之后都可让用户设置
	//start_money = 0;
	//largest_round = 20;
	start_money = s_money;

	loadimage(&background, _T("dfw_map_3.png"));
	loadimage(&dialog, _T("dialog3.png"));
	for (int i = 0; i < human.size(); i++)
	{
		shared_ptr<person> temp = nullptr;
		switch (human[i])
		{
		case 0:
			temp = make_shared<person>(names[i], start_money, human[i]);
			break;
		case 1:
			temp = make_shared<fartman>("屁宝羊崽", start_money);
			break;
		case 2:
			temp = make_shared<hacker>("黑客fy", start_money);
			break;
		case 3:
			temp = make_shared<shirtman>("屎宝樊人精", start_money);
			break;
		case 4:
			temp = make_shared<cutebaby>("萌宝洋芋", start_money);
			break;
		case 5:
			temp = make_shared<blindBoxGirl>("盲盒少女", start_money);
			break;
		default:
			cout << "人物种类出错！";
			break;
		}

		players.push_back(temp);
	}
	for (int i = 0; i < robot.size(); i++)
	{
		shared_ptr<person> temp = make_shared<person>("robot", start_money, robot[i]);
		players.push_back(temp);
	}

}


void dfw::dfw_main()
{
	initgraph(1420, 813);   //1200,850+200
	refresh_background();
	init_music();

	/*
	//测试入狱功能 与 hacker的技能
	m.get_site(1)->set_owner(players[0]);
	m.get_site(2)->set_owner(players[0]);
	m.get_site(4)->set_owner(players[0]);
	m.get_site(5)->set_owner(players[0]);

	m.get_site(1)->set_status(1);
	m.get_site(2)->set_status(1);
	m.get_site(4)->set_status(1);
	m.get_site(5)->set_status(1);
*/



	//将所有人物的图片放到起点
	for (int i = players.size() - 1; i >= 0; i--)
	{
		pair<int, int> loc = m.get_site(0)->get_location();
		putimage(loc.first, loc.second, players[i]->get_picture());
	}

	for (int i = 0; i < largest_round; i++)
	{
		for (int j = 0; j < players.size(); j++)
		{
			if (players[j]->get_pause())
			{
				players[j]->set_pause(false);
				string temp = players[j]->get_name();
				temp += "跳过该回合";
				caption_write(1, temp);
				Sleep(1000);
				refresh_background();
				continue;
			}

			//抛骰子
			int p = throw_dice(j);
			//角色移动，并判断是否过起点
			if (player_move(j, p))
			{
				string temp = players[j]->get_name();
				temp += "通过起点，完成一圈";
				caption_write_r(temp);
				_getch();
				string temp2 = players[j]->reach_starting();

				//如果是盲盒少女，需要重新初始化主游戏界面
				if (players[j]->get_kind() == 5)
				{
					initgraph(1420, 813);   //1200,850+200
				}
				refresh_background();
				//如果person类的reach_starting方法返回非空的string，需将其输出
				if (!temp2.empty())
				{
					caption_write_r(temp2);
					_getch();
				}
				
				//take_loans();
			}
			//对于目标地点的操作
			shared_ptr<site> current_site = m.get_site(players[j]->get_location());
			operatate_estate(current_site, j);

			judge_bankruptcy(j);
			Sleep(1000);


			refresh_background();
		}
		
	}
	count_property();
	refresh_background();
	caption_write(1, "game over!");
	Sleep(1000);
	closegraph();
	
	return;
}


int dfw::throw_dice(int j)
{
	//将键盘缓冲区中之前误按的读走，否则会出现上次多按空格，这回就不用按直接执行的情况
	while(_kbhit())
		_getch();
	while (1)
	{
		FlushMouseMsgBuffer();  //清空鼠标缓存区
		string temp = "";
		temp += players[j]->get_name();
		temp += "请投掷骰子（按空格或点击右上角骰子图片）";
		caption_write(1, temp);
		//鼠标投掷
		if (MouseHit())
		{
			//FlushMouseMsgBuffer();
			MOUSEMSG m = GetMouseMsg();
			if (m.x > d.get_xy(1).first && m.x < d.get_xy(1).first + 100 &&
				m.y > d.get_xy(1).second && m.y < d.get_xy(1).second + 100 &&
				m.uMsg == WM_LBUTTONDOWN)
			{
				//outtextxy(200, 173, _T("Click on"));
				break;
			}
		}
		//键盘投掷
		if (_kbhit())
		{
			if (_getch() == 32)
			{
				//outtextxy(200, 173, _T("Hit Space"));
				break;
			}
		}
	}

	size_t p = d.throw_dice();
	
	refresh_background();
	//输出点数图片
	putimage(d.get_xy(0).first, d.get_xy(0).second, d.get_image(p));
	//输出点数文字
	string temp = "您掷出";
	temp += to_string(p);
	temp += "点";
	caption_write(4, temp);
	return p;
}

bool dfw::player_move(int player_id,int p)
{
	int move_steps = 10;
	if (p >= 1 && p <= 4)
		move_steps = p * 2;

	pair<int, int> pre = m.get_site(players[player_id]->get_location())->get_location();
	bool reach_starting = players[player_id]->go_steps(p);
	pair<int, int> current = m.get_site(players[player_id]->get_location())->get_location();

	int movex = (current.first - pre.first) / move_steps;
	int movey = (current.second - pre.second) / move_steps;

	//outfile << "pre:" << pre.first<<" "<<pre.second << endl;
	//outfile << "current:" << current.first << "  " << current.second << endl;
	//outfile << "movexy:" << movex << " " << movey << endl;
	for (int i = 1; i <= move_steps; i++)
	{
		refresh_background(player_id);
		putimage(pre.first + movex * i, pre.second + movey * i, players[player_id]->get_picture());	
		Sleep(200);
	}
	refresh_background();
	return reach_starting;
}

/*
void dfw::init()
{
	// 绘图窗口初始化
	initgraph(1200, 850);

	loadimage(&background, _T("dfw_map.png"));

	for (int i = 0; i < players.size(); i++)
	{
		shared_ptr<person> temp = make_shared<person>("player", start_money, players[i]);
		players.push_back(temp);
	}
}
*/

void dfw::refresh_background()
{
	putimage(0, 0, &background);
	//putimage(1150, 0, &dialog);
	putimage(d.get_xy(1).first, d.get_xy(1).second, d.get_image(0));
	for (int i = players.size() - 1; i >= 0; i--)
	{
		pair<int,int> temp = m.get_site(players[i]->get_location())->get_location();
		putimage(temp.first, temp.second, players[i]->get_picture());
	}

	show_money_situation();
}

void dfw::show_money_situation()
{
	string temp = "现金情况:";
	for (int i = 0; i < players.size(); ++i)
	{
		if (i == 2)
			temp += "\n";
		//temp += "\t";
		temp += "  ";
		temp += players[i]->get_name();
		temp += ":";
		temp += to_string(players[i]->get_money());
	}
	caption_write_money_show(temp);

}


void dfw::refresh_background(int ignore_id)
{
	putimage(0, 0, &background);
	putimage(d.get_xy(1).first, d.get_xy(1).second, d.get_image(0));
	for (int i = players.size() - 1; i >= 0; i--)
	{
		if (i != ignore_id)
		{
			pair<int, int> temp = m.get_site(players[i]->get_location())->get_location();
			putimage(temp.first, temp.second, players[i]->get_picture());
		}
	}

	//show_money_situation();
}


void dfw::operatate_estate(shared_ptr<site> current_site,int j)
{
	switch (current_site->get_status())
	{
	case -1:  //交税
	{
		touch_tax(j, current_site->get_name());
		break;
	}
	case -2: //机会
	{
		touch_cha_des("按空格，获得神秘机会", j, 0);
		break;
	}
	case -3: //命运
	{
		touch_cha_des("按空格，获得神秘命运", j, 1);
		break;
	}
	case -4:  //路过
	{
		refresh_background();
		string temp = "";
		temp += players[j]->get_name();
		temp += "路过";
		temp += current_site->get_name();
		caption_write(2, temp);
		break;
	}
	case -5: //入牢
	{
		refresh_background();
		string temp = "";
		temp += players[j]->get_name();
		temp += "入牢";
		caption_write(2, temp);
		player_move(j, -15);
		players[j]->set_pause(true);
		break;
	}
	case 0:  //无人拥有的土地
	{
		land_basic_operations(j, current_site);
		touch_no_owner_land(j, current_site);
		break;
	}
	case 1: //有人拥有的空地
	{
		land_basic_operations(j, current_site);
		pay_or_build(j, current_site, 1, 0, "");
		break;
	}
	case 2:  //青年旅社
	{
		land_basic_operations(j, current_site);
		pay_or_build(j, current_site, 2, 1, "青年旅舍");
		break;
	}
	case 3:  //宾馆
	{
		land_basic_operations(j, current_site);
		pay_or_build(j, current_site, 3, 2, "宾馆");
		break;

	}
	case 4:  //情侣酒店
	{
		land_basic_operations(j, current_site);
		pay_or_build(j, current_site, 0, 3, "情侣酒店");
		break;
	}
	default:break;//在这要加异常

	}
}

void dfw::touch_cha_des(string cap,int player_id,int des_kind)
{
	while (_kbhit())
		_getch();
	refresh_background();
	caption_write(2, cap);
	destiny cha(des_kind);
	while (1)
	{
		if (_kbhit())
		{
			char c = _getch();
			if (c >= 48 || c <= 58)
			{
				cha.set_id(c - 48);
				break;
			}
			else if (c == 13)
			{
				break;
			}
		}
	}

	caption_write_r(cha.get_content());
	players[player_id]->set_money(cha.get_money_change());
	_getch();  //按任意键进入下一步

	if (cha.is_to_jail())
	{
		_getch();
		go_to_prison(player_id);
	}
}

void dfw::touch_tax(int player_id,string tax_name)
{
	refresh_background();
	string temp = "";
	temp += players[player_id]->get_name();
	temp += "需交";
	temp += tax_name;
	temp += "700元，已自动为你个小屁娃子付喽！";
	caption_write(2, temp);
	players[player_id]->set_money(-700);
	_getch();
}

void dfw::land_basic_operations(int player_id, shared_ptr<site> current_site)
{
	//人物可能拥有的技能
	int res = players[player_id]->all_land_operations();
	if (res == 2)
		current_site->set_shirt(true);
	else if (res == 1)
		go_to_prison(player_id);

	//是否踩到该地的粑粑
	step_on_shirt(player_id, current_site);
}

void dfw::touch_no_owner_land(int player_id, shared_ptr<site> current_site)
{
	if (current_site->get_price() > players[player_id]->get_money())
	{
		refresh_background();
		caption_write(2, "很可惜，你已经买不起了！");
		return;
	}
	//买得起的情况
	string temp = "您现在拥有现金";
	temp += to_string(players[player_id]->get_money());
	temp += "元，";
	temp += "是否购买 ";
	temp += current_site->get_name();
	temp += " ";
	temp += to_string(current_site->get_price());
	temp += " (y/n)";
	caption_write(2, temp);
	Sleep(1000);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			current_site->set_status(1);
			current_site->set_owner(players[player_id]);
			players[player_id]->set_money(current_site->get_price() * (-1));
			players[player_id]->acquire_property(current_site->get_id());

			//refresh_background();
			string temp2 = "";
			temp2 += players[player_id]->get_name();
			temp2 += "已购买";
			temp2 += current_site->get_name();
			caption_write(1, temp2);
			Sleep(1000);
			break;
		}
		else if (c == 'n')
		{
			//refresh_background();
			string temp2 = "";
			temp2 += players[player_id]->get_name();
			temp2 += "放弃购买";
			temp2 += current_site->get_name();
			caption_write(1, temp2);
			Sleep(1000);
			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

void dfw::pay_or_build(int player_id, shared_ptr<site> current_site,int build_kind,int pay_kind,string building_name)
{
	if (current_site->get_owner() == players[player_id])
	{
		int res = players[player_id]->self_land_operations();
		if (res == 1)
			go_to_prison(player_id);

		//选择建青年旅舍
		build_something(current_site, player_id, build_kind);
	}
	else
	{
		refresh_background();
		//交佣金
		string temp2 = "";
		temp2 += players[player_id]->get_name();
		temp2 += "享受完";
		temp2 += building_name;
		temp2 += "后，";
		temp2 += "需向该土地拥有者";
		temp2 += current_site->get_owner()->get_name();
		temp2 += "支付过路费";
		int toll = current_site->get_price() * tolls[pay_kind];
		temp2 += to_string(toll);
		temp2 += "元，来来来，给钱！";
		caption_write(1, temp2);

		players[player_id]->set_money((-1) * toll);
		current_site->get_owner()->set_money(toll);

		_getch();
	}
}

void dfw::count_property()
{
	vector<int> property(players.size(), 0);
	for (int i = 0; i < 30; i++)
	{
		for (int j = 0; j < players.size(); j++)
		{
			if (m.get_site(i)->get_owner() == players[j])
			{
				property[j] += m.get_site(i)->get_price();
				break;
			}
		}
	}

	refresh_background();
	int max = 0;
	int max_id = -1;
	string temp = "最终总资产：\n";
	for (int i = 0; i < players.size(); i++)
	{
		property[i] += players[i]->get_money();
		temp += players[i]->get_name();
		temp += "：";
		temp += to_string(property[i]);
		temp += "\n";

		if (property[i] > max)
		{
			max = property[i];
			max_id = i;
		}
	}
	caption_write_r(temp);
	_getch();

	string temp2 = "最终的获胜者为";
	temp2 += players[max_id]->get_name();
	temp2 += ",大吉大利今晚rua羊！";
	refresh_background();
	caption_write_r(temp2);
	_getch();
}

void dfw::go_to_prison(int player_id)
{
	const int move_steps = 10;

	pair<int, int> pre = m.get_site(players[player_id]->get_location())->get_location();
	players[player_id]->goto_location(9);
	pair<int, int> current = m.get_site(9)->get_location();

	int movex = (current.first - pre.first) / move_steps;
	int movey = (current.second - pre.second) / move_steps;

	//outfile << "pre:" << pre.first<<" "<<pre.second << endl;
	//outfile << "current:" << current.first << "  " << current.second << endl;
	//outfile << "movexy:" << movex << " " << movey << endl;
	for (int i = 1; i <= move_steps; i++)
	{
		refresh_background(player_id);
		putimage(pre.first + movex * i, pre.second + movey * i, players[player_id]->get_picture());
		Sleep(200);
	}
	players[player_id]->set_pause(true);
	//refresh_background();
}

void dfw::step_on_shirt(int player_id,shared_ptr<site> s)
{
	if (!s->get_shirt() || players[player_id]->get_kind() == 3)
		return;
	caption_write(3, to_string(players[player_id]->get_kind()));


	string temp = players[player_id]->get_name();
	temp += "踩到了一坨便便，你可以进行以下选择：1.花400元洗干净  2.一口吃下（25%几率中毒）";
	caption_write_r(temp);
	s->set_shirt(false);
	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == '1')
		{
			string temp2 = players[player_id]->get_name();
			temp2 += "心疼地花费了400元把自己洗干净了";
			caption_write_r(temp2);
			players[player_id]->set_money(-400);
			break;
		}
		else if (c == '2')
		{
			static default_random_engine e(time(0));
			static uniform_int_distribution<size_t> u(1,4);
			string temp2 = players[player_id]->get_name();
			temp2 += "为了不用清洗，一狠心将粑粑吃下！";
			caption_write_r(temp2);
			players[player_id]->set_money(-400);
			_getch();

			int res = u(e);
			if (res == 1)
			{
				string temp3 = "很不幸，";
				temp3 += players[player_id]->get_name();
				temp3 += "体质不好，吃完后不幸中毒，花费500元治疗，并且下回合无法行动";
				caption_write_r(temp3);
				players[player_id]->set_money(-500);
				players[player_id]->set_pause(true);
			}
			else if(res == 4)
			{
				string temp3 = "震惊！";
				temp3 += players[player_id]->get_name();
				temp3 += "竟是传说中的避屎体质，吃完后不仅没事还神清气爽，工作效率倍增，老板奖励他300元！";
				caption_write_r(temp3);
				players[player_id]->set_money(-500);
			}
			else
			{
				string temp3 = players[player_id]->get_name();
				temp3 += "吃完后虽口感不适，但身体也无大碍，想想自己可以不用花清洁费，颇感欣慰";
				caption_write_r(temp3);
			}
			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
	_getch();
}

void dfw::judge_bankruptcy(int player_id)
{
	/*需增加房子的赎回*/
	//未破产，直接返回
	if (players[player_id]->get_money() >= 0)
		return;

	//此块土地玩家投入资金比上地价的比例（考虑上面的buildings）
	const double rate[4] = { 1,1.3,1.7,2.2 };
	while (players[player_id]->get_money() < 0)
	{
		//计算银行要收回的地产id，以及破产者获得的补偿金额（购买价的0.5倍）
		//此处收回地产按照购买顺序，先买先收，后续可改进为玩家自主选择
		int p_id = players[player_id]->lose_property();
		//表示该玩家已彻底破产
		if (p_id == -1)
		{
			string temp = players[player_id]->get_name();
			temp += "因欠债过多，旗下地产也全部被银行收回，无奈宣告破产，从此流落街头...";
			caption_write_r(temp);
			_getch();
			players.erase(players.begin() + player_id);
			if (players.size() == 1)
			{
				count_property();
				closegraph();
				exit(0);
			}
			else if(players.size() == 0)
			{
				string temp = "无人获胜，游戏结束！";
				caption_write_r(temp);
				_getch();
				closegraph();
				exit(0);
			}
			break;
		}
		int call_price = m.get_site(p_id)->get_price() * 0.5 * rate[m.get_site(p_id)->get_status() - 1];
		//设置地产所有者为空
		m.get_site(p_id)->set_status(0);   
		m.get_site(p_id)->set_owner(nullptr);
		//使玩家获得赎回价
		players[player_id]->set_money(call_price);

		string temp = players[player_id]->get_name();
		temp += "因欠债过多，其地产";
		temp += m.get_site(p_id)->get_name();
		temp += "被银行强制收回，并返还其购买价（包括后续建筑物）的一半";
		caption_write_r(temp);
		_getch();
	}
	
}

void take_loans(int player_id)
{
	string temp = "是否选择向银行货款（y/n）";
	caption_write_r(temp);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			
			break;
		}
		else if (c == 'n')
		{
			string temp2 = "您已放弃该次贷款";
			caption_write_r(temp2);
			break;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}


//kind=0表示啥也不干，1表示青年旅舍，2表示宾馆，3表示情侣酒店
void dfw::build_something(shared_ptr<site> s,int player_id,int kind)
{
	if (kind == 0)
		return;

	if (s->get_price() * building_prices[kind - 1] * (-1) > players[player_id]->get_money())
	{
		string temp = "您已没有足够的财力在";
		temp += s->get_name();
		temp += "建造";
		temp += building_names[kind - 1];
		caption_write_r(temp);
		_getch();
		return;
	}

	int building_price = building_prices[kind - 1] * s->get_price();

	string temp = "您拥有现金";
	temp += to_string(players[player_id]->get_money());
	temp += "元，";
	temp += "是否要在";
	temp += "花费";
	temp += to_string(building_price);
	temp += "元在";
	temp += s->get_name();
	temp += "建造";
	temp += building_names[kind - 1];
	temp += "(y/n)";
	caption_write_r(temp);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			string temp2 = players[player_id]->get_name();
			temp2 += "在";
			temp2 += s->get_name();
			temp2 += "上建造了";
			temp2 += building_names[kind - 1];
			caption_write_r(temp2);
			
			s->set_status(kind + 1);
			players[player_id]->set_money(building_price);
			_getch();
			return;
		}
		else if (c == 'n')
		{
			string temp2 = players[player_id]->get_name();
			temp2 += "放弃在";
			temp2 += s->get_name();
			temp2 += "上建造";
			temp2 += building_names[kind - 1];
			caption_write_r(temp2);
			_getch();
			return;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

void init_music()
{
	// 打开音乐
	mciSendString(_T("open background_music_2.mp3 alias mymusic"), NULL, 0, NULL);
	// 播放音乐
	mciSendString(_T("play mymusic"), NULL, 0, NULL);
}