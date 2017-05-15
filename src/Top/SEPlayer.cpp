#include "SEPlayer.h"
using namespace ci;
using namespace ci::app;
SEPlayer::~SEPlayer()
{
	//buf_player->stop();
	buf_player->disconnectAll();
}

SEPlayer::SEPlayer(const std::string name)
{
	ctx = audio::master();
	ctx->enable();
	buf_player = ctx->makeNode(new audio::BufferPlayerNode());
	{
		std::string path = "Sound/SE/" + name;
		audio::SourceFileRef source = audio::load(loadAsset(path));
		buf_player->loadBuffer(source);
		gain = ctx->makeNode(new audio::GainNode());
		buf_player >> gain >> ctx->getOutput();
		//buf_player->start();
	}
}

SEPlayer::SEPlayer()
{
}

void SEPlayer::stop()
{
	buf_player->stop();
}

void SEPlayer::changeGain(float value)
{
	value = std::max(value, 0.0f);
	value = std::min(value, 1.0f);
	gain->setValue(value);
}

void SEPlayer::GainDifference(float value)
{
	float now = gain->getValue();
	now += value;
	now = std::max(now, 0.0f);
	float endvalude = std::min(now, 1.0f);
	gain->setValue(endvalude);
}

void SEPlayer::Play()
{
	buf_player->start();
}

void SEPlayer::PlayGainChanage(float gain)
{
	changeGain(gain);
	buf_player->start();
}

void SEPlayer::SetIsLoop(const bool isloop)
{
	buf_player->setLoopEnabled(isloop);
}

bool SEPlayer::GetIsLoop()
{
	return buf_player->isLoopEnabled();
}

void SEPlayer::bgmDelete()
{
}
