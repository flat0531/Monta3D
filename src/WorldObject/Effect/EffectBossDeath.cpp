#include "EffectBossDeath.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DataManager.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
EffectBossDeath::EffectBossDeath()
{
}

EffectBossDeath::EffectBossDeath(const ci::Vec3f _pos, const ci::Vec3f _endscale, const float _time)
{
	t = 0.0f;
	pos = _pos;
	scale = Vec3f(0,0,0);
	endscale = _endscale;
	time = _time;
	color = ColorA(1, randFloat(0.5f, 1.0f), 0.0f, 1.0f);
}

void EffectBossDeath::update()
{
	rotate += ci::Vec3f(0, 5, 0);
	scale.x = EasingCubicOut(t, 0.f, endscale.x);
	scale.y = EasingCubicOut(t, 0.f, endscale.y);
	scale.z = EasingCubicOut(t, 0.f, endscale.z);
	EasingManager::tCount(t, time);
	if (EasingManager::tCountEnd(t))
		CountUp();
}

void EffectBossDeath::draw(const ci::CameraPersp camera)
{
	DrawM.drawSphere(pos, scale, rotate, 12, color);
}

bool EffectBossDeath::deleteThis()
{
	return count > 20;
}
