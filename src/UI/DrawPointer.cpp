#include "DrawPointer.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"

#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../Input/MouseMamager.h"
using namespace ci;
using namespace ci::app;
DrawPointer::DrawPointer()
{
	pos = MouseManager::getMouse().getmousepos();
	iscircledraw = true;
	createAsset();
	circlecolor = ColorA(1, 1, 0, 0.5f);
	circlesize = 30;
}

void DrawPointer::draw()
{
	if (iscircledraw) {
		DrawM.drawTextureBox(pos, Vec2f(circlesize, circlesize)*2.1f, 0.0f, TextureM.getTexture("UI/circlrepoint.png"), circlecolor);
		DrawM.drawTextureBox(pos, Vec2f(circlesize, circlesize)*2.1f, 0.0f, TextureM.getTexture("UI/circlrepointaround.png"), ColorA(1,1,1,1));
	}
	
	//DrawM.drawTextureBox(pos, Vec2f(100, 100), 0, TextureM.getTexture("UI/pointer.png"), ColorA(1, 1, 1, 1));
}

void DrawPointer::update()
{
	pos = MouseManager::getMouse().getmousepos();
}

ci::Vec2f DrawPointer::getPos()
{
	return pos;
}

float DrawPointer::getCircleSize()
{
	return circlesize;
}

void DrawPointer::setIsCircledraw(bool _iscircledraw)
{
	iscircledraw = _iscircledraw;
}

void DrawPointer::setCircleColor(ci::ColorA _color)
{
	circlecolor = _color;
}

void DrawPointer::setCircleSize(float const _circlesize)
{
	circlesize = _circlesize;
}

void DrawPointer::createAsset()
{
	TextureM.CreateTexture("UI/pointer.png");
	TextureM.CreateTexture("UI/circlrepoint.png");
	TextureM.CreateTexture("UI/circlrepointaround.png");
}

