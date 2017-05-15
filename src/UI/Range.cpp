#include "Range.h"
#include"../Input/MouseMamager.h"
#include"../Top/EasingManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
Range::Range()
{
}

Range::Range(ci::Vec2f _centerpos, float _length, ci::Vec2f _iconsize, std::string _rangetexturepath, std::string _icontexturepath, float _minvalue, float _maxvalue, float _rangevalue)
{
	centerpos = _centerpos;
	length = _length;
	startpos = Vec2f(centerpos.x - length/2.f, centerpos.y);
	endpos = Vec2f(centerpos.x + length / 2.f, centerpos.y);
	iconsize = _iconsize;
	minvalue = _minvalue;
	maxvalue = _maxvalue;
	rangevalue = _rangevalue;
	iconpos.x = EasingLinear(rangevalue, startpos.x, endpos.x);
	iconpos.y = centerpos.y;
	rangetexturepath = _rangetexturepath;
	icontexturepath = _icontexturepath;
	TextureM.CreateTexture(rangetexturepath);
	TextureM.CreateTexture(icontexturepath);
	istouch = false;
}

void Range::update()
{
	if (!istouch)return;
	Vec2f mousepos = MouseManager::getMouse().getmousepos();
	lookpos = mousepos;
	lookpos.x = std::max(lookpos.x, startpos.x);
	lookpos.x = std::min(lookpos.x, endpos.x);
	rangevalue = (lookpos.x - startpos.x) / length;
	iconpos.x = EasingLinear(rangevalue, startpos.x, endpos.x);
}

void Range::draw()
{
	DrawM.drawTextureBox(centerpos,Vec2f(length,30),0,TextureM.getTexture(rangetexturepath),ColorA(1,1,1,1));
	DrawM.drawTextureBox(iconpos,iconsize, 0, TextureM.getTexture(icontexturepath), ColorA(1, 1, 1, 1));
}

float Range::getRangeValue()
{
	return rangevalue;
}

float Range::getIconValue()
{
	float iconvalue = EasingLinear(getRangeValue(), minvalue, maxvalue);
	return iconvalue;
}

void Range::setIsTouch(bool _istouch)
{
	istouch = _istouch;
}

ci::Vec2f Range::getIconLeftUpPos()
{
	float x = iconpos.x - iconsize.x / 2.f;
	float y = iconpos.y - iconsize.y / 2.f;
	return Vec2f(x, y);
}

ci::Vec2f Range::getIconSize()
{
	return iconsize;
}

void Range::setRangeValue(const float _rangevalue)
{
	rangevalue = _rangevalue;
	iconpos.x = EasingLinear(rangevalue, startpos.x, endpos.x);
}

void Range::AddRangevalue(const float addvalue)
{
	rangevalue += addvalue;
	if (rangevalue >= 1)rangevalue = 1.0f;
	if (rangevalue <= 0)rangevalue = 0.0f;
	iconpos.x = EasingLinear(rangevalue, startpos.x, endpos.x);
}
