#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
/////////////////ŠG‹ïˆê‚Âˆê‚Â‚ÌƒNƒ‰ƒX
class ColorObject {
public:
	ColorObject();
	ColorObject(ci::Vec2f _trancepos,ci::Vec2f _palletpos,ci::Vec2f _size, ci::ColorA _color,bool _isnecessary);
	ci::ColorA getColor();
	bool getIsnecessary();
	ci::Vec2f getPos();
	ci::Vec2f getSize();
	ci::Vec2f getLeftUpPos();
	void SetIsselected(bool _isselected);
	void update(const ci::Vec2f _palletpos);
	void drawCircle();
	void drawNecessaryIcon();
private:
	ci::ColorA color;
	ci::Vec2f pos;
	ci::Vec2f trancepos;
	ci::Vec2f palletpos;
	ci::Vec2f size;
	ci::Vec2f easingpos;
	bool isnecessary;
	bool isselected;
	float t = 0.0f;
	void move(const ci::Vec2f _palletpos);
};