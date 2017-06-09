#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class ActionIcon {
public:
	ActionIcon();
	ActionIcon(ci::Vec2f _pos,
	ci::Vec2f _size,
	std::string _name,bool _isselected);
	void update();
	void draw();
	void setIsSelected(const bool _isselected);
	std::string getName();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	std::string name;
	ci::gl::Texture snaptex;
	ci::gl::Texture frametex;
	ci::gl::Texture snapbase;
	ci::ColorA framecolor;
	bool isselected;
};
