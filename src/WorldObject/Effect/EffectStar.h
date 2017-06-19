#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectStar : public EffectBase {
public:
	EffectStar();
	EffectStar(const ci::Vec3f _pos, const ci::Vec3f _scale, ci::Color color);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	struct Particle
	{
		ci::Vec2f pos;
		ci::Vec2f scale;
		float t[3];
		float sinangle;
		float length;
		float rotate;
		ci::ColorA color;
	};
	ci::Vec3f objpos;
	ci::Vec3f objsize;
	float z = 1.0f;
	float scale_t = 0.0f;
	float scalerate = 0.0f;
	std::vector<Particle>particles;
	ci::gl::Texture colortex;
};
