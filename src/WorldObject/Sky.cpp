#include "Sky.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;

Sky::Sky()
{
}

Sky::Sky(const ci::Vec3f _pos, const ci::Vec3f _scale, const ci::Vec3f _rotate, const ci::ColorA _color, const std::string _texturepath)
{
	pos = _pos;
	scale = _scale;
	rotate = _rotate;
	color = _color;
	texturepath = _texturepath;
	TextureM.CreateTexture(texturepath);
	isrotate = false;
}

void Sky::setup()
{
}

void Sky::update()
{
}

void Sky::draw()
{
	gl::disable(GL_CULL_FACE);
	DrawM.drawTextureSphere(pos, scale, rotate, 20, TextureM.getTexture(texturepath), color);
	gl::enable(GL_CULL_FACE);
}

void Sky::Rotate(const ci::Vec3f _rotate)
{
	if(isrotate)
	rotate += _rotate;
}

void Sky::setIsRotate(const bool _is)
{
	isrotate = _is;
}

void Sky::setRotation(const ci::Vec3f _rotate)
{
	rotate = _rotate;
}
