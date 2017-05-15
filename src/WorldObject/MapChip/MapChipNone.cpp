#include "MapChipNone.h"

MapChipNone::MapChipNone(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = false;
}

void MapChipNone::draw()
{
}

void MapChipNone::update()
{
}
