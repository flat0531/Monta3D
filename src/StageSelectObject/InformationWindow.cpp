#include "InformationWindow.h"
#include"../Top/MyJson.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../Top/DataManager.h"
#include"../Input/KeyManager.h"
#include"../Top/SoundManager.h"
using namespace ci;
using namespace ci::app;
InformationWindow::InformationWindow()
{

}

InformationWindow::InformationWindow(const int _worldnum, const int _stagenum, const int _itemnember)
{
	windowpos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT)*0.5f;
	windowsize = Vec2f(800, 500);


	std::string path = "Json/StageSelect/World" + std::to_string(_worldnum) + "/stage" + std::to_string(_stagenum) + "item.json";
	JsonTree item(loadAsset(path));
	JsonTree child = item.getChild(_itemnember);
	itemtype = child.getValueForKey<std::string>("type");
	itemname = child.getValueForKey<std::string>("name");
	buttontex = TextureM.CreateTexture("UI/Button/press_l.png");
	if (itemtype == "color") {
		windowtex= TextureM.CreateTexture("UI/informationcolor.png");
		itemtex = TextureM.CreateTexture("UI/paintpen.png");
		painttex= TextureM.CreateTexture("UI/color.png");
		paintcolor = DataM.getColor(itemname);
	}
	if (itemtype == "folm") {
		windowtex = TextureM.CreateTexture("UI/informationcandraw.png");
		frametex = TextureM.CreateTexture("UI/waku.png");
		itemtex = TextureM.CreateTexture("Draw/" + itemname + "/frame.png");
	}

}

void InformationWindow::update()
{
	updateOpen();
	updateClose();
}

void InformationWindow::draw()
{
	if (itemtype == "color") {
		drawColorWindow();
		

	}
	if (itemtype == "folm") {
		drawFolmWindow();
	}

}

bool InformationWindow::isDelete()
{
	return EasingManager::tCountEnd(t) && isclose;
}

void InformationWindow::drawColorWindow()
{
	DrawM.drawTextureBox(windowpos, windowsize*sizerate, 0.f, windowtex);
	Vec2f trancepos = Vec2f(0, -50)*sizerate;
	Vec2f itemsize = Vec2f(60, 240);

	DrawM.drawTextureBox(windowpos + trancepos, itemsize*sizerate, 45.f, itemtex);
	DrawM.drawTextureBox(windowpos + trancepos, itemsize*sizerate, 45.f, painttex, paintcolor);
	Vec2f buttontrancepos = Vec2f(300, 240)*sizerate;
	Vec2f buttonsize = Vec2f(300, 75);
	DrawM.drawTextureBox(windowpos + buttontrancepos, buttonsize*sizerate, 0.0f, buttontex, ColorA(1, 0, 0, 1));
}

void InformationWindow::drawFolmWindow()
{

	DrawM.drawTextureBox(windowpos, windowsize*sizerate, 0.f, windowtex);
	Vec2f trancepos = Vec2f(0, -75)*sizerate;
	Vec2f itemsize = Vec2f(250, 250);
	DrawM.drawTextureBox(windowpos+trancepos, itemsize*sizerate, 0.f, frametex);
	DrawM.drawTextureBox(windowpos + trancepos, itemsize*sizerate, 0.f, itemtex);
	Vec2f buttontrancepos = Vec2f(300, 240)*sizerate;
	Vec2f buttonsize = Vec2f(300, 75);
	DrawM.drawTextureBox(windowpos + buttontrancepos, buttonsize*sizerate, 0.0f, buttontex, ColorA(1, 0, 0, 1));
}

void InformationWindow::updateOpen()
{
	if (isclose)return;
	if (!playedse) {
		playedse = true;
		SoundM.PlaySE("itemwindow.wav",0.3f);
	}
	EasingManager::tCount(t, 1.0f);
	sizerate = EasingElasticOut(t, 0.0f, 1.0f);
	if (EasingManager::tCountEnd(t)) {
		if (KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
			t = 0.0f;
			isclose = true;
			SoundM.PlaySE("close.wav");
		}
	}
}

void InformationWindow::updateClose()
{
	if (!isclose)return;
	EasingManager::tCount(t, 0.5f);
	sizerate = EasingBackIn(t, 1.0f, 0.f);
	
}
