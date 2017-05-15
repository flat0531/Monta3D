#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include "../../WorldObject/Map2d.h"
#include"../../Top/SurfaceEffect.h"
class Title :public SceneBase {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;

	ci::Vec3f skyrotate;
	ci::Vec3f skypos;
	std::vector<Map2d> map2d;
	std::vector<Map2d> map2dfront;
	SurfaceEffect surfaceeffect;
	SurfaceEffect backsurface;
	SurfaceEffect framesurface;
	void updateSky();
	void drawSky();
	void CreateMap2d();
	void drawmap2d();
	void drawmap2dFront();
	int delay=120;
	int delaycount = 0;
	int testtexturenum = 3;
	int testtexturecount = 0;
};