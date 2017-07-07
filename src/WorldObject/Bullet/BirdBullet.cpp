#include "BirdBullet.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
BirdBullet::BirdBullet()
{
}

BirdBullet::BirdBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate, int _power)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = _rotate;
	atackpoint = 3;
	endpower = _power;
	uniquecolor = ColorA(0, 1, 0, 1);
	hp = 5;
	int createnum = 12;
	for (int i = 0;i < createnum;i++) {
		Ring buff;
		buff.trancepos = Vec3f(0, -scale.y / 2.f + ((float(i)) / (float(createnum)))*scale.y, 0);
		buff.angle = ((float(i) / (float(createnum)))*2.f*M_PI);
		buff.length = 0.0f;
		buff.scale = 1.0f;
		buff.scale_t = 0.0f;
		buff.endscale = 0.2f + 0.8f*(float(i + 1) / (float(createnum)));
		if (i % 3 == 0)buff.color = ColorA(0, 1, 0, 1);
		if (i % 3 == 1)buff.color = ColorA(1, 1, 1, 1);
		if (i % 3 == 2)buff.color = ColorA(1, 1, 0, 1);
		rings.push_back(Ring(buff));
	}
}



void BirdBullet::update()
{
	timecount++;
	if (timecount >= switchtime) {
		isshiftup = true;
		
	}
	else {
		EasingManager::tCount(speedeasing_t,(float(switchtime))/60.f);
		speedeasing = EasingCircOut(speedeasing_t, 8.0f, 0.0f);
		atackpoint = int(EasingLinear(speedeasing_t,3.0f,10.0f));
		for (int i = 0;i < rings.size();i++) {
			rings[i].length = EasingCircOut(speedeasing_t, 0.0f, 0.2f)*WorldScale;
			rings[i].scale = EasingCircIn(speedeasing_t, 1.0f, rings[i].endscale);
		}
	}
	for (int i = 0;i < rings.size();i++) {
		rings[i].angle += 0.5f;
	}
	for (int i = 0;i < rings.size();i++) {
		rings[i].trancepos = Vec3f(rings[i].length*cos(rings[i].angle),rings[i].trancepos.y, rings[i].length*sin(rings[i].angle));
	}
	arrangeStaus();
	pos += speed*speedeasing;
}

void BirdBullet::draw()
{
	for (int i = 0;i < rings.size();i++) {
		DrawM.drawTaurus(pos+rings[i].trancepos, scale.x*0.6f*rings[i].scale, scale.x*0.02f*rings[i].scale, Vec3f(90, 0, 0),rings[i].color);
	}
	
	//DrawM.drawCube(pos, scale, rotate, ColorA(0, 1, 0, 1));
}

bool BirdBullet::deleteThis()
{
	return timecount > 60 || compulsiondelete;
}

void BirdBullet::arrangeStaus()
{
	if (isshiftup) {
		atackpoint = endpower;
		hp = 20;
		speed = Vec3f(0, 0.12f, 0)*WorldScale;
		speedeasing = 1.0f;
		scale += Vec3f(0.05f, 0.05f, 0.05f)*WorldScale;
		
	}
}
