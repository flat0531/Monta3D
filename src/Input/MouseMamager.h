#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\app\MouseEvent.h"
#include<set>
class MouseManager {
public:
	void registerDown(ci::app::MouseEvent& _event);
	void registerUp(ci::app::MouseEvent& _event);
	void registerEnd();
	void registerMove(ci::app::MouseEvent& _event);
	void registerWheel(ci::app::MouseEvent& _event);
	bool isPress(const int& _event);
	bool isPush(const int& _event);
	bool isPull(const int& _event);
	cinder::Vec2i getmousepos();
	float getWheelIncrement();
	static MouseManager& getMouse() {
		static MouseManager manager;
		return manager;
	}
private:
	std::set<int> push;
	std::set<int> press;
	std::set<int> pull;
	cinder::Vec2i mousepos;
	float wheel_increment;
};