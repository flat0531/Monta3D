#include "SelectAction.h"
#include"../Top/Top.h"
using namespace ci;
using namespace ci::app;
SelectAction::SelectAction()
{
	CreateActionICons();
}

void SelectAction::update()
{
	for (auto& itr : actionaicons) {
		itr.update();
	}
}

void SelectAction::draw()
{
	for (auto itr : actionaicons) {
		itr.draw();
	}
}

void SelectAction::CreateActionICons()
{
	
	std::vector<std::string>names;
	names.push_back("slime");
	names.push_back("slime");
	names.push_back("slime");
	int createnum = names.size();
	//‚æ‚Ý‚±‚Ý
	Vec2f size = Vec2f(115,115);
	for (int i = 0;i < createnum;i++) {
		Vec2f pos = Vec2f(WINDOW_WIDTH/2.f-(((float(createnum-1)) / 2.f)*size.x)+size.x*i,750);
		actionaicons.push_back(ActionIcon(pos, size,names[i], true));
	}
	names.clear();
}
