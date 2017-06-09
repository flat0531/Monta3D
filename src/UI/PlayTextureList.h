#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include"PlayTexture.h"
#include<vector>
#include<memory>
class PlayTextureList {
public:
	PlayTextureList();
	void update();
	void draw();
	void CreatePlayTextures(std::string actionname);
	void selectUserTexture();
	int getSelectNum();
private:
	std::vector<std::shared_ptr<PlayTexture>> playtextures;
	ci::Vec2f trancepos;
	ci::Vec2f beginpos;
	ci::Vec2f endpos;
	float span_y = 350.f;
	ci::gl::Texture push_w;
	ci::gl::Texture push_s;
	float cursorsinangle = 0.0f;
	int selectnum = 1;
	float trance_t = 1.0f;
	void setEasing(ci::Vec2f _beginpos,ci::Vec2f _endpos);
	void EasingTranxePos();
	void drawCursor();
};