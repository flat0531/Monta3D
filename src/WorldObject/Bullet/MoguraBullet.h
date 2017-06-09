#pragma once
#include"BulletBase.h"
#include<vector>
class CatAction;
class Player;
class MoguraBullet : public BulletBase {
public:
	MoguraBullet();
	MoguraBullet(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _speed, ci::Vec3f _rotate);
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	struct Ring
	{
		ci::Vec3f trancepos;
		float angle;
		ci::ColorA color;
	};
	std::vector<Ring>rings;

};