#include "WideShotBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
WideShotBullet::WideShotBullet()
{
}

WideShotBullet::WideShotBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate, ci::ColorA _color)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = 10;
	hp = 30;
	color = _color;
	uniquecolor = color;
	bullettype = BulletType::BOSS_BULLET;
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, color));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, color));
}


void WideShotBullet::setup()
{
}

void WideShotBullet::update()
{
	pos += speed;
	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
	}
	timecount++;
}

void WideShotBullet::draw()
{
	gl::pushModelView();
	for (int i = 0;i < toras.size();i++) {
		toras[i].draw(pos);
	}
	gl::popModelView();
}

bool WideShotBullet::deleteThis()
{
	return (pos.z<-1.f*WorldScale) || compulsiondelete;
}
