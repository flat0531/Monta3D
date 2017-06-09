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
class Draw :public SceneBase {
public:
	Draw::Draw();
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
	bool isCirclePointvalue(ci::Vec2f circlepos, ci::Vec2f pointpos, float circlesize, float& value, float underlimit = 0.0f);
	void drawSample();
	void drawColorPallet();
	void testup();
	void check();
	void drawcheckpoint();
	float check_rate_value = 0.f;
	//std::vector<std::vector<bool>>isdraw;
};