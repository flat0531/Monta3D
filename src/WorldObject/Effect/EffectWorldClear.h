#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectWorldClear : public EffectBase {
public:
	EffectWorldClear();
	EffectWorldClear(int worldnum);
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
		float t = 0.0f;
	};
	std::vector<Blood>bloods;
	ci::gl::Texture name;
	ci::gl::Texture blood;
	ci::Vec2f uppos;
	ci::Vec2f downpos;
	float begin_t = 0.0f;
	bool isend = false;
	void CreateBlood(ci::Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color);
};