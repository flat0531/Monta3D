#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class TextureObj {
public:
	TextureObj();
	TextureObj(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _rotate,std::string _path,bool _isalpha);
	ci::Vec3f getPos();
	ci::Vec3f getScale();
	ci::Vec3f getRotate();
	std::string getPath();
	bool getIsAlpha();
	void setIsAlpha(const bool is);
	void setPos(const ci::Vec3f _pos);
	void setPosX(const float _posx);
	void setPosY(const float _posy);
	void setPosZ(const float _posz);
	void setScale(const ci::Vec3f _scale);
	void setRotate(const ci::Vec3f _rotate);
	void setPath(const std::string _path);
	void setColor(const ci::ColorA _color);
	void draw();
private:
	ci::Vec3f pos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	std::string path;
	ci::ColorA color;
	bool isalpha;
};