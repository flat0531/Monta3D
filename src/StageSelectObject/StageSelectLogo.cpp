#include "StageSelectLogo.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
StageSelectLogo::StageSelectLogo()
{
	CretaeLogoString();
	montatex = TextureM.CreateTexture("UI/montaicon.png");
	treetex = TextureM.CreateTexture("Map/tree.png");
	basetex = TextureM.CreateTexture("UI/titlebase.png");
	monta_t = 0.0f;
	monta_delay_t = 0.0f;
	montaiconsize = Vec2f(120,120);
	montaiconpos = Vec2f(130,70);
	montaiconangle = -8.0f;
	treeangle = 0.0f;
	treesinangle = 0.0f;
}

void StageSelectLogo::update()
{
	for (auto& it : logostrig) {
		it.update();
	}
	updateMontaIcon();
	updateTreeIcon();
}

void StageSelectLogo::draw()
{
	drawBase();
	DrawM.drawTextureBox(montaiconpos, montaiconsize, montaiconangle, montatex, ColorA(1, 1, 1, 1));
	DrawM.drawTextureBoxBottom(Vec2f(480, 115), Vec2f(110, 110), treeangle+2.f, treetex, ColorA(1, 1, 1, 1));
	DrawM.drawTextureBoxBottom(Vec2f(440, 110), Vec2f(90, 90), -treeangle-2.f, treetex, ColorA(1, 1, 1, 1));
	for (auto it : logostrig) {
		it.draw();
	}
}

void StageSelectLogo::CretaeLogoString()
{

	float tranceposx = 40.f;
	float t_displace = 0.03f;
	float begin_t = 0.5f;
    pos = Vec2f(75, 100);
	Vec2f size = Vec2f(70, 70);
	logostrig.push_back(StringLogo("s", pos, size, begin_t));
	logostrig.push_back(StringLogo("t", pos + Vec2f(tranceposx * logostrig.size(), 0), size, begin_t - t_displace*((float)logostrig.size())));
	logostrig.push_back(StringLogo("a", pos + Vec2f(tranceposx * logostrig.size() - size.x*0.1f, 0), size, begin_t - t_displace*((float)logostrig.size())));
	logostrig.push_back(StringLogo("g", pos + Vec2f(tranceposx * logostrig.size(), 0), size, begin_t - t_displace*((float)logostrig.size())));
	logostrig.push_back(StringLogo("e", pos + Vec2f(tranceposx * logostrig.size(), 0), size, begin_t - t_displace*((float)logostrig.size())));

	logostrig.push_back(StringLogo("s", pos + Vec2f(tranceposx * (logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
	logostrig.push_back(StringLogo("e", pos + Vec2f(tranceposx *(logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
	logostrig.push_back(StringLogo("l", pos + Vec2f(tranceposx * (logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
	logostrig.push_back(StringLogo("e", pos + Vec2f(tranceposx * (logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
	logostrig.push_back(StringLogo("c", pos + Vec2f(tranceposx * (logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
	logostrig.push_back(StringLogo("t", pos + Vec2f(tranceposx * (logostrig.size() + 1), 0), size, begin_t - t_displace*((float)logostrig.size() + 1.f)));
}

void StageSelectLogo::updateMontaIcon()
{
	if (EasingManager::tCountEnd(monta_delay_t)) {
		EasingManager::tCount(monta_t, 0.3f);
		float startposy = 70.f;
		float trancepos = 20.f;
		montaiconpos.y = EasingReturn(monta_t, startposy, -20.f);
		montaiconsize.x = EasingReturn(monta_t, 120.f, 10.f);
		montaiconsize.y = EasingReturn(monta_t, 120.f, 10.f);
		if (EasingManager::tCountEnd(monta_t)) {
			monta_delay_t = 0.0f;
			monta_t = 0.0f;
		}
	}
	else {
		EasingManager::tCount(monta_delay_t, 4.0f);
	}
	
}

void StageSelectLogo::updateTreeIcon()
{
	treesinangle += 0.02f;
	treeangle = 7 * sin(treesinangle);
	if (treesinangle >= 2.0f*M_PI) {
		treesinangle -= 2.0f*M_PI;
	}
}

void StageSelectLogo::drawBase()
{
	Vec2f pos = Vec2f(300, 100);
	Vec2f size = Vec2f(512, 128);
	DrawM.drawTextureBox(pos,size,0.0f,basetex);
}


