#include "EffectFlashBack.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DataManager.h"
using namespace ci;
using namespace ci::app;


EffectFlashBack::EffectFlashBack()
{
}

EffectFlashBack::EffectFlashBack(const float _time, const ci::ColorA _color)
{
	t = 0.0f;
	time = _time;

	color = ColorA(_color.r, _color.g, _color.b, 0.0f);
}

void EffectFlashBack::update()
{
	EasingManager::tCount(t, time);
	color.a = EasingReturn(t, 0.f, 1.f);

}

void EffectFlashBack::draw(const ci::CameraPersp camera)
{
	DrawM.drawBoxEdge(Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT), color);
}

bool EffectFlashBack::deleteThis()
{
	return EasingManager::tCountEnd(t);
}
