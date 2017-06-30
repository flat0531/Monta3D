#pragma once
#include"BulletBase.h"
#include<vector>
class MyToras;
class BarrierBullet : public BulletBase {
public:
	BarrierBullet();
	BarrierBullet(ci::Vec3f _beginpos, ci::Vec3f _betweenpos, ci::Vec3f _endpos, ci::ColorA _color);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
	float t[3];
	ci::Vec3f beginpos;
	ci::Vec3f betweenpos;
	ci::Vec3f endpos;
	ci::ColorA color;
};
