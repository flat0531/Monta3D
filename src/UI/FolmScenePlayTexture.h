#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class FolmScenePlayTexture {
public:
	FolmScenePlayTexture();
	FolmScenePlayTexture(const ci::Vec2f _pos,const ci::Vec2f _size,const std::string path,const std::string _name);
	void draw();
private:
	ci::Vec2f pos;
	ci::Vec2f size;
	ci::gl::Texture tex;
	ci::gl::Texture frametex;
	ci::gl::Texture basetex;
};
