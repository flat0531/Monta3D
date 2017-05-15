#include "HitBox.h"
#include"../../WorldObject/MapChip/MapChipBase.h"

HitBox::HitBox(ci::Vec2f _pos, ci::Vec2f _size, float _distance, MapChipBase * _mapchipptr)
{
	pos = _pos;
	size = _size;
	distance = _distance;
	mapchipptr = _mapchipptr;
}

ci::Vec2f HitBox::getPos()
{
	return pos;
}

ci::Vec2f HitBox::getSize()
{
	return size;
}

float HitBox::getDistance()
{
	return distance;
}

MapChipBase * HitBox::getMapChipPtr()
{
	return mapchipptr;
}
