#pragma once
#include"BulletBase.h"
#include<vector>
class MyToras;
class SlimeBullet : public BulletBase {
public:
	SlimeBullet();
	SlimeBullet(ci::Vec3f _pos,ci::Vec3f _scale,ci::Vec3f _speed,ci::Vec3f _rotate,int _power);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
};