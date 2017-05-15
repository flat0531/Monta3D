#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
enum BulletType {
	PLAYER_BULLET,ENEMY_BULLET,GIMMICK_BULLET
};
class BulletBase {
public:
	virtual void setup() {};
	virtual void update() {};
	virtual void draw() {};
	virtual bool deleteThis() { return compulsiondelete; };
	
	
	void setPos(ci::Vec3f _pos) {
		pos = _pos;
	}
	ci::Vec3f getPos() {
		return pos;
	}
	ci::Vec3f getScale() {
		return scale;
	}
	ci::Vec3f getSpeed() {
		return speed;
	}
	ci::AxisAlignedBox3f getAABB() {
		ci::AxisAlignedBox3f buf(pos - (scale / 2.f), pos + (scale / 2.f));
		
		return buf;
	}
	int getAttackPoint() {
		return atackpoint;
	}
	int getHp() {
		return hp;
	}
	void AddHpValue(int value) {
		hp += value;
	}
	bool isActive() {
		return hp > 0;
	}
	BulletBase* getThisPointer() {
		return this;
	}
	void setCompulsiondelete(const bool is) {
		compulsiondelete = is;
	}
	//É}ÉbÉvÇ∆ìñÇΩÇËîªíËÇµÇΩÇ†Ç∆è¡Ç¶ÇÈÇ©Ç«Ç§Ç©
	bool getismapcollision_endddelet() {
		return ismapcollision_endddelet;
	}
protected:
	
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f speed;
	ci::Vec3f rotate;
	int atackpoint;
	int hp;
	BulletType bullettype;
	int timecount = 0;
	bool compulsiondelete = false;
	bool ismapcollision_endddelet = true;
	ci::AxisAlignedBox3f aabb;
};

template<class T>
inline void BulletBase::setParent(T * _parent)
{
	parent = _parent;
}
