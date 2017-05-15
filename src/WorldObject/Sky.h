#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class Sky {
public:
	Sky();
	Sky(const ci::Vec3f _pos,
		const ci::Vec3f _scale,
		const ci::Vec3f _rotate,
		const ci::ColorA _color, const std::string _texturepath);
	void setup();
	void update();
	void draw();
	void Rotate(const ci::Vec3f _rotate);
	void setIsRotate(const bool _is);
	void setRotation(const ci::Vec3f _rotate);
private:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	ci::ColorA color;
	std::string texturepath;
	bool isrotate;
};