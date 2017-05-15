#include "MapChipBase.h"

MapChipBase::MapChipBase()
{
}

ci::Vec3f MapChipBase::getPos3f()
{
	return pos;
}

ci::Vec3f MapChipBase::getScale3f()
{
	return scale;
}

ci::Vec3f MapChipBase::getRotate()
{
	return rotate;
}

ci::Vec2f MapChipBase::getPos2f()
{
	return ci::Vec2f(pos.x,pos.y);
}

ci::Vec2f MapChipBase::getScale2f()
{
	return ci::Vec2f(scale.x,scale.y);
}

bool MapChipBase::getIsCollision()
{
	return iscollision;
}

void MapChipBase::setCollision(bool is)
{
	iscollision = is;
}

float MapChipBase::getDistance()
{
	return distance;
}

void MapChipBase::setDistance(float _distance)
{
	distance = _distance;
}

void MapChipBase::setIsHit(bool is)
{
	ishit = is;
}

bool MapChipBase::getIsHit()
{
	return ishit;
}

bool MapChipBase::getIsActive()
{
	return isactive;
}