#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class PlayTexture {
public:
	PlayTexture();
	PlayTexture(const ci::Vec2f _pos,const std::string _actionname,const int _number);
	void update(const int selectnum);
	void draw(const ci::Vec2f trancepos);
private:
	ci::Vec2f pos;
	ci::gl::Texture tex;
	ci::gl::Texture frametex;
	ci::gl::Texture wakutex;
	ci::Vec2f size;
	int number;
	float coloralfa = 0.2f;
	float alfa_t = 0.0f;
};