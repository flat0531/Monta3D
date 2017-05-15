#include "ColorObject.h"
using namespace ci;
using namespace ci::app;
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
ColorObject::ColorObject()
{
}

ColorObject::ColorObject(ci::Vec2f _trancepos, ci::Vec2f _palletpos, ci::Vec2f _size, ci::ColorA _color, bool _isnecessary)
{
	trancepos = _trancepos;
	palletpos = _palletpos;
	pos = palletpos + trancepos;
	size = _size;
	color = _color;
	isnecessary = _isnecessary;
	isselected = false;
	easingpos = Vec2f(0, 0);
}

ci::ColorA ColorObject::getColor()
{
	return color;
}

bool ColorObject::getIsnecessary()
{
	return isnecessary;
}

ci::Vec2f ColorObject::getPos()
{
	return pos;
}

ci::Vec2f ColorObject::getSize()
{
	return size;
}

ci::Vec2f ColorObject::getLeftUpPos()
{
	return pos - (size / 2.f);
}

void ColorObject::SetIsselected(bool _isselected)
{
	isselected = _isselected;
}

void ColorObject::update(const ci::Vec2f _palletpos)
{
	move(palletpos);
	pos = _palletpos + trancepos + easingpos;
}

void ColorObject::drawCircle()
{
	DrawM.drawTextureBox(pos, size,0, TextureM.getTexture("UI/paintpen.png"),ColorA(1,1,1,1));
	DrawM.drawTextureBox(pos, size, 0, TextureM.getTexture("UI/color.png"), color);
}

void ColorObject::drawNecessaryIcon()
{
	if (isnecessary) {

	}
}

void ColorObject::move(const ci::Vec2f _palletpos)
{
	easingpos.y = EasingManager::getEas[EasingManager::SineInOut](t, 0.f, -size.y*0.25f);
	if (isselected) {
		EasingManager::tCount(t, 0.1f);
	}
	else {
		EasingManager::tCount(t, -0.1f);
	}
	
}
