#include"BGMPlayer.h"
using namespace ci;
using namespace ci::app;
BGMPlayer::~BGMPlayer() {
	file_player->disconnectAll();
}
BGMPlayer::BGMPlayer(const std::string name)
{
	ctx = audio::master();
	ctx->enable();
	file_player = ctx->makeNode(new audio::FilePlayerNode());
	{
		std::string path = "Sound/BGM/" + name;
		audio::SourceFileRef source = audio::load(loadAsset(path));
		file_player->setSourceFile(source);
		gain = ctx->makeNode(new audio::GainNode());
		file_player >> gain >> ctx->getOutput();
		file_player->start();
		file_player->setLoopBegin(0);
	}

}

BGMPlayer::BGMPlayer()
{
}

void BGMPlayer::stop()
{
	file_player->stop();
	
}

void BGMPlayer::changeGain(float value)
{
	value = std::max(value, 0.0f);
	value = std::min(value, 1.0f);
	gain->setValue(value);
}

void BGMPlayer::GainDifference(float value)
{
	float now = gain->getValue();
	now += value;
	now = std::max(now, 0.0f);
	float endvalude = std::min(now, 1.0f);
	gain->setValue(endvalude);
}

void BGMPlayer::Play()
{
	file_player->start();
}

void BGMPlayer::PlayGainChanage(float gain)
{
	changeGain(gain);
	file_player->start();
}

void BGMPlayer::SetIsLoop(bool isloop)
{
	file_player->setLoopEnabled(isloop);
}

bool BGMPlayer::GetIsLoop()
{
	return file_player->isLoopEnabled();
}

void BGMPlayer::setLoopBegin(const double begintime)
{
	file_player->setLoopBeginTime(begintime);
}

void BGMPlayer::setLoopEnd(const double endtime)
{
	file_player->setLoopEndTime(endtime);
}

void BGMPlayer::bgmDelete()
{
	
}
