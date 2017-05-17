#include "AppleCube.h"
#include"../Top/DrawManager.h"
#include"CubeObject.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
AppleCube::AppleCube(CubeObject * ptr)
{
	cubeobjectptr = ptr;
	TextureM.CreateTexture("Mesh/apple.png");
	TextureM.CreateMesh("apple.obj");
}

void AppleCube::draw()
{
	float scalerate = 0.018f;
	gl::pushModelView();
	gl::translate(cubeobjectptr->getPos()+ci::Vec3f(0, -cubeobjectptr->getScale().y/2.f,0));
	gl::scale(cubeobjectptr->getScale()*scalerate);
	gl::rotate(Vec3f(0,0,0));
	gl::color(ColorA(1,1,1,1));
	TextureM.getTexture("Mesh/apple.png").enableAndBind();
	gl::draw(TextureM.getMesh("apple.obj"));
	TextureM.getTexture("Mesh/apple.png").disable();
	gl::popModelView();
}
