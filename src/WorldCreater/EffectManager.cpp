#include "EffectManager.h"
#include"../Top/SoundManager.h"
EffectManager::EffectManager()
{
	SoundM.CreateSE("cubecolored.wav");
	SoundM.CreateSE("itemget.wav");
	
}

void EffectManager::update()
{
	for (auto itr = effects.begin();itr != effects.end();) {
		if ((*itr)->deleteThis()) {
			itr = effects.erase(itr);
			continue;
		}
		itr++;
	}
	for (auto itr = effects2d.begin();itr != effects2d.end();) {
		if ((*itr)->deleteThis()) {
			itr = effects2d.erase(itr);
			continue;
		}
		itr++;
	}
	for (auto itr : effects) {
		itr->update();
	}
	for (auto itr : effects2d) {
		itr->update();
	}
}

void EffectManager::draw(const ci::CameraPersp camera)
{
	for (auto itr : effects) {
		itr->draw(camera);
	}
}


void EffectManager::draw2D(const ci::CameraPersp camera)
{
	for (auto itr : effects2d) {
		itr->draw(camera);
	}
}

EffectManager * EffectManager::getThisPointer()
{
	return this;
}
