#include "FireBullet.h"
#include "ColorShotBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"../../Top/EasingManager.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
FireBullet::FireBullet()
{
}

FireBullet::FireBullet(ci::Vec3f _begincenterpos, ci::Vec3f _endcenterpos, ci::Vec3f _endscale, float _length, float beginangle, ci::ColorA _color)
{
	length = _length;
	endscale = _endscale;
	begincenterpos = _begincenterpos;
	endcenterpos = _endcenterpos;
	pos.x = begincenterpos.x + length*cos(beginangle);
	pos.y = begincenterpos.y;
	pos.z = begincenterpos.z + length*sin(beginangle);

	angle = beginangle;
	scale = Vec3f(0, 0, 0);
	atackpoint = 7;
	hp = 10000;
	color = _color;
	uniquecolor = color;
	bullettype = BulletType::BOSS_BULLET;
	rotate = Vec3f(0, 0, 0);
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, color));
	ismapcollision_endddelet = false;
}

void FireBullet::setup()
{
}

void FireBullet::update()
{
	
	EasingManager::tCount(center_pos_t,15.f);
	centerpos.x = EasingExpoOut(center_pos_t, begincenterpos.x, endcenterpos.x);
	centerpos.z = EasingExpoOut(center_pos_t, begincenterpos.z, endcenterpos.z);

	if (!EasingManager::tCountEnd(beginrotate_t)) {
		EasingManager::tCount(beginrotate_t, 7.0f);
		anglespeed = EasingCubicOut(beginrotate_t, 0.f, 0.035f);
	}
	else {
		EasingManager::tCount(endrotate_t, 7.0f);
		anglespeed = EasingCubicIn(endrotate_t, 0.035f, 0.f);
	}
	if (!EasingManager::tCountEnd(begin_scale_t)) {
		EasingManager::tCount(begin_scale_t, 1.0f);
		scale.x = EasingBackOut(begin_scale_t, 0.f, endscale.x);
		scale.y = EasingBackOut(begin_scale_t, 0.f, endscale.y);
		scale.z = EasingBackOut(begin_scale_t, 0.f, endscale.z);
	}
	if (EasingManager::tCountEnd(endrotate_t))
	{
		EasingManager::tCount(end_scale_t, 1.0f);
		scale.x = EasingBackOut(end_scale_t, endscale.x, 0.0f);
		scale.y = EasingBackOut(end_scale_t, endscale.y, 0.0f);
		scale.z = EasingBackOut(end_scale_t, endscale.z, 0.0f);
	}
	


	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
	}

	angle += anglespeed;

	pos.x = centerpos.x + length*cos(angle);
	pos.z = centerpos.z + length*sin(angle);

}

void FireBullet::draw()
{
	for (int i = 0;i < toras.size();i++) {
		toras[i].setScale(scale);
		toras[i].draw(pos);
		
	}
}

bool FireBullet::deleteThis()
{
	return EasingManager::tCountEnd(center_pos_t);
}
