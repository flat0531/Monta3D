#pragma once
#include"BulletBase.h"
#include<vector>
class MyToras;
class WideShotBullet : public BulletBase {
public:
	WideShotBullet();
	WideShotBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate,ci::ColorA _color);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
	ci::ColorA color;

};