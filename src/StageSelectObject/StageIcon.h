#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class StageIcon {
public:
	StageIcon();
	StageIcon(const ci::Vec2f _pos, const ci::Vec2f _size,const ci::ColorA _color,const bool _isclear,const int _number);
	void update(const bool ismoving,const int selectstagenum);
	void draw();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	ci::Vec2f beginsize;
	ci::Vec2f endsize;
	ci::ColorA defaltcolor;
	ci::ColorA color;
	bool isclear;
	int number;
	float colorangle = 0.0f;
	float scale_t = 0.0f;
};