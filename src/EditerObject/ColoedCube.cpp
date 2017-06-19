#include "ColoedCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
#include"../Top/TextureManager.h"
ColoredCube::ColoredCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void ColoredCube::draw()
{
	DrawM.drawCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), ci::ColorA(1, 1, 0, 1));
}
