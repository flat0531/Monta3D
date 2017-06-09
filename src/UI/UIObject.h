#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include"../Top/MyJson.h"

class UIObject {
public:
	UIObject();
	UIObject(ci::JsonTree json);
	void draw();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	float rotate;
	ci::gl::Texture tex;
	ci::ColorA color;
};
