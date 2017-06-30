#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能
#include "cinder/imageIo.h"  

#include "cinder/Surface.h"

#include <memory>
#include <functional>
#include"../../Top/SurfaceEffect.h"
#include"../../UI/DrawPointer.h"
#include"../../UI/PalletManager.h"
#include"../../UI/PlayerCanvas.h"
#include"../../UI/DrawMenu.h"
#include"../../UI/UICreater.h"
class FreeDraw :public SceneBase {
public:
	FreeDraw();
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	DrawPointer drawpointer;
	PalletManager palletmanager;
	PlayerCanvas playercanvas;
	DrawMenu drawmenu;
	UICretaer uiback;
	UICretaer uifront;
	std::vector<SurfaceEffect> effects;
	std::vector<ci::ColorA> color;
	std::string charactername;
	std::string framepath;
	std::string characterframepath;
	std::string charactercoloredpath;
	std::string characterplaypath;
	ci::Vec2f savewindowpos;
	ci::Vec2f savewindowsize;
	ci::gl::Texture drawtex;
	bool issavewindow = false;
	float savewinodw_t = 0.0f;
	float delay_t = 0.0f;
	bool isshift = false;
	void updateEraceCanvas();
	void updateDrawCanvas();
	void updateSave();
	void updateBack();
	void updateSaveWindow();
	void drawSaveWindow();
	void createAsset();
	void playBGM();
};
