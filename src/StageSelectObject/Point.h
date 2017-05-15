#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class Point {
public:
	Point();
	Point(const ci::Vec2f _pos,const ci::Vec2f _size,const float _angle);
	void update();
	void draw();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	ci::Vec2f endsize;
	ci::ColorA color;
	float angle;
	float t;
	float sizeangle = 0.0f;
};