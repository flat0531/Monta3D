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
	ci::Vec3f pos = ci::Vec3f(0, 0, 0);
	ci::Vec3f scale = ci::Vec3f(0, 0, 0);
	ci::Vec3f rotate = ci::Vec3f(0, 0, 0);
	ci::Vec2f pos2f = ci::Vec2f(0, 0);
	ci::Vec2f scale2f = ci::Vec2f(0, 0);
	float rotate_2d = 0.0f;
	int count = 0;
};