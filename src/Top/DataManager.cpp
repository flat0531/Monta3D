#include "DataManager.h"
#include"MyJson.h"
#include"cinder/ImageIo.h"
#include"cinder\Surface.h"
#include <filesystem>
#include"TextureManager.h"
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
	if (child.hasChild("getitem")) {
		JsonTree gchild = child.getChild("getitem");
		for (int i = 0;i < gchild.getNumChildren();i++) {
			bool isget = gchild.getValueAtIndex<bool>(i);
			getitems.push_back(isget);
		}
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

void DataManager::WriteImage(const Surface surface, const std::string name)
{
	int createnum = 0;
	for (std::tr2::sys::directory_iterator it(app::getAssetPath("Texture/UserPlay/" + name).string()), end; it != end; it++)
	{
		createnum++;
	}
	std::string path = "assets/Texture/UserPlay/" + name + "/play" + std::to_string(createnum+1)+".png";

	auto datasourceref = DataTargetPath::createRef(getAppPath().string() + path);

	ci::writeImage(datasourceref, surface);
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

std::string DataManager::getSelectActionName()
{
	return selectactionname;
}

void DataManager::setSelectActionName(const std::string name)
{
	selectactionname = name;
}

ActionType DataManager::stringToActionType(const std::string name)
{
	if (name == "slime") {
		return ActionType::SLIME;
	}
	if (name == "cat") {
		return ActionType::CAT;
	}
	if (name == "bird") {
		return ActionType::BIRD;
	}
	if (name == "angel") {
		return ActionType::ENJEL;
	}
	if (name == "mogura") {
		return ActionType::MOGURA;
	}
	if (name == "ratton") {
		return ActionType::RATTON;
	}
	if (name == "witch") {
		return ActionType::WITCH;
	}
	if (name == "sparrow") {
		return ActionType::SPARROW;
	}
	if (name == "ghost") {
		return ActionType::GHOST;
	}
	if (name == "pumpman") {
		return ActionType::PUMPMAN;
	}
	if (name == "walkratton") {
		return ActionType::WALKRATTON;
	}
	if (name == "PumpkyDumpty") {
		return ActionType::BIGPUMPKIN;
	}
	console() << "ƒoƒO‚Å‚·" << std::endl;
	return ActionType::RATTON;
}

bool DataManager::getIsTutorial(const std::string name)
{
	std::string path = "SaveData/Tutorial/tutorial.json";
	JsonTree tutorial(loadAsset(path));
	for (int i = 0;i < tutorial.getNumChildren();i++) {
		if (tutorial.getChild(i).getValueForKey<std::string>("name") == name) {

			return tutorial.getChild(i).getValueForKey<bool>("clear");
		}
	}

	return false;
}

void DataManager::saveIsTutorial(const std::string name)
{
	std::string path = "SaveData/Tutorial/tutorial.json";
	JsonTree tutorial(loadAsset(path));
	for (int i = 0;i < tutorial.getNumChildren();i++) {
		JsonTree child = tutorial.getChild(i);
		if (child.getValueForKey<std::string>("name") == name)
		{
			tutorial.getChild(i).getChild("clear") = JsonTree("clear", true);
		}
	}
	tutorial.write(getAssetPath(path).string());
}

ci::gl::Texture DataManager::getLastSaveTexture(const std::string name)
{
	int createnum = 0;
	for (std::tr2::sys::directory_iterator it(app::getAssetPath("Texture/UserPlay/" + name).string()), end; it != end; it++)
	{
		createnum++;
	}
	std::string path = "UserPlay/" + name + "/play" + std::to_string(createnum) + ".png";
	return TextureM.CreateTexture(path);
}

void DataManager::setPlayTextureStatus(const ci::Surface surface)
{
	float r_rate = 0.0f;
	float g_rate = 0.0f;
	float b_rate = 0.0f;
	float a_rate = 0.0f;
	float max = surface.getSize().x*surface.getSize().y;
	float half = max / 2.f;
	for (int y = 0; y <surface.getSize().y; y++)
	{
		for (int x = 0; x < surface.getSize().x; x++)
		{
			int r = surface.getPixel(Vec2i(x, y)).r;
			int g = surface.getPixel(Vec2i(x, y)).g;
			int b = surface.getPixel(Vec2i(x, y)).b;
			int a = surface.getPixel(Vec2i(x, y)).a;
		
			if (r == g&&g == b) {
				a_rate++;
				continue;
			}
			if (r > g&&r > b) {
				r_rate++;
				continue;
			}
			if (g > r&&g > b) {
				g_rate++;
				continue;
			}
			if (b > r&&b > g) {
				b_rate++;
				continue;
			}
			if (r == g&&r > b) {
				r_rate += 0.5f;
				g_rate += 0.5f;
				continue;
			}
			if (r == b&&r > g) {
				r_rate += 0.5f;
				b_rate += 0.5f;
				continue;
			}
			if (g == b&&g > r) {
				g_rate += 0.5f;
				b_rate += 0.5f;
				continue;
			}
			
		}
	}

	float r_value = 0.7f*std::min(r_rate / half, 1.0f) + 0.3f*std::min(1.5f*( a_rate / half), 1.0f);
	float g_value = 0.7f*std::min(g_rate / half, 1.0f) + 0.3f*std::min(1.5f*(a_rate / half), 1.0f);
	float b_value = 0.7f*std::min(b_rate / half, 1.0f) + 0.3f*std::min(1.5f*(a_rate / half), 1.0f);

	play_power_rate = r_value;
	play_speed_rate = g_value;
	play_defense_rate = b_value;
}

ci::Vec3i DataManager::getBaseStatus(std::string name)
{
	ActionType  type = stringToActionType(name);

	switch (type)
	{
	case SLIME:
		return Vec3i(4, 3, 2);
	case CAT:
		return Vec3i(5, 3, 4);
	case BIRD:
		return Vec3i(3, 1, 5);
	case ENJEL:
		return Vec3i(2, 1, 5);
	case MOGURA:
		return Vec3i(2, 5, 2);
	}

	return ci::Vec3i(1, 1, 1);
}



float DataManager::getPlayPowerRate()
{
	return play_power_rate;
}

float DataManager::getPlayDefenseRate()
{
	return play_defense_rate;
}

float DataManager::getPlaySpeedRate()
{
	return play_speed_rate;
}
