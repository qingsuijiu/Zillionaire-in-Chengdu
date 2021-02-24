#include "dfwmap.h"


/*
起点 青羊宫 杜甫草堂 机会 武侯祠 双流机场 命运 放屁税 宽窄巷子 牢狱
成都欢乐谷 四川大学 春熙路 机会熊猫基地 免费停车场
都江堰 九眼桥 命运 东郊记忆 打嗝税 成都东火车站 机会 青城山 进牢
海洋公园 西南民族大学 建设路 命运 太古里
*/

void dfwmap::init()
{
	for (int i = 0; i < 30; i++)
	{
		shared_ptr<site> temp = make_shared<site>(i);
		sites.emplace_back(temp);
	}
	sites[0]->set_status(-4);
	sites[9]->set_status(-4);
	sites[15]->set_status(-4);
	sites[24]->set_status(-5);
	sites[7]->set_status(-1);
	sites[20]->set_status(-1);
	sites[3]->set_status(-2);
	sites[13]->set_status(-2);
	sites[22]->set_status(-2);
	sites[6]->set_status(-3);
	sites[18]->set_status(-3);
	sites[28]->set_status(-3);
}

dfwmap::dfwmap()
{
	init();
}

dfwmap::~dfwmap()
{}