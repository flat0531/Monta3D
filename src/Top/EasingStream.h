#pragma once
#include"EasingManager.h"
#include"EasingObj.h"
#include<vector>
class EasingStream {
public:
	static EasingStream& getEasStr() {
		static EasingStream easingstream;
		return  easingstream;
	}
	void update();
	void Create(float *value, float _start, float _end, EasingManager::EasType _type,float time,float _t = 0.0f);
private:
	std::vector<EasingObj> easingobjs;
};
#define EasStr (EasingStream:: getEasStr(). getEasStr())