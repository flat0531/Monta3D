#pragma once
#include<list>
#include<memory>
#include"../WorldObject/Effect/EffectBase.h"
class EffectManager {
public:
	EffectManager();
	void update();
	void draw();
	template<class T>
	void CreateEffect(T effect);
	EffectManager* getThisPointer();
private:
	std::list<std::shared_ptr<EffectBase>>effects;
};

template<class T>
inline void EffectManager::CreateEffect(T effect)
{
	effects.push_back(std::make_shared<T>(effect));
}
