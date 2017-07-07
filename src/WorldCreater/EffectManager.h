#pragma once
#include<list>
#include<memory>
#include"../WorldObject/Effect/EffectBase.h"
class EffectManager {
public:
	EffectManager();
	void update();
	void draw(const ci::CameraPersp camera);
	void draw2D(const ci::CameraPersp camera);
	template<class T>
	void CreateEffect(T effect);
	template<class T>
	void CreateEffect2D(T effect);
	EffectManager* getThisPointer();
	void clearEffects();
private:
	std::list<std::shared_ptr<EffectBase>>effects;
	std::list<std::shared_ptr<EffectBase>>effects2d;
	void createAsset();
};
/////�RD�p�̃G�t�F�N�g�𐶐�
template<class T>
inline void EffectManager::CreateEffect(T effect)
{
	effects.push_back(std::make_shared<T>(effect));
}
/////�QD�p�̃G�t�F�N�g�𐶐�
template<class T>
inline void EffectManager::CreateEffect2D(T effect)
{
	effects2d.push_back(std::make_shared<T>(effect));
}
