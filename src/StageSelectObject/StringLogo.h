#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class StringLogo {
public:
	StringLogo();
	StringLogo(std::string _str, ci::Vec2f _pos,ci::Vec2f _size,float _trance_delay);
	void update();
	void draw();
private:
	void updatePos();
	std::string str;
    ci::gl::Texture tex;
	ci::Vec2f pos;
	ci::Vec2f startpos;
	ci::Vec2f size;
	float angle = 0.0f;
	float trancepos_t = 0.0f;
	float trance_delay_t;
};