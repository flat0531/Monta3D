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
	//pos = Vec2f(WINDOW_WIDTH/2, WINDOW_HEIGHT/2);
	pos = MouseManager::getMouse().getmousepos();
	iscircledraw = true;
	TextureM.CreateTexture("UI/pointer.png");
	TextureM.CreateTexture("UI/circlrepoint.png");
	TextureM.CreateTexture("UI/circlrepointaround.png");
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
	//float speed = 5.0f;
	//if (KeyManager::getkey().isPress(KeyEvent::KEY_k)) {
	//	speed = 1.0f;
	//}
	//Vec2f vec = Vec2f(0, 0);
	//if (KeyManager::getkey().isPress(KeyEvent::KEY_w)) {
	//	vec.y -= speed;
	//}
	//if (KeyManager::getkey().isPress(KeyEvent::KEY_s)) {
	//	vec.y += speed;
	//}
	//if (KeyManager::getkey().isPress(KeyEvent::KEY_a)) {
	//	vec.x -= speed;
	//}
	//if (KeyManager::getkey().isPress(KeyEvent::KEY_d)) {
	//	vec.x += speed;
	//}
	//pos += vec;
	//pos.x = std::min(pos.x, float(WINDOW_WIDTH));
	//pos.x = std::max(pos.x, 0.0f);
	//pos.y = std::min(pos.y, float(WINDOW_HEIGHT));
	//pos.y = std::max(pos.y, 0.0f);
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

