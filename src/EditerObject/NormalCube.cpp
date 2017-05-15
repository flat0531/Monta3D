#include "NormalCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
#include"../Top/TextureManager.h"
NormalCube::NormalCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void NormalCube::draw()
{
	DrawM.drawTextureCube(cubeobjectptr->getPos(), cubeobjectptr->getScale(), ci::Vec3f(0, 0, 0), TextureM.getTexture("Map/normalbox.png"), ci::ColorA(1, 1, 1, 1));
}
