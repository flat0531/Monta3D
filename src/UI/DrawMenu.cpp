#include "DrawMenu.h"
#include "../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Input/MouseMamager.h"
#include"../Top/CollisionManager.h"
#include"../Top/Top.h"
using namespace ci;
using namespace ci::app;
DrawMenu::DrawMenu()
{
	TextureM.CreateTexture("UI/drawmenu.png");
	size = Vec2f(350,620);
	pos = Vec2f(WINDOW_WIDTH-size.x/2.0f*1.1f, WINDOW_HEIGHT/2);
	sizerange = Range(Vec2f(WINDOW_WIDTH - size.x / 2.0f*1.1f,350), 300, Vec2f(40, 40), "UI/bar.png", "UI/circlrepoint.png", 1.f, 70.f, 0.5f);
}

void DrawMenu::draw()
{
	drawBackGround();
	drawSampleCircle();
	sizerange.draw();
}

void DrawMenu::update()
{
	if (MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN)) {
		Vec2f mousepos = MouseManager::getMouse().getmousepos();
		if (CollisionM.isBoxPoint(mousepos, sizerange.getIconLeftUpPos(), sizerange.getIconSize())) {
			sizerange.setIsTouch(true);
		}
	}
	if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
		sizerange.setIsTouch(false);
	}
	sizerange.update();
}

float DrawMenu::getSizeRangeValue()
{
	return sizerange.getIconValue();
}

void DrawMenu::setSampleCircleSize(float size)
{
	circlesize = size;
}

void DrawMenu::setCircleColor(ci::ColorA _color)
{
	circlecolor = _color;
}

void DrawMenu::drawBackGround()
{
	DrawM.drawTextureBox(pos,size,0,TextureM.getTexture("UI/drawmenu.png"),ColorA(0.7,1.0,0.7,1.0));
}

void DrawMenu::drawSampleCircle()
{
	Vec2f circlepos = pos + Vec2f(100,-200);
	DrawM.drawTextureBox(circlepos, Vec2f(circlesize, circlesize)*2.f, 0.0f, TextureM.getTexture("UI/circlrepoint.png"), circlecolor);
	DrawM.drawTextureBox(circlepos, Vec2f(circlesize, circlesize)*2.f, 0.0f, TextureM.getTexture("UI/circlrepointaround.png"), ColorA(1, 1, 1, 1));
}
