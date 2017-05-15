#pragma once
#include"EasingManager.h"

class EasingObj {
public:
	EasingObj::EasingObj();
	EasingObj::EasingObj(float *value,float _start, float _end, EasingManager::EasType _type,float _t=0.0f);
	void update();
	bool easingEnd();
private:
	float t;
	float start;
	float end;
	EasingManager::EasType type;
	float *value_;
};