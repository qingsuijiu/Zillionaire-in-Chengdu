#include "destiny.h"

vector<string> destiny::contents = {"rua小孩子噶堆，被判猥亵，送入监狱，并罚款300元",
									"买草莓多多奶茶，花去100元",
									"吃九宫格火锅，花去300元",
									"你被评为“年度好噶堆”，获得奖金600元",
									"打响嗝比赛中获得第二名，获得奖金500元",
									"买泡泡码特，花去100元",
									"泡泡玛特开出超级稀有款，竞拍卖出获得800元",
									"双11买byt花去200元",
									"收到快递着火短信，被诈骗200元",
									"写的人物通讯获得稿费300元",
									"微博抽奖获得200元",
									"饭卡弄丢损失100元"};
vector<int> destiny::money_changes = {-300,-100,-300,600,500,-100,800,-200,-200,300,200,-100};


destiny::destiny()
{
	static default_random_engine e(time(0));
	static uniform_int_distribution<int> u(0,contents.size()-1);
	id = u(e);
}