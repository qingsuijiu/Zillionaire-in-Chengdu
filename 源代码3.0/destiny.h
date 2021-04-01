#pragma once
#include<string>
#include<vector>
#include<random>
#include<ctime>
using namespace std;
class destiny
{
public:
	destiny(int m_kind,int m_id) :kind(m_kind),id(m_id){}
	destiny(int m_kind);
	~destiny(){}
	void set_id(int i)
	{
		if (i >= 0 && i < contents[0].size())
			id = i;
	}
	string get_content()
	{
		return contents[kind][id];
	}
	int get_money_change()
	{
		return money_changes[kind][id];
	}
	bool is_to_jail()
	{
		if (kind == 0 && id == 0)
			return true;
		return false;
	}
	
private:
	int kind;
	int id;
	//机会命运事件的文字表述
	static vector<vector<string>> contents;  
	//机会命运事件带来的金钱改动
	static vector<vector<int>> money_changes;

};

