#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\Surface.h"
//////�v���C���[���h�邱�Ƃ̂ł���L�����o�X
class PlayerCanvas {
public:
	PlayerCanvas();
	void draw();
	void updateCanvas(const ci::ColorA _color, const ci::Vec2f pointerpos, float _circlesize);
	void setup(ci::Vec2f _pos,ci::Vec2f _size,std::string _charactername);
	ci::Vec2f getPos();
	ci::Vec2f getSIze();
	ci::Surface getSurface();
private:
	ci::Surface drawcanvas;
	std::string charactername;
	std::string characterframepath;
	ci::Vec2f pos;
	ci::Vec2f size;
	void SetupdrawCanvas();
	
};