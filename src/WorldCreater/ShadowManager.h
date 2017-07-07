#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/Ray.h"
class MapChipManager;

class ShadowManager {
public:
	ShadowManager();
	ShadowManager* getThisPtr();
	void draw(const ci::Vec3f pos,const ci::Vec3f scale);///�I�u�W�F�N�g��POS��SCALE���擾���ĉe��`��
	void setMapChipManager(MapChipManager* mapchipmanager);
private:
	MapChipManager* mapchipmanagerptr;
};