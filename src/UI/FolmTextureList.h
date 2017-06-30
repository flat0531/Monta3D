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
	int selectnum;
	void selectFolm();
	void drawCursor();
	ci::gl::Texture cursortex;
};