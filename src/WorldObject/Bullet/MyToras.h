#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class MyToras {
public:
	MyToras(ci::Vec3f _scale, ci::Vec3f _rotate, ci::Vec3f _rotatespeed, float _sizeangle, ci::ColorA _color);
	void draw(const ci::Vec3f _pos);
	void update();
	void setScale(const ci::Vec3f _scale);
private:
	ci::Vec3f startscale;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	ci::Vec3f rotatespeed;
	ci::ColorA color;
	float sizeangle;
};