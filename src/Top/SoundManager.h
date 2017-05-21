#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"
#include"BGMPlayer.h"
#include"SEPlayer.h"
#include<vector>
#include<unordered_map>
#include<map>
class SoundManager{
public:
	static SoundManager& getSound() {
		static SoundManager sound;
		return sound;
	}
	SoundManager::SoundManager();
	void updateGainFadeT();
	void PlayBGM(const std::string name, float gain = 0.3f);
	void StopBGM(const std::string name);
	void StopNowBGM();
	void GainBGM(const std::string name, const float value);
	void GainBGMDifference(const std::string name, const float value);
	void SetLoopBGM(const std::string name, bool isloop);
	bool GetLoopBGM(const std::string name);
	void SetBeginLoopBGM(const std::string name, const double begintime);
	void SetEndLoopBGM(const std::string name, const double endtime);
	void SetLoopTimeBGM(const std::string name, const double begintime, const double endtime);
	float getBGMGain(const std::string name);
	void eraseBGM(const std::string name);
	std::string getNowPlayBGMString();

	void PlaySE(const std::string name, float gain = 1.0f);
	void StopSE(const std::string name);
	void GainSE(const std::string name, const float value);
	void GainSEDifference(const std::string name, const float value);
	void SetLoopSE(const std::string name, bool isloop);
	bool GetLoopSE(const std::string name);
	void eraseSE(const std::string name);
	void CreateSE(const std::string name);
	void FadeNowBGM(float _endgain,float _fadetime, const bool isenderace = true);
	float getPlayStartGain();
private:
	std::string nowplaybgmname = "";
	std::map<std::string, BGMPlayer> bgmmap;
	std::map<std::string, SEPlayer> semap;
	float fade_t = 1.0f;
	float fadetime = 1.0f;
	bool isfading = false;
	float begingain;
	float endgain;
	bool iserace = false;
	float playstartgain = 0.0f;
};
#define SoundM (SoundManager::getSound().getSound())