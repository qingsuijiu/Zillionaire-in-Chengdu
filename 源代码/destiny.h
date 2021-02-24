#pragma once
#include<string>
#include<vector>
#include<random>
#include<ctime>
using namespace std;
class destiny
{
public:
	destiny(int m_id) :id(m_id){}
	destiny();
	~destiny(){}
	void set_id(int i)
	{
		if (i >= 0 && i < contents.size())
			id = i;
	}
	string get_content()
	{
		return contents[id];
	}
	int get_money_change()
	{
		return money_changes[id];
	}
	bool is_to_jail()
	{
		if (id == 0)
			return true;
		return false;
	}
	
private:
	int id;
	
	//string content;
	//int money_change;
	static vector<string> contents;
	static vector<int> money_changes;
};

