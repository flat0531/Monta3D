#include "ScaleUpBullet.h"
#include "../../WorldObject/Enemy.h"
#include"MyToras.h"
#include"../../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
ScaleUpBullet::ScaleUpBullet()
{
}

ScaleUpBullet::ScaleUpBullet(ci::Vec3f _pos, ci::Vec3f _startscale, ci::Vec3f _endscale, ci::Vec3f _speed, ci::Vec3f _rotate, Enemy * enemy, int power, int _hp, int _delay, ci::ColorA _color, int _deleettime)
{
	pos = _pos;
	scale = _startscale;
	startscale = _startscale;
	endscale = _endscale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = power;
	hp = _hp;
	delay = _delay;
	bullettype = BulletType::ENEMY_BULLET;
	deleettime = _deleettime;
	enemyptr = enemy;
	scale_t = 0.0f;

	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, _color));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, _color));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, _color));
}

void ScaleUpBullet::setup()
{
}

void ScaleUpBullet::update()
{
	timecount++;
	if (!EasingManager::tCountEnd(scale_t)) {
		EasingManager::tCount(scale_t, (float(delay)) / 60.f);
		scale.x = EasingLinear(scale_t, startscale.x, endscale.x);
		scale.y = EasingLinear(scale_t, startscale.y, endscale.y);
		scale.z = EasingLinear(scale_t, startscale.z, endscale.z);
	}

	for (int i = 0;i < toras.size();i++) {
		toras[i]->update();
		toras[i]->setScale(scale);
	}
	if (timecount < delay)return;
	pos += speed;
}

void ScaleUpBullet::draw()
{
	gl::pushModelView();
	for (int i = 0;i < toras.size();i++) {
		toras[i]->draw(pos);
	}
	gl::popModelView();
}

bool ScaleUpBullet::deleteThis()
{
	return (timecount >= deleettime)|| compulsiondelete||(!enemyptr->getIsAlive());
}