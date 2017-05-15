#include "NormalEnemyBullet.h"
#include "../../WorldObject/Enemy.h"
#include"MyToras.h"
using namespace ci;
using namespace ci::app;
NormalEnemyBullet::NormalEnemyBullet()
{
}

NormalEnemyBullet::NormalEnemyBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate, Enemy * enemy, int power, int _hp, int _delay, ci::ColorA _color, int _deleettime)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = power;
	hp = _hp;
	delay = _delay;
	bullettype = BulletType::ENEMY_BULLET;
	deleettime = _deleettime;
	enemyptr = enemy;

	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 0, 10), 0.f, ColorA(1, 1, 1, 1)));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 10, 10), 1.5f, _color));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(5, 10, 10), 3.f, ColorA(1, 1, 1, 1)));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(0, 5, 15), 1.f, _color));
	toras.push_back(std::make_shared<MyToras>(scale, rotate, ci::Vec3f(10, 0, 5), 2.f, _color));
}



void NormalEnemyBullet::setup()
{
}

void NormalEnemyBullet::update()
{
	timecount++;
	for (int i = 0;i < toras.size();i++) {
		toras[i]->update();
	}
	if (timecount < delay)return;
	pos += speed;
}

void NormalEnemyBullet::draw()
{
	gl::pushModelView();
	for (int i = 0;i < toras.size();i++) {
		toras[i]->draw(pos);
	}
	gl::popModelView();
}

bool NormalEnemyBullet::deleteThis()
{
	return (timecount >= deleettime)|| compulsiondelete;
}
