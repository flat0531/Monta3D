#include "BarrierBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"../../Top/EasingManager.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;

BarrierBullet::BarrierBullet()
{
}

BarrierBullet::BarrierBullet(ci::Vec3f _beginpos, ci::Vec3f _betweenpos, ci::Vec3f _endpos, ci::ColorA _color)
{
	pos = _beginpos;
	beginpos = _beginpos;
	betweenpos = _betweenpos;
	endpos = _endpos;
	scale = Vec3f(0.9,0.9,0.9)*WorldScale;
	speed = Vec3f(0,0,0);
	rotate = Vec3f(0,0,0);
	atackpoint = 12;
	hp = 10000;
	color = _color;
	uniquecolor = _color;
	bullettype = BulletType::BOSS_BULLET;
	for (int i = 0;i < 3;i++) {
		t[i] = 0.0f;
	}
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f,color));
}

void BarrierBullet::setup()
{
}

void BarrierBullet::update()
{
	if (!EasingManager::tCountEnd(t[0])) {
		EasingManager::tCount(t[0], 1.5f);
		pos.x = EasingLinear(t[0], beginpos.x, betweenpos.x);
		pos.y = EasingLinear(t[0], beginpos.y, betweenpos.y);
		pos.z = EasingLinear(t[0], beginpos.z, betweenpos.z);
	}
	if (EasingManager::tCountEnd(t[0])&&(!EasingManager::tCountEnd(t[1]))) {
		EasingManager::tCount(t[1], 7.0f);
		pos.x = EasingExpoOut(t[1], betweenpos.x, betweenpos.x - (betweenpos.x - endpos.x) / 10.f);
		pos.y = EasingExpoOut(t[1], betweenpos.y, betweenpos.y - (betweenpos.y - endpos.y) / 10.f);
		pos.z = EasingExpoOut(t[1], betweenpos.z, betweenpos.z - (betweenpos.z - endpos.z) / 10.f);
	}
	if (EasingManager::tCountEnd(t[1]) && (!EasingManager::tCountEnd(t[2]))) {
		EasingManager::tCount(t[2], 3.0f);
		pos.x =EasingExpoIn(t[2], betweenpos.x - (betweenpos.x - endpos.x) / 10.f, endpos.x);
		pos.y = EasingExpoIn(t[2], betweenpos.y - (betweenpos.y - endpos.y) / 10.f, endpos.y);
		pos.z = EasingExpoIn(t[2], betweenpos.z - (betweenpos.z - endpos.z) / 10.f, endpos.z);
	}
	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
	}
}

void BarrierBullet::draw()
{
	for (int i = 0;i < toras.size();i++) {
		toras[i].draw(pos);
	}
}

bool BarrierBullet::deleteThis()
{
	return EasingManager::tCountEnd(t[2])|| compulsiondelete;
}
