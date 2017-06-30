#pragma once
#include"BulletBase.h"
#include<vector>
class MyToras;
class FireBullet : public BulletBase {
public:
	FireBullet();
	FireBullet(ci::Vec3f _begincenterpos,ci::Vec3f _endcenterpos,ci::Vec3f _endscale, float _length, float beginangle, ci::ColorA _color);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
	ci::ColorA color;
	ci::Vec3f centerpos;
	ci::Vec3f begincenterpos;
	ci::Vec3f endcenterpos;
	ci::Vec3f endscale;
	float begin_scale_t = 0.0f;
	float beginrotate_t = 0.0f;
	float endrotate_t = 0.0f;
	float end_scale_t = 0.0f;
	float center_pos_t = 0.0f;
	float length;
	float beginangle;
	float angle;
	float anglespeed;
};
