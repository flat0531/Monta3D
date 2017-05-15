#include "Point.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
Point::Point()
{
}

Point::Point(const ci::Vec2f _pos, const ci::Vec2f _size, const float _angle)
{
	pos = _pos;
	endsize = _size;
	size = Vec2f(0, 0);
	angle = _angle;
	t = 0.0f;
	color = ColorA(1, 0, 0, 1);
	TextureM.CreateTexture("UI/road.png");
}

void Point::update()
{
	if (!EasingManager::tCountEnd(t)) {
		size.x = EasingBackOut(t, 0, endsize.x);
		size.y = EasingBackOut(t, 0, endsize.y);
		EasingManager::tCount(t,0.5f);

	}
	else {
		sizeangle += 0.1f;
	}
	color = ColorA(1, 0.4f + 0.4f*cos(sizeangle), 0.4f + 0.4f*cos(sizeangle));
}

void Point::draw()
{
	//float sizerate = 1 + 0.05f*cos(sizeangle);
	DrawM.drawBox(pos,(size),angle,ColorA(1,1,0,1));
	DrawM.drawBox(pos, size*Vec2f(0.75f,1.f), angle, color);
	//DrawM.drawTextureBox(pos, size, angle, TextureM.getTexture("UI/road.png"), color);
	//DrawM.drawTextureBox(pos, (size*1.2f), 0, TextureM.getTexture("UI/circlrepoint.png"), ColorA(1,1,0,1));
	//DrawM.drawTextureBox(pos, size, 0, TextureM.getTexture("UI/circlrepoint.png"), color);
}
