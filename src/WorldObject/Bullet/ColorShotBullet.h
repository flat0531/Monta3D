#pragma once

#include"BulletBase.h"
#include<vector>
class Boss;
class MyToras;
class ColorShotBullet : public BulletBase {
public:
	ColorShotBullet();
	ColorShotBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate, ci::ColorA _color, Boss* _bossptr);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
	ci::ColorA color;
	ci::Vec3f beginscale;
	ci::Vec3f endscale;
	float scale_t = 0.0f;
	bool isshot = false;
	bool iseffect = false;
	int maxhp;
	Boss* bossptr;
	void createEffect();
};