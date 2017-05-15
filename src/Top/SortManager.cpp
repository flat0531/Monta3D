#include "SortManager.h"

void SortManager::setSortCount(const float count)
{
	sortcount = count;
}

void SortManager::SortCountUp()
{
	float countupvalue = 0.01f;
	sortcount += countupvalue;
}

float SortManager::getSortCount()
{
	return sortcount;
}
