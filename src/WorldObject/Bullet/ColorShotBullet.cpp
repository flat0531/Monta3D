#include "ColorShotBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"../../WorldObject/Boss.h"
#include"../../Top/EasingManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldCreater/CameraMnager.h"
#include"../../WorldObject/Effect/EffectColorShot.h"
#include"../../Top/SoundManager.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
ColorShotBullet::ColorShotBullet()
{
}

ColorShotBullet::ColorShotBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate, ci::ColorA _color, Boss * _bossptr)
{
	pos = _pos;
	beginscale = Vec3f(0, 0, 0);
	scale = beginscale;
	endscale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = 30;
	hp = 40;
	maxhp =  hp;
	uniquecolor = ColorA(1, 1, 1, 1);
	bullettype = BulletType::BOSS_BULLET;
	bossptr = _bossptr;
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 0, 0, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 0), 1.5f, ColorA(1, 165.f / 255.f, 0, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 0, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 10), 1.f, ColorA(51.f / 255.f, 153.f / 255.f, 67.f / 255.f, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, ColorA(0, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 5, 0), 2.f, ColorA(0, 0, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 10, 5), 2.f, ColorA(165.f / 255.f, 0, 1, 1)));
	ismapcollision_endddelet = false;
}

void ColorShotBullet::setup()
{
}

void ColorShotBullet::update()
{
	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
		toras[i].setScale(scale);
	}
	if (isshot) {
		float scalerate = (float(hp) / (float(maxhp)));
		atackpoint = std::max(10.f, scalerate*30.f);
		scale.x = scalerate*endscale.x;
		scale.y = scalerate*endscale.y;
		scale.z = scalerate*endscale.z;
		pos += speed;
		if (pos.z - (scale.z / 2.f) < (-WorldScale*7.f) && (!iseffect)) {
			createEffect();
			bossptr->getCameraManager()->Shake(scalerate*100.f,1.0f);
			
		}
	}
	else {
		EasingManager::tCount(scale_t, 3.f);
		scale.x = EasingLinear(scale_t, beginscale.x, endscale.x);
		scale.y = EasingLinear(scale_t, beginscale.y, endscale.y);
		scale.z = EasingLinear(scale_t, beginscale.z, endscale.z);
		if (EasingManager::tCountEnd(scale_t)) {
			isshot = true;
			hp = maxhp;
			SoundM.PlaySE("colorchargeshot.wav");
		}
	}
}

void ColorShotBullet::draw()
{
	for (int i = 0;i < toras.size();i++) {
		toras[i].draw(pos);
	}
}

bool ColorShotBullet::deleteThis()
{
	return pos.z-(scale.z/2.f) < (-WorldScale*7.f);
}

void ColorShotBullet::createEffect()
{
	bossptr->getEffectManagerPointer()->CreateEffect2D(EffectColorShot(scale));
}
