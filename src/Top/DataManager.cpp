#include "DataManager.h"

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
