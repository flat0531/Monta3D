#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder\Json.h"
#include "../WorldObject/Sky.h"
#include "../WorldObject/Map2d.h"
#include"../WorldObject/Line.h"
#include"../WorldObject/VerticalLine.h"
#include"cinder/Camera.h"
#include<memory>
class TextureObj;
class MapManager {
public:
	MapManager();
	void ReadData(const int world,const int stage,const int floor);
	void CreateWorld(const ci::JsonTree& _json);
	void CreateSky(const ci::JsonTree& _json);
	std::string getPath(const int world, const int stage, const int floor);
	void CreateTexutreObj(const ci::JsonTree& _json);////2Dテクスチャーを３D座標に生成
	void drawSky();
	void rotateSky(const ci::Vec3f _rotate);
	void drawTexureObjct(const ci::CameraPersp& camera);
private:
	std::vector<Sky> skyobj;
	std::vector<std::shared_ptr<TextureObj>> textureobject;
};