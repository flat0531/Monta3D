#include "FolmTexture.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
FolmTexture::FolmTexture()
{
}

FolmTexture::FolmTexture(const ci::Vec2f _pos, const std::string _actionname, bool _isrelease, const int _number)
{
	pos = _pos;
	name = _actionname;
	isrelease = _isrelease;
	number = _number;
	size = Vec2f(230, 230);
	if (isrelease) {
		tex = TextureM.CreateTexture("Draw/" + name + "/" + name + "color.png");
	}
	else {
		tex = TextureM.CreateTexture("Draw/" + name + "/frame.png");
		TextureM.CreateTexture("Draw/frame.png");
	}
	
}

void FolmTexture::update(const int selectnum)
{

}

ci::Vec2f FolmTexture::getPos()
{
	return pos;
}

std::string FolmTexture::getName()
{
	return name;
}

void FolmTexture::draw(const ci::Vec2f trancepos)
{
	if (!isrelease) {
		DrawM.drawTextureBox(pos, size, 0.0f, TextureM.getTexture("Draw/frame.png"), ColorA(1, 1, 1, 1));
	}

	DrawM.drawTextureBox(pos, size, 0.0f, tex, ColorA(1, 1, 1, 1));
}

bool FolmTexture::getIsRelease()
{
	return isrelease;
}
