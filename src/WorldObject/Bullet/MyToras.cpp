#include "MyToras.h"
#include"../../Top/DrawManager.h"
MyToras::MyToras(ci::Vec3f _scale, ci::Vec3f _rotate, ci::Vec3f _rotatespeed, float _sizeangle, ci::ColorA _color)
{
	scale = _scale;
	startscale = scale;
	sizeangle = _sizeangle;
	rotate = _rotate;
	rotatespeed = _rotatespeed;
	color = _color;
}

void MyToras::draw(const ci::Vec3f _pos)
{
	DrawM.drawTaurus(_pos, scale.x*0.6f, scale.x*0.1f, rotate, color);
}

void MyToras::update()
{
	rotate += rotatespeed;
	float sizespeed = 0.4f;
	sizeangle += sizespeed;
	scale = startscale*(0.6f + 0.4f*cos(sizeangle));
}

void MyToras::setScale(const ci::Vec3f _scale)
{
	scale = _scale;
}

