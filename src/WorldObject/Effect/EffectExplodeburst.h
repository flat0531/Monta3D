#pragma once
#include"EffectBase.h"
class EffectExplodeburst : public EffectBase {
public:
	EffectExplodeburst();
	EffectExplodeburst(const ci::Vec3f _pos, const ci::Vec3f _scale, const ci::Vec3f _rotate,
		const ci::ColorA _color,float _easingtime);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	struct BurstCube
	{
		ci::Vec3f trancepos;
		ci::Vec3f endpos;
		ci::Vec3f scale;
		ci::Vec3f rotate;
		ci::Vec3f rotatespeed;
	};
	std::vector<BurstCube> cubes;
	ci::Vec3f endtrancepos(int i);
	float t;
	ci::Vec3f endscale;
	ci::Vec3f beginscale;
	ci::ColorA color;
    float easingtime;
};