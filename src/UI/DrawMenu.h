#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../UI/Range.h"
/////////様々な機能を乗っけるメニュー
class DrawMenu {
public:
	DrawMenu();
	void draw();
	void update();
	float getSizeRangeValue();
	void setSampleCircleSize(float size);
	void setCircleColor(ci::ColorA _color);
private:
	Range sizerange;
	ci::Vec2f pos;
	ci::Vec2f size;
	float circlesize;
	ci::ColorA circlecolor;
	void drawBackGround();
	void drawSampleCircle();
};