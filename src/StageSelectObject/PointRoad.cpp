#include "PointRoad.h"
using namespace ci;
using namespace ci::app;
PointRoad::PointRoad()
{
}

PointRoad::PointRoad(ci::Vec2f _beginpos, ci::Vec2f _endpos, EasingManager::EasType _x_type, EasingManager::EasType _y_type)
{
	beginpos = _beginpos;
	endpos = _endpos;
	x_type = _x_type;
	y_type = _y_type;
	createnum = 100;
}

void PointRoad::draw()
{
	for (auto it : points) {
		it.draw();
	}
}

void PointRoad::update()
{
	for (auto& it : points) {
		it.update();
	}
	count++;
	if ((count % 2 == 0)&&(points.size()<createnum)) {
		createPoint();
	}

}

ci::Vec2f PointRoad::getPos(float t)
{
	float x = EasingManager::getEas[x_type](t,beginpos.x,endpos.x);
	float y = EasingManager::getEas[x_type](t, beginpos.y, endpos.y);
	return ci::Vec2f(x, y);
}

void PointRoad::createPoint()
{
	Vec2f pos;
	pos.x = EasingManager::getEas[x_type](t, beginpos.x, endpos.x);
	pos.y = EasingManager::getEas[y_type](t, beginpos.y, endpos.y);
	Vec2f size = Vec2f(25, 20);
	if (points.size() == 0 || points.size() == (createnum - 1)) {
		points.push_back(Point(pos, size, 0.0f));
	}
	else {
		Vec2f prevpos;
		Vec2f nextpos;
		prevpos.x = EasingManager::getEas[x_type](t - (1 / (createnum - 1.f)), beginpos.x, endpos.x);
		prevpos.y = EasingManager::getEas[y_type](t - (1 / (createnum - 1.f)), beginpos.y, endpos.y);
		nextpos.x = EasingManager::getEas[x_type](t + (1 / (createnum - 1.f)), beginpos.x, endpos.x);
		nextpos.y = EasingManager::getEas[y_type](t + (1 / (createnum - 1.f)), beginpos.y, endpos.y);
		float angle = std::atan2f(nextpos.y - prevpos.y, nextpos.x - prevpos.x) + M_PI / 2.f;
		points.push_back(Point(pos, size, angle*(180.f/M_PI)));
	}
	
	
	t += 1 / (createnum - 1.f);
}
