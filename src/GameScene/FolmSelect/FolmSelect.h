#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include"../../UI/UICreater.h"
#include"../../UI/FolmTextureList.h"
class FolmSelect :public SceneBase {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	UICretaer uicreater;
	bool isfadein = false;
	bool isselect = false;
	bool isyes = true;
	void shiftScene();
	void select();
	void updateWindow();
	void updateButton();
	void drawButton();
	void drawWindow();
	void createAsset();
	FolmTextureList folmtexturelist;
};
