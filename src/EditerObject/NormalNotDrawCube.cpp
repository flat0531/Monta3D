#include "NormalNotDrawCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
NormalNotDrawCube::NormalNotDrawCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void NormalNotDrawCube::draw()
{
	DrawM.drawStrokeCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), ci::ColorA(1, 0, 0, 1));
}
