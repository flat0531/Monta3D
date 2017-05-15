#pragma once
#include "cinder/gl/gl.h"
class SortManager {
public:
	static SortManager& getSort() {
		static SortManager sortmanager;
		return  sortmanager;
	}
	const float BASESORT = -50.f;
	void setSortCount(const float count);
	void SortCountUp();
	float getSortCount();
private:
	float sortcount = BASESORT;

};
#define SortM (SortManager::getSort().getSort())