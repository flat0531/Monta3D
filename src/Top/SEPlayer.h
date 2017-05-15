#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/audio/Context.h"
#include "cinder/audio/GainNode.h"
#include "cinder/audio/SamplePlayerNode.h"
class SEPlayer {
private:
	ci::audio::FilePlayerNodeRef file_player;
	ci::audio::BufferPlayerNodeRef buf_player;
	ci::audio::GainNodeRef gain;
	ci::audio::Context* ctx;
public:
	SEPlayer::~SEPlayer();
	SEPlayer::SEPlayer(const std::string name);
	SEPlayer::SEPlayer();
	void stop();
	void changeGain(float value);
	void GainDifference(float value);
	void Play();
	void PlayGainChanage(float gain);
	void SetIsLoop(const bool isloop);
	bool GetIsLoop();
	void bgmDelete();
};