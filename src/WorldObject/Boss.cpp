#include "Boss.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"

using namespace ci;
using namespace ci::app;
Boss::Boss()
{

}

Boss::Boss(ci::Vec3f _pos, ActionType _type, int _id)
{
	pos = _pos;
	drawpos = pos;
	scale = ci::Vec3f(1, 1, 1)*WorldScale;
	rotate = ci::Vec3f(0, 0, 180);
	speed = ci::Vec3f(0, 0, 0);
	actiontype = _type;
	hp = 100;
	id = _id;
	isstun = false;
}

void Boss::update()
{
	prevpos = pos;
	pos += speed;
	drawpos = pos;
	jumpcount++;
	updateStun();
	if (isstun) {
		action->damaged();
	}
	if (!isstun)
		action->update();
}

void Boss::draw()
{
	action->draw();
}

void Boss::setup(ci::Vec3f _pos)
{

}

int Boss::getjumpCount()
{
	return jumpcount;
}