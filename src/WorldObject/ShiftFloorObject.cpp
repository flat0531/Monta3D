#include "ShiftFloorObject.h"
#include"../Top/CollisionManager.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;

ShiftFloorObject::ShiftFloorObject()
{
}

ShiftFloorObject::ShiftFloorObject(const ci::Vec3f _pos, const ci::Vec3f _size, const int _nextfloornum, const ci::Vec3f _nextplayerpos)
{
	pos = _pos;
	size = _size;
	nextfloornum = _nextfloornum;
	nextplayerpos = _nextplayerpos;
}

ci::Vec3f ShiftFloorObject::getPos()
{
	return pos;
}

ci::Vec3f ShiftFloorObject::getSize()
{
	return size;
}

int ShiftFloorObject::getNextFloorNum()
{
	return nextfloornum;
}

ci::Vec3f ShiftFloorObject::getNextPlayerPos()
{
	return nextplayerpos;
}

void ShiftFloorObject::draw()
{
	DrawM.drawStrokeCube(pos, size, Vec3f(0, 0, 0), ColorA(0, 1, 0, 1));
}
