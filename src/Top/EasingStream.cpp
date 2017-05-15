#include "EasingStream.h"

void EasingStream::update()
{
	for (int i = 0;i < easingobjs.size();i++) {
		easingobjs[i].update();
	}
	for (int i = 0;i < easingobjs.size();i++) {
		if (easingobjs[i].easingEnd()) {
			easingobjs.erase(easingobjs.begin() + i);
		}
		
	}
}

void EasingStream::Create(float * value, float _start, float _end, EasingManager::EasType _type, float time, float _t)
{
	easingobjs.push_back(EasingObj(value, _start, _end, _type, _t));
}
