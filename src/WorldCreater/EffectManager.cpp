#include "EffectManager.h"

EffectManager::EffectManager()
{

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

void EffectManager::draw()
{
	for (auto itr : effects) {
		itr->draw();
	}
}

void EffectManager::draw2D()
{
	for (auto itr : effects2d) {
		itr->draw();
	}
}

EffectManager * EffectManager::getThisPointer()
{
	return this;
}
