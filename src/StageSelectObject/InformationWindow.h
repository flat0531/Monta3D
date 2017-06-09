#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\gl\Texture.h"
class InformationWindow {
public:
	InformationWindow();
	InformationWindow(const int _worldnum, const int _stagenum, const int _itemnember);
	void update();
	void draw();
	bool isDelete();
private:
	ci::Vec2f windowpos;
	ci::Vec2f itempos;
	ci::Vec2f windowsize;
	ci::Vec2f itemsize;
	float rotate;
	ci::gl::Texture windowtex;
	ci::gl::Texture itemtex;
	ci::gl::Texture frametex;
	ci::gl::Texture painttex;
	ci::gl::Texture buttontex;
	ci::ColorA paintcolor = ci::ColorA(1, 1, 1, 1);
	float angle;
	float t = 0.0f;
	float sizerate = 0.0f;
	std::string itemtype;
	std::string itemname;
	void drawColorWindow();
	void drawFolmWindow();
	void updateOpen();
	void updateClose();
	bool isclose = false;
	bool playedse = false;
};
