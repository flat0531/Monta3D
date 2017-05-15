#include "NoneCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
NoneCube::NoneCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void NoneCube::draw()
{
	DrawM.drawStrokeCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), ci::ColorA(1, 1, 1, 1));
}
