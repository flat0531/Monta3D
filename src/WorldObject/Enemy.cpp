#include "Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
Enemy::Enemy()
{

}

Enemy::Enemy(ci::Vec3f _pos, ActionType _type, int _id)
{
	pos = _pos;
	drawpos = pos;
	scale = ci::Vec3f(1, 1, 1)*WorldScale;
	rotate = ci::Vec3f(0, 0, 180);
	speed = ci::Vec3f(0, 0, 0);
	actiontype = _type;
	hp = 100;
	id = _id;
}


void Enemy::update()
{
	prevpos = pos;

	pos += speed;
	drawpos = pos;

	updateStun();
	if (isstun) {
		action->damaged();
	}
	if(!isstun)
	action->update();
}

void Enemy::draw()
{
	//DrawM.drawCube(aabbbox.getCenter(),aabbbox.getSize()*0.9f,ci::Vec3f(0,0,0),ci::ColorA(0,0,1,1));
	action->draw();
}

void Enemy::setup(ci::Vec3f _pos)
{
	
}
