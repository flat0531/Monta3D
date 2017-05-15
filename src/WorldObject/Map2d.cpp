#include "Map2d.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
Map2d::Map2d(const ci::Vec3f _pos, const ci::Vec3f _scale, const ci::Vec3f _rotate, const ci::ColorA _color, const std::string _texturepath)
:tex(TextureM.CreateTexture(_texturepath)){
	pos = _pos;
	startpos = _pos;
	centerpos = Vec3f(0,0,0);
	scale = _scale;
	rotate = _rotate;
	startrotate = rotate;
	color = _color;
	texturepath = _texturepath;
	for (int i = 0;i < int(Map2dUpdatetype::Map2dNONE) - 1;i++) {
		isupdate[i] = false;
	}
}

void Map2d::setuptrancerate(const ci::Vec3f _vec)
{
	isupdate[Map2dUpdatetype::Map2dTRANCERATE] = true;
	vec = _vec;
}

void Map2d::setupRotate(const ci::Vec3f _rotatespeed)
{
	isupdate[Map2dUpdatetype::Map2dROTATE] = true;
	rotatespeed = _rotatespeed;
}

void Map2d::setupRotateReturn(const Vec3f _centerpos, const float _maxangle,const float _return_speed,const float _statrtrotate)
{
	isupdate[Map2dUpdatetype::Map2dROTATE_RETURN] = true;
	centerpos = _centerpos;
	maxangle = _maxangle;
	return_speed = _return_speed;
	return_angle = _statrtrotate;
}

void Map2d::setupCircle(const Vec2f _size, const float _circlespeed)
{
	isupdate[Map2dUpdatetype::Map2dCIRCLE] = true;
	circlesize = _size;
	circle_speed = _circlespeed;
}

void Map2d::updatetrancerate()
{
	pos += vec;
}

void Map2d::updateRotate()
{
	rotate += rotatespeed;
}

void Map2d::updateRotateReturn()
{
	rotate = Vec3f(rotate.x, rotate.y, startrotate.z + maxangle*sin(return_angle));
	return_angle += return_speed;
	if (return_angle > 2 * M_PI)return_angle -= 2 * M_PI;
}

void Map2d::updateCircle()
{
	pos = startpos + Vec3f(circlesize.x*cos(circle_angle), circlesize.y*sin(circle_angle), 0);
	circle_angle += circle_speed;
}


void Map2d::update()
{
	//console() << vec << std::endl;
	
	if (isupdate[Map2dUpdatetype::Map2dTRANCERATE]) {
	
		
		updatetrancerate();
	}
	if (isupdate[Map2dUpdatetype::Map2dROTATE]) {
		updateRotate();
	}
	if (isupdate[Map2dUpdatetype::Map2dROTATE_RETURN]) {
		updateRotateReturn();
	}
	if (isupdate[Map2dUpdatetype::Map2dCIRCLE]) {
		updateCircle();
	}
}

void Map2d::draw()
{
	DrawM.drawTextureCube(pos, scale, rotate, tex, color,centerpos);
}
