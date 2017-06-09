#include "SelectAction.h"
#include"../Input/KeyManager.h"
#include"../Top/Top.h"
#include"../Top/MyJson.h"
#include"../Top/SoundManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;
SelectAction::SelectAction()
{
	SoundM.CreateSE("cursor.wav");
	push_a_tex = TextureM.CreateTexture("UI/push_a.png");
	push_d_tex = TextureM.CreateTexture("UI/push_d.png");
	selectnum = 0;
	CreateActionICons();
	iconsize = Vec2f(115, 115);
	playtexturelist.CreatePlayTextures(actionaicons[selectnum].getName());
	cursorbeginpos.x = leftedge + iconsize.x*selectnum;
	cursorendpos.x = cursorbeginpos.x;
	cursorpos.x = cursorbeginpos.x;
	cursorpos.y = 800.f;
	
}

void SelectAction::update()
{
	playtexturelist.update();
	ChoiceAction();
	for (int i = 0;i < actionaicons.size();i++) {
		actionaicons[i].setIsSelected(selectnum == i);
		actionaicons[i].update();
	}
	cursorsinangle += 0.1f;
	if (cursorsinangle >= 2.0f*M_PI)cursorsinangle -= 2.0f*M_PI;
	EasingManager::tCount(cursor_t, 0.3f);
	cursorpos.x = EasingCubicOut(cursor_t, cursorbeginpos.x, cursorendpos.x);
}

void SelectAction::draw()
{
	playtexturelist.draw();
	for (auto itr : actionaicons) {
		itr.draw();
	}
	float trancex = 75.f;
	DrawM.drawTextureBox(cursorpos - Vec2f(
		
		trancex, 0), Vec2f(80, 80)*(0.9f + 0.1f*sin(cursorsinangle)), 0.f, push_a_tex, ColorA(1, 1, 0.5f + 0.5f*sin(cursorsinangle), (selectnum == 0) ? 0.1f : 1.0f));
	DrawM.drawTextureBox(cursorpos + Vec2f(trancex, 0), Vec2f(80, 80)*(0.9f + 0.1f*sin(cursorsinangle)), 0.f, push_d_tex, ColorA(1, 1, 0.5f + 0.5f*sin(cursorsinangle), (selectnum == (actionaicons.size() - 1)) ? 0.1f : 1.0f));
}

std::string SelectAction::getActionName()
{
	return actionaicons[selectnum].getName();
}

int SelectAction::getPlayTextureNum()
{
	return playtexturelist.getSelectNum();
}

void SelectAction::CreateActionICons()
{
	
	std::vector<std::string>names;
	std::string path = "SaveData/Folm/releasefolm.json";
	JsonTree folm(loadAsset(path));
	for (int i = 0;i < folm.getNumChildren();i++) {
		JsonTree child = folm.getChild(i);
		if (child.getValueForKey<bool>("release")) {
			names.push_back((child.getValueForKey<std::string>("name")));
		}
	}
	int createnum = names.size();
	iconsize = Vec2f(115, 115);
	for (int i = 0;i < createnum;i++) {
		Vec2f pos = Vec2f(WINDOW_WIDTH / 2.f - (((float(createnum - 1)) / 2.f)*iconsize.x) + iconsize.x*i, 750);
		actionaicons.push_back(ActionIcon(pos, iconsize, names[i], true));
	}
	leftedge = WINDOW_WIDTH / 2.f - ((float(createnum - 1)) / 2.f)*iconsize.x;
	names.clear();
}

void SelectAction::ChoiceAction()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_a)) {
		if (!(selectnum == 0)) {
			selectnum--;
			SoundM.PlaySE("cursor.wav");
			cursor_t = 0.0f;
			cursorbeginpos.x = cursorpos.x;
			cursorendpos.x = leftedge + iconsize.x*selectnum;
			playtexturelist.CreatePlayTextures(actionaicons[selectnum].getName());
		}
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_d)) {
		if (!(selectnum == (actionaicons.size()-1))) {
			selectnum++;
			cursor_t = 0.0f;
			cursorbeginpos.x = cursorpos.x;
			cursorendpos.x = leftedge + iconsize.x*selectnum;
			SoundM.PlaySE("cursor.wav");
			playtexturelist.CreatePlayTextures(actionaicons[selectnum].getName());
		}
	}
}
