#include "EasingObj.h"
#include "FadeManager.h"
using namespace ci;
using namespace ci::app;
EasingObj::EasingObj()
{

}

EasingObj::EasingObj(float * value, float _start, float _end, EasingManager::EasType _type, float _t)
{
	start = _start;
	end = _end;
	t = _t;
	type = _type;
	value_ = value;
	*value_ = EasingManager::getEas[type](t, start, end);
}

void EasingObj::update()
{
	t += 1 / (1.0f*60.0f);
	if (t >= 1) {
		t = 1.0f;
	}
	*value_ = EasingManager::getEas[type](t, start, end);
}

bool EasingObj::easingEnd()
{
	return t >= 1.0f;
}
