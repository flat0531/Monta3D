#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include"../UI/FolmTexture.h"
#include"../UI/FolmScenePlayTexture.h"
#include<vector>
#include<memory>
class FolmTextureList {
public:
	FolmTextureList();
	void update();
	void draw();
	void CreateFolmTextures();
	void CreatePlayTextures();
	bool getIsrelease();
private:
	std::vector<std::shared_ptr<FolmTexture>> folmtextures;
	std::vector<std::shared_ptr<FolmScenePlayTexture>>playtextures;
	int selectnum = 0;
	void selectFolm();
	void drawCursor();
	ci::gl::Texture cursortex;
	//ci::Vec2f trancepos;
	//ci::Vec2f beginpos;
	//ci::Vec2f endpos;
	//float span_y = 350.f;
	//ci::gl::Texture push_w;
	//ci::gl::Texture push_s;
	//float cursorsinangle = 0.0f;
	//int selectnum = 1;
	//float trance_t = 1.0f;
	//void setEasing(ci::Vec2f _beginpos, ci::Vec2f _endpos);
	//void EasingTranxePos();
	//void drawCursor();
};