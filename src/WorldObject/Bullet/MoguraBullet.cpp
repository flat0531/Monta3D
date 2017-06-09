#include "MoguraBullet.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../CharacterAction/MoguraAction.h"
#include"../../WorldObject/Player.h"
using namespace ci;
using namespace ci::app;
MoguraBullet::MoguraBullet()
{
}

MoguraBullet::MoguraBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = 5;
	hp = 10;
	bullettype = BulletType::PLAYER_BULLET;
	int createnum = 6;
	
	for (int i = 0;i < createnum;i++) {
		Ring buff;
		buff.angle= ((float(i) / (float(createnum)))*2.f*M_PI);
		buff.trancepos = Vec3f(0, scale.y*sin(buff.angle)/2.f, 0);
		if (i % 3 == 0)buff.color = ColorA(1, 1, 0, 1);
		if (i % 3 == 1)buff.color = ColorA(1, 88.f / 255.f, 0, 1);
		if (i % 3 == 2)buff.color = ColorA(1, 1, 1, 1);
		rings.push_back(buff);
	}
}


void MoguraBullet::update()
{
	pos += speed;
	for (int i = 0;i < rings.size();i++) {
		rings[i].angle += 0.1f;
		rings[i].trancepos = Vec3f(0, scale.y*sin(rings[i].angle)/2.f, 0);
	}
	timecount++;
}

void MoguraBullet::draw()
{
	for (int i = 0;i < rings.size();i++) {
		DrawM.drawTaurus(pos+rings[i].trancepos,scale.x*0.6f,scale.x*0.04f,Vec3f(90,0,0),rings[i].color);
	}
}

bool MoguraBullet::deleteThis()
{
	return timecount > 40 || compulsiondelete;
}
