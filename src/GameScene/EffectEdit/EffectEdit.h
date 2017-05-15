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
class EffectEdit :public SceneBase {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	struct MousePosPress
	{
		ci::Vec2i pos;
		bool ispress;
	};
	std::string createname;
	ci::Surface surface;
	ci::Surface texturesurface;
	int pixceldrawsize = 60;
	bool issaving = false;
	bool isreplay = false;
	std::vector<MousePosPress>savepos;
	ci::Vec2i texturesize;
	int replaycount;
	void baseDraw();
	void Drawsurface();
	void updateSurface();
	void writeMousepos();
	void startReplay();
	void ReplayEffect();
	void resetSurface();
	void saveStart();
	void saveStop();
	void loadMousePos();
};