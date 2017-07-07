#pragma once
#include"BulletBase.h"
class CatAction;
class Player;
class CatBullet : public BulletBase {
public:
	CatBullet();
	CatBullet(ci::Vec3f _pos, ci::Vec3f _scale, float _angle,
		ci::Vec3f _rotate,ci::ColorA _color, Player* _playerptr,int power);
	void setup()override;
	void update()override;
	void draw()override;
	bool deleteThis()override;
private:
	ci::ColorA color;
	float angle;
	template<class T>
	void setParent(T* _parent);
	Player* playerptr;
};

template<class T>
inline void CatBullet::setParent(T * _parent)
{
	parent = _parent;
}
