#pragma once
#include"Point.h"
#include"../Top/EasingManager.h"
#include<vector>
class PointRoad {
public:
	PointRoad();
	PointRoad(ci::Vec2f _beginpos, ci::Vec2f _endpos,EasingManager::EasType _x_type, EasingManager::EasType _y_type);
	void draw();
	void update();
	ci::Vec2f getPos(float t);
private:
	void createPoint();
	int count = 0;
	std::vector<Point>points;
	ci::Vec2f beginpos;
	ci::Vec2f endpos;
	EasingManager::EasType x_type;
	EasingManager::EasType y_type;
	float t = 0.0f;
	int createnum;
};