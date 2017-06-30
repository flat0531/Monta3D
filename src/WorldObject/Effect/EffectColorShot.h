#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectColorShot: public EffectBase {
public:
	EffectColorShot();
	EffectColorShot(const ci::Vec3f scale);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	struct Blood
	{
		ci::Vec2f pos;
		ci::Vec2f beginpos;
		ci::Vec2f size;
		float rotate;
		ci::ColorA color;
	};
	std::vector<Blood>bloods;
	ci::gl::Texture blood;
	bool isend = false;
	float begin_alpha_t = 0.0f;
	float end_alpha_t = 0.0f;
	float color_alfa;
	void CreateBlood(ci::Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color);
};