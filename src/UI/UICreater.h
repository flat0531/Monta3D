#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"UIObject.h"
#include<vector>
class UICretaer {
public:
	UICretaer();
	void CreateUI(const std::string path);
	void draw();
private:
	std::vector<UIObject>uiobjects;
};