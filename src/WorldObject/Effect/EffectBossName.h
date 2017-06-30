
#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectBossName : public EffectBase {
public:
	EffectBossName();
	EffectBossName(const std::string path);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	struct Blood
	{
		ci::Vec2f pos;
		ci::Vec2f size;
		float rotate;
		ci::ColorA color;
	};
	std::vector<Blood>bloods;
	ci::gl::Texture name;
	ci::gl::Texture blood;
	float t[5];
	float alpha[5];
	bool isend = false;
	void CreateBlood(ci:: Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color);
};
