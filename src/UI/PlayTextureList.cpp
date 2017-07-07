#include "PlayTextureList.h"
#include"../Top/Top.h"
#include"cinder/ImageIo.h"
#include"../Input/KeyManager.h"
#include"../Top/SoundManager.h"
#include"../Top/EasingManager.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/DataManager.h"
#include <filesystem>
using namespace ci;
using namespace ci::app;
PlayTextureList::PlayTextureList()
{
	trancepos = Vec2f(0.0f, 0.0f);
	beginpos = trancepos;
	endpos = trancepos;
	push_w = TextureM.CreateTexture("UI/push_w.png");
	push_s = TextureM.CreateTexture("UI/push_s.png");
}

void PlayTextureList::update()
{
	selectUserTexture();
	statusbar.update();
	EasingTranxePos();
	for (int i = 0;i < playtextures.size();i++) {
		playtextures[i]->update(selectnum);
	}
	cursorsinangle += 0.1f;
	if (cursorsinangle >= 2.0f*M_PI)cursorsinangle -= 2.0f*M_PI;
}

void PlayTextureList::draw()
{
	statusbar.draw();
	for (auto it : playtextures) {
		it->draw(trancepos);
	}
	drawCursor();
	
}

void PlayTextureList::CreatePlayTextures(std::string actionname)
{
	playtextures.clear();
	name = actionname;
	selectnum = 1;
	trancepos = Vec2f(0, 0);
	trance_t = 1.0f;
	int createnum = 0;	

	for (std::tr2::sys::directory_iterator it(app::getAssetPath("Texture/UserPlay/" + actionname).string()), end; it != end; it++)
	{
		createnum++;
	}
	for (int i = 0;i < createnum;i++) {
		playtextures.push_back(std::make_shared<PlayTexture>(Vec2f(1250,WINDOW_HEIGHT/2.3f + span_y * i), actionname, i + 1));
	}
	DataM.setPlayTextureStatus(playtextures[selectnum - 1]->getSurface());
	statusbar.setEaing(name);
}

void PlayTextureList::selectUserTexture()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_w)) {
		if (!(selectnum == 1)) {
			selectnum--;
			SoundM.PlaySE("cursor.wav");
			DataM.setPlayTextureStatus(playtextures[selectnum - 1]->getSurface());
			statusbar.setEaing(name);
			setEasing(trancepos, Vec2f(0, -span_y*(selectnum - 1)));
		}
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_s)) {
		if (!(selectnum == playtextures.size())) {
			selectnum++;
			SoundM.PlaySE("cursor.wav");
			DataM.setPlayTextureStatus(playtextures[selectnum - 1]->getSurface());
			statusbar.setEaing(name);
			setEasing(trancepos, Vec2f(0, -span_y*(selectnum - 1)));
		}
	}
}

int PlayTextureList::getSelectNum()
{
	return selectnum;
}

void PlayTextureList::setEasing(ci::Vec2f _beginpos, ci::Vec2f _endpos)
{
	trance_t = 0.0f;
	beginpos = _beginpos;
	endpos = _endpos;
}

void PlayTextureList::EasingTranxePos()
{
	EasingManager::tCount(trance_t, 0.3f);
	if (!EasingManager::tCountEnd(trance_t)) {
		trancepos.x = EasingCubicOut(trance_t, beginpos.x, endpos.x);
		trancepos.y = EasingCubicOut(trance_t, beginpos.y, endpos.y);
	}
	
}

void PlayTextureList::drawCursor()
{
	Vec2f pos = Vec2f(1450, WINDOW_HEIGHT / 2.f - 60);
	Vec2f size = Vec2f(75, 75)*(0.9f + 0.1f*sin(cursorsinangle));
	Vec2f trance = Vec2f(0, 150);
	float color_g_b = 0.5f + 0.5f*sin(cursorsinangle);
	DrawM.drawTextureBox(pos - trance, size, 0.0f, push_w, ColorA(1, color_g_b, color_g_b, selectnum == 1 ? 0.1f : 1.f));
	DrawM.drawTextureBox(pos + trance, size, 0.0f, push_s, ColorA(1, color_g_b, color_g_b, (selectnum == playtextures.size()) ? 0.1f : 1.0f));
}
