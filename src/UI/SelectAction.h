#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include"ActionIcon.h"
#include<vector>
class SelectAction {
public:
	SelectAction();
	void update();
	void draw();
private:
	std::vector<ActionIcon>actionaicons;
	void CreateActionICons();
};