#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"InformationWindow.h"
#include<vector>
#include<memory>
class InformationWindowList {
public:
	InformationWindowList();
	void update();
	void draw();
	bool isEnd();
	void CreateInformationWindows();
private:
	std::vector<std::shared_ptr<InformationWindow>>informationwindows;
};
