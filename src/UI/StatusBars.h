#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class StatusBars {
public:
	StatusBars();
	void update();
	void draw();
	void setEaing(std::string _name);
private:
	struct Bar {
		ci::Vec2f pos;
		ci::Vec2f size;
		float beginvalue;
		float endvalue;
		float value;
		float t;
		ci::ColorA color;
	};
	Bar red;
	Bar green;
	Bar blue;
	Bar white;
	void createAsset();
	ci::gl::Texture attacktex;
	ci::gl::Texture speedktex;
	ci::gl::Texture defensetex;
	ci::gl::Texture flytex;
};
