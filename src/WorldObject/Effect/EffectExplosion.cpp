#include "EffectExplosion.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
EffectExplosion::EffectExplosion()
{
}

EffectExplosion::EffectExplosion(const ci::Vec3f _pos, const ci::Vec3f _scale, const ci::Vec3f _rotate)
{
	pos = _pos;
	endscale = _scale;
	rotate = _rotate;
	t = 0.0f;
}

void EffectExplosion::update()
{
	rotate += ci::Vec3f(0,5,0);
	scale.x = EasingBackOut(t, 0.f, endscale.x);
	scale.y = EasingBackOut(t, 0.f, endscale.y);
	scale.z = EasingBackOut(t, 0.f, endscale.z);
	EasingManager::tCount(t,0.5f);
	if(EasingManager::tCountEnd(t))
	CountUp();
}

void EffectExplosion::draw(const ci::CameraPersp camera)
{
	DrawM.drawSphere(pos, scale, rotate, 12, ci::ColorA(1, 0.5, 0, 1));
}

bool EffectExplosion::deleteThis()
{
	return count > 30;
}
