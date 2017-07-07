#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/Ray.h"
class MapChipManager;

class ShadowManager {
public:
	ShadowManager();
	ShadowManager* getThisPtr();
	void draw(const ci::Vec3f pos,const ci::Vec3f scale);///オブジェクトのPOSとSCALEを取得して影を描画
	void setMapChipManager(MapChipManager* mapchipmanager);
private:
	MapChipManager* mapchipmanagerptr;
};