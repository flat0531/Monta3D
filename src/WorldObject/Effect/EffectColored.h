#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectColored : public EffectBase {
public:
	EffectColored();
	EffectColored(const ci::Vec3f _pos, const ci::Vec3f _scale,ci::Color color);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	struct Particle
	{
		ci::Vec2f pos;
		ci::Vec2f scale;
		float t;
		float sinangle;
		float beginangle;
		ci::ColorA color;
	};
	ci::Vec3f objpos;
	ci::Vec3f objsize;
	std::vector<Particle>particles;
	ci::gl::Texture colortex;
};
