#include "BulletBase.h"

ci::ColorA BulletBase::getUniqueColor()
{
	return uniquecolor;
}

void BulletBase::setUniqueColor(const ci::ColorA color)
{
	uniquecolor = color;
}
