#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"StringLogo.h"
class StageSelectLogo {
public:
	StageSelectLogo();
	void update();
	void draw();
private:
	std::vector<StringLogo>logostrig;
	ci::gl::Texture montatex;
	ci::gl::Texture treetex;
	ci::gl::Texture basetex;
	void CretaeLogoString();
	void updateMontaIcon();
	void updateTreeIcon();
	void drawBase();
	ci::Vec2f pos;
	ci::Vec2f montaiconpos;
	ci::Vec2f montaiconsize;
	float montaiconangle;
	float monta_t;
	float monta_delay_t;
	float treeangle;
	float treesinangle;
};