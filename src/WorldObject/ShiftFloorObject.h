#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class ShiftFloorObject {
public:
	ShiftFloorObject();
	ShiftFloorObject(const ci::Vec3f _pos,const ci::Vec3f _size,const int _nextfloornum,
		const ci::Vec3f _nextplayerpos, const ci::Vec3f _nextplayerrotate);
	ci::Vec3f getPos();
	ci::Vec3f getSize();
	int getNextFloorNum();
	ci::Vec3f getNextPlayerPos();
	ci::Vec3f getNextPlayerRotate();
	void draw();
private:
	ci::Vec3f pos;
	ci::Vec3f size;
	int nextfloornum;
	ci::Vec3f nextplayerpos;
	ci::Vec3f nextplayerrotate;
};