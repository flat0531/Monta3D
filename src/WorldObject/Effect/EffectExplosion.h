#pragma once
#include"EffectBase.h"
class EffectExplosion : public EffectBase{
public:
	EffectExplosion();
	EffectExplosion(const ci::Vec3f _pos,const ci::Vec3f _scale,const ci::Vec3f _rotate);
	void update() override;
	void draw() override;
	bool deleteThis()override;
private:
	float t;
	ci::Vec3f endscale;
};