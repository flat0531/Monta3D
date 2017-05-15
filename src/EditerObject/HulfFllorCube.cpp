#include "HulfFllorCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
#include"../Top/TextureManager.h"
HulfFllorCube::HulfFllorCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
}

void HulfFllorCube::draw()
{
	ci::Vec3f drawscale = cubeobjectptr->getScale()*ci::Vec3f(1, 0.25f, 1);
	DrawM.drawTextureCube(cubeobjectptr->getPos() + ci::Vec3f(0, cubeobjectptr->getScale().y / 2.f - drawscale.y / 2.f, 0), drawscale, ci::Vec3f(0, 0, 0),
		TextureM.getTexture("Map/hulffloor.png"), ci::ColorA(1, 1, 1, 1));
}
