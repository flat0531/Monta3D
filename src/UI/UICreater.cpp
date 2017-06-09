#include "UICreater.h"
#include"../Top/MyJson.h"
using namespace ci;
using namespace ci::app;
UICretaer::UICretaer()
{
}

void UICretaer::CreateUI(const std::string path)
{
	uiobjects.clear();
	JsonTree loadjson(loadAsset(path));
	for (int i = 0;i < loadjson.getNumChildren();i++) {
		uiobjects.push_back(UIObject(loadjson.getChild(i)));
	}

}

void UICretaer::draw()
{
	for (auto it : uiobjects) {
		it.draw();
	}
}
