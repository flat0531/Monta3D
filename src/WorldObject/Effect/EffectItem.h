#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectItem : public EffectBase {
public:
	EffectItem();
	EffectItem(const ci::Vec2f _pos, const ci::Vec2f _endpos, const ci::Vec2f _scale);
	void update() override;
	void draw() override;
	bool deleteThis()override;
private:
	struct Particle
	{
		ci::Vec2f beginpos;
		ci::Vec2f endpos;
		ci::Vec2f pos;
		ci::Vec2f scale;
		float t;
		ci::ColorA color;
		EasingManager::EasType easingtype_x;
		EasingManager::EasType easingtype_y;
	};
	float t = 0.0f;
	std::vector<Particle>particles;
	ci::Vec2f beginpos;
	ci::Vec2f endpos;
	ci::gl::Texture icontex;
	ci::gl::Texture itemeffecttex;
	void CreateParticles();
	EasingManager::EasType RandEas();
};
