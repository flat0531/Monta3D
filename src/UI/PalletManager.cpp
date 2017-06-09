#include "PalletManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Input/KeyManager.h"
#include"../Top/MyJson.h"
using namespace ci;
using namespace ci::app;
PalletManager::PalletManager()
{
	TextureM.CreateTexture("UI/pletbase.png");
	TextureM.CreateTexture("UI/paintpen.png");
	TextureM.CreateTexture("UI/color.png");
	
	std::string path = "SaveData/Color/releasecolor.json";
	JsonTree color(loadAsset(path));
	int createnum = 0;
	for (int i = 0;i < color.getNumChildren();i++) {
		if (color.getChild(i).getValueForKey<bool>("release")) {
			createnum++;
		}
	}
	for (int i = 0;i < color.getNumChildren();i++) {
		if (color.getChild(i).getValueForKey<bool>("release")) {
			float color_r = color.getChild(i).getChild("color").getValueAtIndex<float>(0) / 255.f;
			float color_g = color.getChild(i).getChild("color").getValueAtIndex<float>(1) / 255.f;
			float color_b = color.getChild(i).getChild("color").getValueAtIndex<float>(2) / 255.f;
			pallet.addColorObject(ColorA(color_r, color_g, color_b, 1), false,createnum);
		}
	}

	pallet.setup();
}

void PalletManager::draw()
{
	pallet.draw();
}

void PalletManager::update()
{
	if ((effectnext() && (!effectend()))) {
		pallet.selectcolor();
	}
	if (effectend()) {
		pallet.selectColorPosition();
	}
	pallet.update();
	effectCountup();
}

void PalletManager::setup()
{
}

ci::ColorA PalletManager::getSelectcolor()
{
	return pallet.getSelectColor();
}

bool PalletManager::effectend()
{
	return effectcount >= effectnexttime* pallet.getColorObjectNum();
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
