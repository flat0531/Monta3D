#pragma once
#include"BulletBase.h"
#include<vector>
class MyToras;
class BlackScaleBullet : public BulletBase {
public:
	BlackScaleBullet();
	BlackScaleBullet(ci::Vec3f _pos,ci::Vec3f _beginscale ,ci::Vec3f _endscale,float _easingtime);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	std::vector<MyToras> toras;
	float scale_t;
	ci::Vec3f beginscale;
	ci::Vec3f endscale;
	float easingtime;
};
