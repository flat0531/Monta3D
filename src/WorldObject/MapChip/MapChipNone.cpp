#include "MapChipNone.h"

MapChipNone::MapChipNone(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = false;
	aabb = ci::AxisAlignedBox3f(pos - scale / 2.f, pos + scale / 2.f);
}

void MapChipNone::draw()
{
}

void MapChipNone::update()
{
}
