#include "Pallet.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Input/KeyManager.h"
#include"../Input/MouseMamager.h"
#include"../Top/Top.h"
#include"../Top/CollisionManager.h"
using namespace ci;
using namespace ci::app;
Pallet::Pallet()
{
	palletpos = Vec2f(WINDOW_WIDTH/2, WINDOW_HEIGHT);
	palletsize = Vec2f(450, 300);
	selectnum = 0;
	
}

Pallet::Pallet(ci::Vec2f _pos)
{
}

void Pallet::draw()
{
	//DrawM.drawTextureBox(palletpos, palletsize, 0.0f, TextureM.getTexture("UI/pletbase.png"), ColorA(1, 1, 1, 1));
	for (auto itr : colorobjects) {
		itr.drawCircle();
	}
}

void Pallet::update()
{
	for (auto& itr : colorobjects) {
		itr.update(palletpos);
	}
	//selectcolor();
}

void Pallet::addColorObject(ci::ColorA _color, bool _isnecessary, int _num)
{
	Vec2f size = 1.5f*TextureM.getTexture("UI/paintpen.png").getSize();
	Vec2f trancepos = Vec2f(colorobjects.size()*size.x-(_num-1)*size.x/2.f,0);
	
	colorobjects.push_back(ColorObject(trancepos, palletpos, size, _color, _isnecessary));
}

int Pallet::getColorObjectNum()
{
	return colorobjects.size();
}

void Pallet::setPos(ci::Vec2f _pos)
{
	palletpos = _pos;
}

void Pallet::drawline()
{

}

int Pallet::getSelectNum()
{
	return selectnum;
}

ColorA Pallet::getSelectColor()
{
	if (colorobjects.size() >= 1) {
		return colorobjects[selectnum].getColor();
	}
	return ColorA(1, 1, 1, 1);
	
}

void Pallet::setup()
{
	colorobjects[0].SetIsselected(true);
}

void Pallet::selectcolor()
{
	for (int i = 0;i < colorobjects.size();i++) {
		colorobjects[i].SetIsselected(false);
	}
	selectnum++;
	selectnum = selectnum % colorobjects.size();
	colorobjects[selectnum].SetIsselected(true);
}

void Pallet::selectColorPosition()
{
	Vec2f pointerpos = MouseManager::getMouse().getmousepos();
	if (!MouseManager::getMouse().isPush(MouseEvent::LEFT_DOWN))return;
	if (pointerpos.y > WINDOW_HEIGHT - 300) {
		for (int i = 0;i < colorobjects.size();i++) {
			if (CollisionM.isBoxPoint(pointerpos, colorobjects[i].getLeftUpPos(), colorobjects[i].getSize())) {
				selectnum = i;
				colorobjects[i].SetIsselected(true);
			}
			else {
				colorobjects[i].SetIsselected(false);
			}
		}

	}
}
