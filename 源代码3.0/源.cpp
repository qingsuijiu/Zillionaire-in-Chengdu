#include <graphics.h>		// 引用图形库头文件
#include <conio.h>
#include<stdlib.h>
#include <iostream>
#include"dfw.h"
#include"setting.h"

using namespace std;
int main()
{
	
	setting m_setting;
	m_setting.setting_main();

	dfw game(m_setting.get_kinds(), {}, {}, m_setting.get_round(),m_setting.get_start_money());
	//dfw game({ 5 }, {}, {}, 20, 10000);
	game.dfw_main();
	
	// 按任意键退出
	_getch();
	closegraph();
	return 0;
	




	/*
	map m;
	int i=m.get_site(0)->get_price();
	cout << i;

	i = m.get_site(1)->get_price();
	cout << i;

	
		// 绘图窗口初始化
		initgraph(1280*0.7, 852*0.7);

		IMAGE img,background;
		// 读取图片至绘图窗口
		loadimage(&img, _T("cartoon_fy.png"));
		loadimage(&background, _T("dfw_map.png"));
		for (int i = 0; i < 20; i++)
		{
			putimage( 0, 0,&background);
			putimage(100, 100 + 10 * i, &img);
			Sleep(100);
		}

		// 按任意键退出
		_getch();
		closegraph();
	*/
}


/*
开发笔记

基础扩展
	四个人物的加入:
		屁宝羊崽   √
		黑客fy  √
		屎宝樊人精  √
		萌宝洋芋  √
	两所大学、机场、火车站的过路费重新设计
	机会命运的入狱机制（现在只会改变人物金钱）  √
	破产系统的开发  √
	贷款系统的开发
	建青年旅舍、宾馆、情侣酒店功能的实现  √
	实现由用户控制的人物选择、最大回合数、起始资金  √
	加入机器人玩家，数量也由用户控制
	更多有趣的机会命运加入
	机会命运的随机化  √

进阶扩展
	加入泡泡玛特抽盲盒机制（可能通过设计一个新人物用她的技能实现） √
	更多有趣彩蛋，有趣人物
	推出皮肤系统
	任务系统
	联机联网（得等我下学期学完网络）

美工拓展
	地图重新设计（缺画师，现在的有点丑）  完成一次优化，增加右边的对话框
	调优背景音乐，加各种音效 

bug修复
	金钱变成很大的负数  ？（试验时未发现）

*/



/*
人物简介：
屁宝羊崽：技能臭屁推进，扔完骰子后，可以选择放屁将自己朝前方额外推进一格；
黑客fy：技能攻击银行，在自己的地产上，可以发动对银行的远程网络攻击，成功盗得金钱，失败锒铛入狱；
屎宝樊人精：技能乱扔粑粑，可以在地上乱扔一坨粑粑，其他玩家路过该地会踩中，踩中者可选择洗掉或吃掉；
萌宝洋芋：技能可爱撒娇，在路过起点时，可以留下来陪银行管家玩一回合，赚取零花钱
所有人物的技能会在使用后陷入冷却，在路过起点时刷新技能。
*/