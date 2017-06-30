#include "BlackScaleBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"../../Top/EasingManager.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
BlackScaleBullet::BlackScaleBullet()
{

}

BlackScaleBullet::BlackScaleBullet(ci::Vec3f _pos, ci::Vec3f _beginscale, ci::Vec3f _endscale, float _easingtime)
{
	pos = _pos;
	scale = _beginscale;
	beginscale = _beginscale;
	endscale = _endscale;
	easingtime = _easingtime;
	speed = Vec3f(0, 0, 0);
	rotate = Vec3f(0, 0, 0);
	atackpoint = 10;
	hp = 10000;
	uniquecolor = ColorA(0, 0, 0, 1);
	bullettype = BulletType::BOSS_BULLET;
	scale_t = 0.0f;
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, uniquecolor));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, uniquecolor));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, uniquecolor));
	ismapcollision_endddelet = false;
}



void BlackScaleBullet::setup()
{

}

void BlackScaleBullet::update()
{
	EasingManager::tCount(scale_t,easingtime);
	scale.x = EasingReturn(scale_t, beginscale.x, endscale.x);
	scale.y = EasingReturn(scale_t, beginscale.y, endscale.y);
	scale.z = EasingReturn(scale_t, beginscale.z, endscale.z);
	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
		toras[i].setScale(scale);
	}
}

void BlackScaleBullet::draw()
{
	for (int i = 0;i < toras.size();i++) {
		toras[i].draw(pos);
	}
}

bool BlackScaleBullet::deleteThis()
{
	return EasingManager::tCountEnd(scale_t);
}
