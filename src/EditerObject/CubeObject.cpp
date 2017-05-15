#include "CubeObject.h"
#include"../WorldObject/MapChip/MapChipType.h"
CubeObject::CubeObject()
{
}

CubeObject::CubeObject(const ci::Vec3f _pos,const ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
}

ci::AxisAlignedBox3f CubeObject::getAABB()
{
	ci::AxisAlignedBox3f buf(pos - scale / 2.f, pos + scale / 2.f);
	return buf;
}

CubeObject * CubeObject::getThisPtr()
{
	return this;
}

void CubeObject::draw()
{
	cube->draw();
}

ci::Vec3f CubeObject::getPos()
{
	return pos;
}

ci::Vec3f CubeObject::getScale()
{
	return scale;
}

void CubeObject::setScale(const ci::Vec3f _scale)
{
	scale = _scale;
}

void CubeObject::setMapChipType(const MapChipType _mapchiptype)
{
	mapchiptype = _mapchiptype;
}

MapChipType CubeObject::getMapChiptype()
{
	return mapchiptype;
}
