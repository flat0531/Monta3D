#include "StageIcon.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"

using namespace ci;
using namespace ci::app;

StageIcon::StageIcon()
{

}

StageIcon::StageIcon(const ci::Vec2f _pos, const ci::Vec2f _size, const ci::ColorA _color, const bool _isclear,const int _number)
{
	pos = _pos;
	size = _size;
	beginsize = _size;
	endsize = _size*1.3f;
	number = _number;
	isclear = _isclear;

	if (isclear) {
		defaltcolor = ColorA(0, 0, 1, 1);
	}
	else {
		defaltcolor = _color;
	}
	
	colorangle = 0.0f;

	TextureM.CreateTexture("UI/circlrepoint.png");
}

void StageIcon::update(const bool ismoving, const int selectstagenum)
{
	if ((!ismoving) && (selectstagenum == number)) {
		EasingManager::tCount(scale_t,0.3f);
		
	}else{
		EasingManager::tCount(scale_t, -0.3f);
	}
	size.x = EasingCubicOut(scale_t, beginsize.x, endsize.x);
	size.y = EasingCubicOut(scale_t, beginsize.y, endsize.y);

	colorangle += 0.05f;
	float addcolor = 1.1f + 0.2f*sin(colorangle);
	color = ColorA(defaltcolor.r/addcolor, defaltcolor.g / addcolor, defaltcolor.b / addcolor, 1);
}

void StageIcon::draw()
{
	DrawM.drawTextureBox(pos, (size*1.2f), 0, TextureM.getTexture("UI/circlrepoint.png"), ColorA(1, 1, 1, 1));
	DrawM.drawTextureBox(pos, size, 0, TextureM.getTexture("UI/circlrepoint.png"), color);
	
}
