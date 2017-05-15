#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"
class BGMPlayer {
private:
	ci::audio::FilePlayerNodeRef file_player;
	ci::audio::GainNodeRef gain;
	ci::audio::Context* ctx;
public:
	BGMPlayer::~BGMPlayer();
	BGMPlayer::BGMPlayer(const std::string name);
	BGMPlayer::BGMPlayer();
	void stop();
	void changeGain(float value);
	void GainDifference(float value);
	void Play();
	void PlayGainChanage(float gain);
	void SetIsLoop(const bool isloop);
	bool GetIsLoop();
	void setLoopBegin(const double begintime);
	void setLoopEnd(const double endtime);
	void bgmDelete();
};