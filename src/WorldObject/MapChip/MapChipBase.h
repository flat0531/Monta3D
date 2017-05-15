#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../CharacterBase.h"
#include"../Bullet/BulletBase.h"
#include<memory>
class MapChipBase {

public:
	MapChipBase();
	ci::Vec3f getPos3f();
	ci::Vec3f getScale3f();
	ci::Vec3f getRotate();
	ci::Vec2f getPos2f();
	ci::Vec2f getScale2f();
	virtual void draw() {};
	virtual void update() {};
	virtual void UpCollisionEnter(CharacterBase * characterbase) {};
	virtual void DownCollisionEnter(CharacterBase * characterbase) {};
	virtual void RightCollisionEnter(CharacterBase * characterbase) {};
	virtual void LeftCollisionEnter(CharacterBase * characterbase) {};
	virtual void InCollisionEnter(CharacterBase * characterbase) {};
	virtual void BulletCollison(BulletBase * bulletbase,bool isbreak) {};
	MapChipBase* getThisPointer() {
		return this;
	};
	bool getIsCollision();
	void setCollision(bool is);
	float getDistance();
	void setDistance(float _distance);
	void setIsHit(bool is);
	bool getIsHit();
	bool getIsActive();
protected:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	bool iscollision = false;
	bool ishit = false;
	float distance;
	bool isactive = true;
};