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
	for (auto itr : effects) {
		itr->update();
	}
}

void EffectManager::draw()
{
	for (auto itr : effects) {
		itr->draw();
	}
}

EffectManager * EffectManager::getThisPointer()
{
	return this;
}
