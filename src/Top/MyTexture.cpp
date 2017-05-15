#include "MyTexture.h"
using namespace ci;
using namespace ci::app;

MyTexture::MyTexture()
{
	//console() << "コンスト" << std::endl;
}

MyTexture::~MyTexture()
{
	//console() << "デスト : " << name << std::endl;
}


MyTexture::MyTexture(const std::string name)
{
	this->name = name;
	tex = loadImage(loadAsset("Texture/" + name));
}

ci::gl::Texture const& MyTexture::getTex()
{
	return tex;
}

void MyTexture::Clear()
{

}

void MyTexture::Set(const std::string name)
{
	tex = loadImage(loadAsset("Texture/" + name));
}
