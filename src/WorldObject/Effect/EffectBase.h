#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class EffectBase {
public:
	EffectBase();
	virtual void draw() {};
	virtual void update() {};
	virtual bool deleteThis() { return false; };
	void CountUp();
protected:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	int count = 0;
};