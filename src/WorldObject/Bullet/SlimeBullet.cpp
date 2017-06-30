#include "SlimeBullet.h"
#include"../../Top/DrawManager.h"
#include"../../Top/Top.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
SlimeBullet::SlimeBullet()
{
	console() << "¶‚Ü‚ê‚Ä‚µ‚Ü‚Á‚½" << std::endl;
}

SlimeBullet::SlimeBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = 6;
	hp = 12;
	uniquecolor = ColorA(0, 1, 1, 1);
	bullettype = BulletType::PLAYER_BULLET;
	toras.push_back(MyToras(scale,rotate,ci::Vec3f(5,0,10),0.f,ColorA(1,1,1,1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, ColorA(0, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, ColorA(0, 1, 1, 1)));
	toras.push_back(MyToras(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, ColorA(0, 1, 1, 1)));
}


void SlimeBullet::setup()
{
}

void SlimeBullet::update()
{
	pos += speed;
	for (int i = 0;i < toras.size();i++) {
		toras[i].update();
	}
	timecount++;
}

void SlimeBullet::draw()
{
	gl::pushModelView();
	for (int i = 0;i < toras.size();i++) {
		toras[i].draw(pos);
	}
	gl::popModelView();
}

bool SlimeBullet::deleteThis()
{
	return timecount >= 150|| compulsiondelete;
}