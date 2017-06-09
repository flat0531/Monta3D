#pragma once
#include"BulletBase.h"
#include<vector>
class BirdBullet : public BulletBase {
public:
	BirdBullet();
	BirdBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate);
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	struct Ring
	{
		ci::Vec3f trancepos;
		float scale;
		float length;
		float angle;
		float endscale;
		float scale_t;
		ci::ColorA color;
	};
	std::vector<Ring>rings;
	bool isshiftup = false;
	void arrangeStaus();
	float speedeasing;
	float speedeasing_t = 0.0f;
	int switchtime = 30;
};
