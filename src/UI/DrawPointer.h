#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class DrawPointer {
public:
	DrawPointer();
	void draw();
	void update();
	ci::Vec2f getPos();
	float getCircleSize();
	void setIsCircledraw(bool _iscircledraw);
	void setCircleColor(ci::ColorA _color);
	void setCircleSize(float const _circlesize);
private:
	ci::Vec2f pos;
	float circlesize;
	bool iscircledraw;
	ci::ColorA circlecolor;
};