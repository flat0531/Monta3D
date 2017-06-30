#include "EffectBlackBox.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
using namespace ci;
using namespace ci::app;
EffectBlackBox::EffectBlackBox()
{

}

EffectBlackBox::EffectBlackBox(const float _easingtime, const float _deleytime)
{
	easingtime[0] = _easingtime;
	easingtime[1] = _deleytime;
	easingtime[2] = _easingtime;
	setSize();
	for (int i = 0;i < 3;i++) {
		t[i] = 0.0f;
	}
}

void EffectBlackBox::update()
{
	for (int i = 0;i < 3;i++) {
		if (EasingManager::tCountEnd(t[i]))continue;
		EasingManager::tCount(t[i],easingtime[i]);
		upboxsize.x = EasingLinear(t[i],beginupboxsize[i].x, endupboxsize[i].x);
		upboxsize.y = EasingLinear(t[i], beginupboxsize[i].y, endupboxsize[i].y);
		downboxsize.x = EasingLinear(t[i], begindownboxsize[i].x, enddownboxsize[i].x);
		downboxsize.y = EasingLinear(t[i], begindownboxsize[i].y, enddownboxsize[i].y);
		break;
	}
}

void EffectBlackBox::draw(const ci::CameraPersp camera)
{
	DrawM.drawBoxEdge(Vec2f(0, 0), upboxsize, ColorA(0, 0, 0, 1));
	DrawM.drawBoxEdge(Vec2f(0, WINDOW_HEIGHT), downboxsize, ColorA(0, 0, 0, 1));
}

bool EffectBlackBox::deleteThis()
{
	return EasingManager::tCountEnd(t[2]);
}

void EffectBlackBox::setSize()
{
	Vec2f beginsize = Vec2f(WINDOW_WIDTH, 0);
	Vec2f endsizeup = Vec2f(WINDOW_WIDTH, 85);
	Vec2f endsizedown = Vec2f(WINDOW_WIDTH, -235);
	beginupboxsize[0] = beginsize;
	beginupboxsize[1] = endsizeup;
	beginupboxsize[2] = endsizeup;
	begindownboxsize[0] = beginsize;
	begindownboxsize[1] = endsizedown;
	begindownboxsize[2] = endsizedown;
	endupboxsize[0] = endsizeup;
	endupboxsize[1] = endsizeup;
	endupboxsize[2]= beginsize;
	enddownboxsize[0] = endsizedown;
	enddownboxsize[1] = endsizedown;
	enddownboxsize[2] = beginsize;
}
