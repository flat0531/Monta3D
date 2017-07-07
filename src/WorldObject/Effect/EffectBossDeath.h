#pragma once
#include"EffectBase.h"
class EffectBossDeath : public EffectBase {
public:
	EffectBossDeath();
	EffectBossDeath(const ci::Vec3f _pos, const ci::Vec3f _endscale, const float _time);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	float t;
	float time;
	ci::Vec3f endscale;
	ci::ColorA color;
};
