#include "BreakCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
#include"../Top/TextureManager.h"
BreakCube::BreakCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void BreakCube::draw()
{
	DrawM.drawTextureCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), TextureM.getTexture("Map/renga.png"), ci::ColorA(1, 1, 1, 1));
}
