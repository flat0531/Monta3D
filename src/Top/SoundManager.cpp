#include"SoundManager.h"
#include "MyJson.h"
using namespace ci;
using namespace ci::app;




SoundManager::SoundManager()
{

}


void SoundManager::PlayBGM(const std::string name, float gain)
{
	if (bgmmap.find(name) == bgmmap.end()) {
		bgmmap.insert(std::make_pair(name, name));
		bgmmap[name].changeGain(gain);
	}
	else {
		bgmmap[name].PlayGainChanage(gain);
	}

}

void SoundManager::StopBGM(std::string name)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].stop();
	}

}

void SoundManager::GainBGM(std::string name, float value)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].changeGain(value);
	}

}

void SoundManager::GainBGMDifference(std::string name, float value)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].GainDifference(value);
	}
}

void SoundManager::SetLoopBGM(const std::string name, bool isloop)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].SetIsLoop(isloop);
	}
}

bool SoundManager::GetLoopBGM(const std::string name)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		return bgmmap[name].GetIsLoop();
	}
	return false;
}

void SoundManager::SetBeginLoopBGM(const std::string name, const double begintime)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].setLoopBegin(begintime);
	}
}

void SoundManager::SetEndLoopBGM(const std::string name, const double endtime)
{
	if (bgmmap.find(name) != bgmmap.end()) {
		bgmmap[name].setLoopEnd(endtime);
	}
}

void SoundManager::SetLoopTimeBGM(const std::string name, const double begintime, const double endtime)
{
	//std::string name_ = name;
	auto it = bgmmap.find(name);
	if (it != bgmmap.end()) {
		it->second.setLoopBegin(begintime);
		it->second.setLoopEnd(endtime);
		it->second.SetIsLoop(true);
	}
}

void SoundManager::eraseBGM(const std::string name)
{
	auto it = bgmmap.find(name);
	if (it == bgmmap.end()) {

	}
	else {
		it->second.stop();
		bgmmap.erase(it);
	}
}


/////////////////////////////////////////////////////////////
void SoundManager::PlaySE(const std::string name, float gain)
{
	if (semap.find(name) == semap.end()) {
	}
	else {
		semap[name].PlayGainChanage(gain);
	}
}

void SoundManager::StopSE(const std::string name)
{
	if (semap.find(name) != semap.end()) {
		semap[name].stop();
	}
}

void SoundManager::GainSE(const std::string name, const float value)
{
	if (semap.find(name) != semap.end()) {
		semap[name].changeGain(value);
	}
}

void SoundManager::GainSEDifference(const std::string name, const float value)
{
	if (semap.find(name) != semap.end()) {
		semap[name].GainDifference(value);
	}
}

void SoundManager::SetLoopSE(const std::string name, bool isloop)
{
	if (semap.find(name) != semap.end()) {
		semap[name].SetIsLoop(isloop);
	}
}

bool SoundManager::GetLoopSE(const std::string name)
{
	if (semap.find(name) != semap.end()) {
		return semap[name].GetIsLoop();
	}
	return false;
}

void SoundManager::eraseSE(const std::string name)
{
	auto it = semap.find(name);
	if (it == semap.end()) {

	}
	else {
		it->second.stop();
		semap.erase(it);
	}
}

void SoundManager::CreateSE(const std::string name)
{
	if (semap.find(name) == semap.end()) {
		semap.insert(std::make_pair(name, name));
	}
	else {

	}
}
