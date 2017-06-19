#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class FolmTexture {
public:
	FolmTexture();
	FolmTexture(const ci::Vec2f _pos, const std::string _actionname,bool _isrelease, const int _number);
	void update(const int selectnum);
	ci::Vec2f getPos();
	std::string getName();
	void draw(const ci::Vec2f trancepos);
	bool getIsRelease();
private:
	ci::Vec2f pos;
	ci::gl::Texture tex;
	std::string name;
	ci::Vec2f size;
	int number;
	float coloralfa = 0.2f;
	float alfa_t = 0.0f;
	bool isrelease;
};
