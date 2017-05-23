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
	void Create2dMap(const ci::JsonTree& _json);
	
	void CreateWorld(const ci::JsonTree& _json);
	void CreateSky(const ci::JsonTree& _json);
	void CreateLine(const ci::JsonTree& _json);
	void CreateLineWall(const ci::JsonTree& _json);
	void CreateLineSlope(const ci::JsonTree& _json);
	std::string getPath(const int world, const int stage, const int floor);
	void CreateTexutreObj(const ci::JsonTree& _json);
	void drawSky();
	void drawMap2d();
	void drawMap2dFront();
	void drawTexureObjct(const ci::CameraPersp& camera);
	std::vector<Line> getline() {
		return lines;
	}
	std::vector<VerticalLine> getverticalline() {
		return verticallines;
	}
private:
	std::vector<Sky> skyobj;
	std::vector<Map2d> map2dobj;
	std::vector<Map2d> map2frontobj;
	std::vector<Line> lines;
	std::vector<std::shared_ptr<TextureObj>> textureobject;
	std::vector<VerticalLine> verticallines;
	ci::Vec3f getVec3(const ci::JsonTree& _json,const std::string key);
	ci::ColorA getColor(const ci::JsonTree& _json, const std::string key);
};