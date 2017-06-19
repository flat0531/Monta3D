#include "EffectExplodeburst.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
EffectExplodeburst::EffectExplodeburst()
{
}

EffectExplodeburst::EffectExplodeburst(const ci::Vec3f _pos, const ci::Vec3f _scale, const ci::Vec3f _rotate, const ci::ColorA _color, float _easingtime)
{
	pos = _pos;
	t = 0.0f;
	beginscale= _scale*0.15f;
	endscale = _scale*0.3f;
	easingtime = _easingtime;
	color = _color;
	for (int i = 0;i < 8;i++) {
		BurstCube buff;
		buff.trancepos = Vec3f(0, 0, 0);
		buff.scale = Vec3f(0, 0, 0);
		buff.rotate = Vec3f(0, 0, 0);
		buff.rotatespeed = Vec3f(15,15,15);
		buff.endpos = endtrancepos(i)*WorldScale / 2.f;
		cubes.push_back(BurstCube(buff));
	}

}

void EffectExplodeburst::update()
{
	for (int i = 0;i < cubes.size();i++) {
		cubes[i].trancepos.x = EasingCircOut(t, 0.f, cubes[i].endpos.x);
		cubes[i].trancepos.y = EasingCircOut(t, 0.f, cubes[i].endpos.y);
		cubes[i].trancepos.z = EasingCircOut(t, 0.f, cubes[i].endpos.z);
		cubes[i].scale.x = EasingCircOut(t, beginscale.x, endscale.x);
		cubes[i].scale.y = EasingCircOut(t, beginscale.x, endscale.y);
		cubes[i].scale.z = EasingCircOut(t, beginscale.x, endscale.z);
		cubes[i].rotate += cubes[i].rotatespeed;
	}
	EasingManager::tCount(t, easingtime);
	if (EasingManager::tCountEnd(t))
		CountUp();
}

void EffectExplodeburst::draw(const ci::CameraPersp camera)
{
	for (int i = 0;i < cubes.size();i++) {
		DrawM.drawCube(pos+cubes[i].trancepos, cubes[i].scale,cubes[i].rotate,color);
	}

}

bool EffectExplodeburst::deleteThis()
{
	return count > 10;
}

ci::Vec3f EffectExplodeburst::endtrancepos(int i)
{
	switch (i)
	{
	case 0:
		return Vec3f(1, 1, 1);
	case 1:
		return Vec3f(1, 1, -1);
	case 2:
		return Vec3f(1, -1, 1);
	case 3:
		return Vec3f(1, -1, -1);
	case 4:
		return Vec3f(-1, 1, 1);
	case 5:
		return Vec3f(-1, 1, -1);
	case 6:
		return Vec3f(-1, -1, 1);
	case 7:
		return Vec3f(-1, -1, -1);
	default:
		break;
	}
}
