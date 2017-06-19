#pragma once
#include"BulletBase.h"
#include<vector>
class AngelBullet : public BulletBase {
public:
	AngelBullet();
	AngelBullet(ci::Vec3f _pos, ci::Vec3f _scale,float y_rotate, float z_rotate, ci::Vec3f _speed,int _deletetime,std::string _texturepath);
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	int  deletetime;
	std::string texturepath;
	float z_rotate = 0.f;
	float y_rotate = 0.f;
};