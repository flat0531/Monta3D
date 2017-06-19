#include "StageSelectMenu.h"
#include"../Top/DataManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Input/KeyManager.h"
#include"../Top/SoundManager.h"
using namespace ci;
using namespace ci::app;

StageSelectMenu::StageSelectMenu()
{
	//DataM.isCheckFolm("slime", "candraw");
	Vec2f size = Vec2f(240,60);
	{
		Menu gamestart;
		gamestart.trancepos = Vec2f(-size.x/1.8f, 0);
		gamestart.size = size;
		gamestart.iscanselect = DataM.isCheckFolm("slime", "release");
		gamestart.tex = TextureM.CreateTexture("UI/Button/GameStart.png");
		menus.push_back(gamestart);
	}
	{
		Menu characterdraw;
		characterdraw.trancepos = Vec2f(size.x / 1.8f, 0);
		characterdraw.size = size;
		characterdraw.iscanselect = true;
		characterdraw.tex = TextureM.CreateTexture("UI/Button/CharacterDraw.png");
		menus.push_back(characterdraw);
	}
	SoundM.CreateSE("cursor.wav");
	TextureM.CreateTexture("UI/push_a.png");
	TextureM.CreateTexture("UI/push_d.png");
	icontex = TextureM.CreateTexture("UI/uzu.png");
}

void StageSelectMenu::update()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_a)) {
		if (selectnum != 0) {
			selectnum--;
			SoundM.PlaySE("cursor.wav");
			return;
		}
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_d)) {
		if (selectnum != (menus.size()-1)) {
			selectnum++;
			SoundM.PlaySE("cursor.wav");
			return;
		}
	}
}

void StageSelectMenu::draw(const ci::Vec2f menupos)
{
	for (int i = 0;i < menus.size();i++) {
		float colorvalue = menus[i].iscanselect ? 1.0f : 0.55f;
		ColorA color = ColorA(colorvalue, colorvalue, colorvalue, 1.0f);
		DrawM.drawTextureBox(menupos + menus[i].trancepos, menus[i].size, 0.0f, menus[i].tex, color);
		if (i == 0) {
			DrawM.drawTextureBox(menupos + menus[i].trancepos + Vec2f(50, 70), Vec2f(60,60), 0.0f, TextureM.getTexture("UI/push_a.png"), ColorA(1, 1, 0, 1));
		}
		if (i == 1) {
			DrawM.drawTextureBox(menupos + menus[i].trancepos + Vec2f(-50, 70), Vec2f(60, 60), 0.0f, TextureM.getTexture("UI/push_d.png"), ColorA(1, 1, 0, 1));
		}
		
	}
	drawCursor(menupos);
}

int StageSelectMenu::getSelectNum()
{
	return selectnum;
}


void StageSelectMenu::drawCursor(const ci::Vec2f menupos)
{
	Vec2f trancepos = Vec2f(0, 0);

	if (selectnum == MenuType::GAMESTART_MENU) {
		trancepos = Vec2f(-menus[0].size.x / 1.8f, menus[0].size.y/2.f);
	}
	else if(selectnum == MenuType::CHARACTERDRAW_MENU){
		trancepos = Vec2f(menus[0].size.x / 1.8f, menus[0].size.y / 2.f);
	}
	DrawM.drawTextureBox(menupos + trancepos+Vec2f(2,-2), Vec2f(menus[0].size.y*1.05f, menus[0].size.y*1.05f), 0.0f, icontex, ColorA(0, 0, 0, 1));
	DrawM.drawTextureBox(menupos +trancepos,Vec2f(menus[0].size.y*1.05f,menus[0].size.y*1.05f), 0.0f, icontex, ColorA(1, 1, 1, 1));
}

void StageSelectMenu::updateCursor()
{

}
