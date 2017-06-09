#include "DataManager.h"
#include"MyJson.h"
using namespace ci;
using namespace ci::app;
DataManager::DataManager()
{
}

int DataManager::getWorldNum()
{
	return worldnum;
}

int DataManager::getStageNum()
{
	return stagenum;
}

std::string DataManager::getStageName()
{
	return stagename;
}

void DataManager::ReadNowData()
{
}

void DataManager::setWorldNum(const int _worldnum)
{
	worldnum = _worldnum;
}

void DataManager::setStageNum(const int _stagenum)
{
	stagenum = _stagenum;
}

void DataManager::setStageName(const std::string _stagename)
{
	stagename = _stagename;
}

SceneType DataManager::getPrevscene()
{
	return prevscene;
}

SceneType DataManager::getNextscene()
{
	return nextscene;
}

void DataManager::setPrevScene(const SceneType _prevscene)
{
	prevscene = _prevscene;
}

void DataManager::setNextScene(const SceneType _nextscene)
{
	nextscene = _nextscene;
}

void DataManager::releaseCharacter(const std::string name, const std::string type, const bool is)
{
	std::string path = "SaveData/Folm/releasefolm.json";
	JsonTree folm(loadAsset(path));
	for (int i = 0;i < folm.getNumChildren();i++) {
		JsonTree child = folm.getChild(i);
		if (child.getValueForKey<std::string>("name") == name)
		{
			folm.getChild(i).getChild(type) = JsonTree(type, is);
		}
	}
	folm.write(getAssetPath(path).string());
}

void DataManager::roadGetItems(int worldnum, int stagenum)
{
	getitems.clear();
	std::string path = "SaveData/StageSelect/World" + std::to_string(worldnum) + "/save.json";
	JsonTree item(loadAsset(path));
	JsonTree child = item.getChild(stagenum - 1);
	JsonTree gchild = child.getChild("getitem");
	for (int i = 0;i < gchild.getNumChildren();i++) {
		bool isget = gchild.getValueAtIndex<bool>(i);
		getitems.push_back(isget);
	}
}

void DataManager::saveGetItems(int worldnum, int stagenum, std::vector<bool> _getitems)
{
	std::string path = "SaveData/StageSelect/World" + std::to_string(worldnum) + "/save.json";
	JsonTree item(loadAsset(path));
	JsonTree child;
	JsonTree save = child.makeArray("getitem");
	for (int i = 0;i < _getitems.size();i++) {
		save.pushBack(JsonTree("",_getitems[i]));
	}
	item.getChild(stagenum - 1).getChild("getitem") = save;
	item.write(getAssetPath(path).string());
}

void DataManager::saveStageData(int worldnum, int stagenum, bool is)
{
	std::string path = "SaveData/StageSelect/World" + std::to_string(worldnum) + "/save.json";
	JsonTree item(loadAsset(path));
	item.getChild(stagenum - 1).getChild("isclear") = JsonTree("isclear", is);
	item.write(getAssetPath(path).string());
}

void DataManager::saveColorRelease(const std::string name, const bool is)
{
	std::string path = "SaveData/Color/releasecolor.json";
	JsonTree color(loadAsset(path));
	for (int i = 0;i < color.getNumChildren();i++) {
		JsonTree child = color.getChild(i);
		if (child.getValueForKey<std::string>("name") == name)
		{
			color.getChild(i).getChild("release") = JsonTree("release", is);
		}
	}
	color.write(getAssetPath(path).string());
}

bool DataManager::isCheckFolm(const std::string name, const std::string type)
{
	std::string path = "SaveData/Folm/releasefolm.json";
	JsonTree folm(loadAsset(path));
	for (int i = 0;i < folm.getNumChildren();i++) {

		JsonTree child = folm.getChild(i);
		if (child.getValueForKey<std::string>("name")==name) {
			return child.getValueForKey<bool>(type);
		}
		else {
			continue;
		}
	}
	return false;
}

ci::ColorA DataManager::getColor(const std::string name)
{
	std::string path = "SaveData/Color/releasecolor.json";
	JsonTree color(loadAsset(path));
	for (int i = 0;i < color.getNumChildren();i++) {
		if (color.getChild(i).getValueForKey<std::string>("name") == name) {
			float color_r = color.getChild(i).getChild("color").getValueAtIndex<float>(0) / 255.f;
			float color_g = color.getChild(i).getChild("color").getValueAtIndex<float>(1) / 255.f;
			float color_b = color.getChild(i).getChild("color").getValueAtIndex<float>(2) / 255.f;
			return ColorA(color_r, color_g, color_b, 1.0f);
		}
	}

	return ColorA(1, 1, 1, 1);
}

std::vector<bool> DataManager::getItems()
{
	return getitems;
}

std::vector<bool> DataManager::diffGetItems()
{
	std::vector<bool>buff = getitems;
	roadGetItems(worldnum,stagenum);
	std::vector<bool>diff;
	for (int i = 0;i < getitems.size();i++) {
		diff.push_back(!(buff[i] == getitems[i]));
	}
	return diff;
}
