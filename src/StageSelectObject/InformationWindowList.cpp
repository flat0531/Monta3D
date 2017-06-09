#include "InformationWindowList.h"
#include"../Top/DataManager.h"
#include"../Top/SoundManager.h"
InformationWindowList::InformationWindowList()
{
	
}


void InformationWindowList::update()
{
	if (isEnd())return;
	informationwindows[0]->update();
	if (informationwindows[0]->isDelete()) {
		informationwindows.erase(informationwindows.begin());
	}
}

void InformationWindowList::draw()
{
	if (isEnd())return;
	informationwindows[0]->draw();
}

bool InformationWindowList::isEnd()
{
	return informationwindows.size() == 0;
}

void InformationWindowList::CreateInformationWindows()
{
	SoundM.CreateSE("itemwindow.wav");
	SoundM.CreateSE("close.wav");
	std::vector<bool> list = DataM.diffGetItems();
	for (int i = 0;i < list.size();i++) {
		if (list[i]) {
			informationwindows.push_back(std::make_shared<InformationWindow>
				(DataM.getWorldNum(), DataM.getStageNum(), i));
		}
	}
}
