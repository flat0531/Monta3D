#include "FolmScenePlayTexture.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;
FolmScenePlayTexture::FolmScenePlayTexture()
{
}

FolmScenePlayTexture::FolmScenePlayTexture(const ci::Vec2f _pos, const ci::Vec2f _size, const std::string path, const std::string _name)
{
	pos = _pos;
	size = _size;
	tex = TextureM.CreateTexture(path);
	basetex = TextureM.CreateTexture("Draw/frame.png");
	frametex = TextureM.CreateTexture("Draw/" + _name + "/frame.png");
}


void FolmScenePlayTexture::draw()
{
	DrawM.drawTextureBox(pos, size, 0.0f, basetex, ColorA(1, 1, 1, 1));
	DrawM.drawTextureBox(pos, size, 0.0f, tex, ColorA(1, 1, 1, 1));
	DrawM.drawTextureBox(pos, size, 0.0f, frametex, ColorA(1, 1, 1, 1));

}
