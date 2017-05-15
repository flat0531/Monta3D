#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class MapChipBase;
class HitBox {
public:
	HitBox(ci::Vec2f _pos, ci::Vec2f _size, float _distance,MapChipBase* _mapchipptr);
	ci::Vec2f getPos();
	ci::Vec2f getSize();
	float getDistance();
	MapChipBase* getMapChipPtr();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	float distance;
	MapChipBase* mapchipptr;
};