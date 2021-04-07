#pragma once
#include <vector>
#include <memory>
#include "person.h"
#include "site.h"
#include<memory>
using namespace std;
class dfwmap
{
public:
	dfwmap();
	~dfwmap();
	shared_ptr<site> get_site(int i)
	{
		return sites[i];
	}
	
private:
	vector<shared_ptr<site>> sites;

	void init();
};

