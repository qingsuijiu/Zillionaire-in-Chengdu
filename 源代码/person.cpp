#include "person.h"

bool person::go_steps(int i)
{
	int new_location = (location + i + 30) % 30;
	//当人物是在前进 并且 其新位置标号小于旧位置，可认为其过了起点
	if (i > 0 && new_location < location)
	{
		location = new_location;
		return true;
	}
	else
	{
		location = new_location;
		return false;
	}
}

bool fartman::fart_push()
{
	if (!this->get_skill())
		return false;

	string temp = this->get_name();
	temp += "是否使用技能“臭屁推进”（y/n）";
	caption_write_r(temp);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			//refresh_background();
			string temp2 = this->get_name();
			temp2 += "“噗————”放了个惊天大屁，反冲力让她额外向前一格！不愧是fy的女人！";
			caption_write_r(temp2);
			this->set_skill(false);
			return true;
		}
		else if (c == 'n')
		{
			string temp2 = this->get_name();
			temp2 += "放弃使用技能“臭屁推进”";
			caption_write_r(temp2);
			return false;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

bool fartman::go_steps(int i)
{
	bool is_skill = fart_push();
	if (is_skill)
	{
		while (!_kbhit());
		return person::go_steps(i + 1);
	}
	else
		return person::go_steps(i);
}

int hacker::attack_bank()
{
	if (!this->get_skill())
		return false;

	string temp = this->get_name();
	temp += "是否使用技能“黑入银行”（0:放弃 1:黑500元(成功率80%，失败入狱) 2:黑1000元（40%） 3:黑1500元（26%））";
	caption_write_r(temp);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == '0')
		{
			string temp2 = this->get_name();
			temp2 += "放弃使用技能“黑入银行”";
			caption_write_r(temp2);
			return false;
		}
		else if (c == '1')
		{
			static default_random_engine e(time(0));
			static uniform_int_distribution<size_t> u(1, 100);
			string temp2 = this->get_name();
			if (u(e) <= 80)
			{
				this->set_money(500);
				temp2 += "成功黑入银行，盗走500元";
				caption_write_r(temp2);
				this->set_skill(false);
				return 1;
			}
			else
			{
				temp2 += "攻击失败，被抓入狱";
				caption_write_r(temp2);
				this->set_skill(false);
				return 2;
			}
		}
		else if (c == '2')
		{
			static default_random_engine e(time(0));
			static uniform_int_distribution<size_t> u(1, 100);
			string temp2 = this->get_name();
			if (u(e) <= 40)
			{
				this->set_money(1000);
				temp2 += "成功黑入银行，盗走1000元";
				caption_write_r(temp2);
				this->set_skill(false);
				return 1;
			}
			else
			{
				temp2 += "攻击失败，被抓入狱";
				caption_write_r(temp2);
				this->set_skill(false);
				return 2;
			}

		}
		else if (c == '3')
		{
			static default_random_engine e(time(0));
			static uniform_int_distribution<size_t> u(1, 100);
			string temp2 = this->get_name();
			if (u(e) <= 26)
			{
				this->set_money(1500);
				temp2 += "成功黑入银行，盗走1500元";
				caption_write_r(temp2);
				this->set_skill(false);
				return 1;
			}
			else
			{
				temp2 += "攻击失败，被抓入狱";
				caption_write_r(temp2);
				this->set_skill(false);
				return 2;
			}
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

int hacker::self_land_operations()
{
	int res=attack_bank();
	while (!_kbhit());
	if (res == 0 || res == 1)
		return 0;
	else
		return 1;
}

bool shirtman::throw_shirt()
{
	if (!this->get_skill())
		return false;

	string temp = this->get_name();
	temp += "是否使用技能“乱扔大便”（y/n））";
	caption_write_r(temp);

	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			string temp2 = this->get_name();
			temp2 += "“bia————”在地上乱拉了一坨便便，并在上面盖了些干草让便便不易被发现，坏坏地笑了笑，跑了";
			caption_write_r(temp2);
			this->set_skill(false);
			_getch();
			return 1;
		}
		else if (c == 'n')
		{
			string temp2 = this->get_name();
			temp2 += "放弃使用技能“乱扔大便”";
			caption_write_r(temp2);
			_getch();
			return 0;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

int shirtman::all_land_operations()
{
	bool res = throw_shirt();
	if (res == true)
		return 2;
	else
		return 0;
}

bool cutebaby::act_cute()
{
	string temp = "两位银行总管看到路过起点的";
	temp += this->get_name();
	temp += ",被萌化了！想让你留下来陪他们玩一个回合，是否愿意（y/n）";
	caption_write_r(temp);
	while (1)
	{
		while (!_kbhit());
		char c = _getch();
		if (c == 'y')
		{
			string temp2 = this->get_name();
			temp2 += "决定留下，两位银行总管开心地给了她600元红包!不过下回合她就不能继续旅行了。";
			caption_write_r(temp2);
			this->set_money(+600);
			this->set_pause(true);
			_getch();
			return 1;
		}
		else if (c == 'n')
		{
			string temp2 = this->get_name();
			temp2 += "拒绝了怪阿姨帅叔叔，她今晚就要远航，帅叔叔给了她100元零食费";
			caption_write_r(temp2);
			this->set_money(100);
			_getch();
			return 0;
		}
		else//异常输入的处理
		{
			//caption_write(1, "输入错误，请输入y/n");
		}
	}
}

void cutebaby::reach_starting()
{
	act_cute();
}