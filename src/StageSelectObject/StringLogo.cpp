#include "StringLogo.h"
#include"../Top/EasingManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
StringLogo::StringLogo()
{
}

StringLogo::StringLogo(std::string _str, ci::Vec2f _pos, ci::Vec2f _size, float _trance_delay)
{
	TextureM.CreateTexture("UI/stagetitle_" + _str + ".png");
	tex = TextureM.getTexture("UI/stagetitle_" + _str + ".png");
	pos = _pos;
	startpos = _pos;
	size = _size;
	trance_delay_t = _trance_delay;
}

void StringLogo::update()
{
	updatePos();
}

void StringLogo::draw()
{
	DrawM.drawTextureBox(pos, size, angle, tex, ColorA(1, 1, 1, 1));
}

void StringLogo::updatePos()
{
	if (EasingManager::tCountEnd(trance_delay_t)) {
		EasingManager::tCount(trancepos_t,0.2f);
		float y_trance = -45.f;
		pos.y = EasingReturn(trancepos_t, startpos.y, y_trance);
		if (EasingManager::tCountEnd(trancepos_t)) {
			trance_delay_t = 0.0f;
			trancepos_t = 0.0f;
		}
	}
	else {
		EasingManager::tCount(trance_delay_t, 5.0f);
	}
	
}
