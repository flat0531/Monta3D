#pragma once
#include"BulletBase.h"
#include<vector>
#include<memory>
class MyToras;
class Enemy;
class ScaleUpBullet : public BulletBase {
public:
	ScaleUpBullet();
	ScaleUpBullet(ci::Vec3f _pos, ci::Vec3f _startscale,ci::Vec3f _endscale, ci::Vec3f _speed, ci::Vec3f _rotate, Enemy* enemy, int power, int _hp,
		int _delay, ci::ColorA _color, int _deleettime = 60);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<std::shared_ptr<MyToras>> toras;
	Enemy* enemyptr;
	int deleettime;
	int delay;
	float scale_t;
	ci::Vec3f startscale;
	ci::Vec3f endscale;
};