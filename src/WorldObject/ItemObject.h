#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
class ItemObject {
public:
	ItemObject();
	ItemObject(const ci::Vec3f _pos, const ci::Vec3f _scale, const int _number,
		const std::string _itemtype,const std::string _name);
	void update();
	void draw();
	ci::Vec3f getPos();
	ci::Vec3f getScale();
	int getNumber();
	std::string getItemType();
	bool getIsGet();
	void setIsGet(const bool is);
private:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	ci::gl::Texture tex;
	int number;
	bool isget;
	std::string itemtype;
	std::string name;
};
