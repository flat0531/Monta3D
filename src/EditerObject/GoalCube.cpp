#include "GoalCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
using namespace ci;
using namespace ci::app;

GoalCube::GoalCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void GoalCube::draw()
{
	DrawM.drawStrokeCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), ci::ColorA(0, 0, 1, 1));
}
