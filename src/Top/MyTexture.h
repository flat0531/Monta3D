#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能
#include "cinder/imageIo.h"  
class MyTexture {
public:
	MyTexture();
	MyTexture(std::string name);
	~MyTexture();
	ci::gl::Texture const& getTex();
	void Clear();
	//int y_;
	//bool operator<(const MyTexture &right) const { return this->y_ < right.y_; }
	void Set(const std::string name);
private:
	std::string name;
	ci::gl::Texture tex;
	
};