#include "PalletManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Input/KeyManager.h"
using namespace ci;
using namespace ci::app;
PalletManager::PalletManager()
{
	TextureM.CreateTexture("UI/pletbase.png");
	TextureM.CreateTexture("UI/paintpen.png");
	TextureM.CreateTexture("UI/color.png");
	pallets.push_back(Pallet());
	int num = 30;
	//for (int i = 0;i < num;i++) {
	//	pallets[0].addColorObject(ColorA(1, 1, 1, 1), false, num);
	//}
	pallets[0].addColorObject(ColorA(1, 1, 1, 1), false,6);
	pallets[0].addColorObject(ColorA(0, 1, 1, 1), false,6);
	pallets[0].addColorObject(ColorA(1, 0, 1, 1), false,6);
	pallets[0].addColorObject(ColorA(1, 1, 0, 1), false,6);
	pallets[0].addColorObject(ColorA(235.0f/255.0f, 97.f/255.f, 1.f/255.f, 255.f/255.f), false,6);
	pallets[0].addColorObject(ColorA(1, 0, 0, 1), false,6);
	pallets[0].setup();
}

void PalletManager::draw()
{
	for (auto itr : pallets) {
		itr.draw();
	}
}

void PalletManager::update()
{
	for (auto& itr : pallets) {
		//if (KeyManager::getkey().isPush(KeyEvent::KEY_j)||(effectnext()&&(!effectend()))) {
		//	itr.selectcolor();
		//}
		if ((effectnext() && (!effectend()))) {
			itr.selectcolor();
		}
		if (effectend()) {
			itr.selectColorPosition();
		}
		itr.update();
	}
	effectCountup();
}

void PalletManager::setup()
{
}

ci::ColorA PalletManager::getSelectcolor()
{
	return pallets[0].getSelectColor();
}

bool PalletManager::effectend()
{
	return effectcount >= effectnexttime* pallets[0].getColorObjectNum();
}

bool PalletManager::effectnext()
{
	return (effectcount%effectnexttime) == (effectnexttime - 1);
}

void PalletManager::effectCountup()
{
	if (!effectend())
		effectcount++;
}
