#include "ActionIcon.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;

ActionIcon::ActionIcon()
{
}

ActionIcon::ActionIcon(ci::Vec2f _pos, ci::Vec2f _size, std::string _name, bool _isselected)
{
	pos = _pos;
	size = _size;
	name = _name;
	isselected = _isselected;
	std::string pathname = "Snap/" + name + "snap.png";
	snapbase= TextureM.CreateTexture("UI/snapbase.png");
	snaptex = TextureM.CreateTexture(pathname);
	frametex = TextureM.CreateTexture("UI/whiteframe.png");
	framecolor = ColorA(1,1,1,1);
}

void ActionIcon::update()
{
	if (isselected) {
		framecolor = ColorA(1, 1, 0, 1);
	}
	else {
		framecolor = ColorA(1, 1, 1, 1);
	}
}

void ActionIcon::draw()
{
	DrawM.drawTextureBox(pos, size, 0.0f, snapbase);
	DrawM.drawTextureBox(pos, size, 0.0f, snaptex);
	DrawM.drawTextureBox(pos, size, 0.0f, frametex,framecolor);
}

void ActionIcon::setIsSelected(const bool _isselected)
{
	isselected = _isselected;
}

std::string ActionIcon::getName()
{
	return name;
}
