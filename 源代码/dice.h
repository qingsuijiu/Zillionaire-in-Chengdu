#pragma once
#include<graphics.h>
#include<conio.h>
#include<map>
#include<random>
#include<ctime>
using namespace std;
class dice
{
public:
	dice();
	~dice() {};
	IMAGE* get_image(int i)
	{
		if (i == 0)
			return &dice_t;
		else if (i >= 1 && i <= 6)
			return &point[i];
		else
			return nullptr;  //¿ÉÑ¡ÔñÅ×Òì³£
	}
	pair<size_t, size_t> get_xy(bool is_t)
	{
		if (is_t)
			return location_t;
		else
			return location_p;
	}
	size_t throw_dice();
private:
	IMAGE dice_t;
	map<size_t, IMAGE> point;
	pair<size_t , size_t> location_t;
	pair<size_t, size_t> location_p;

};

