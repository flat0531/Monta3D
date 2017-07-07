#include "EffectWorldClear.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DataManager.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
EffectWorldClear::EffectWorldClear()
{
}

EffectWorldClear::EffectWorldClear(int worldnum)
{
	name = TextureM.getTexture("UI/worldclear" + std::to_string(worldnum) + ".png");
	blood = TextureM.getTexture("UI/blood.png");
	Vec2f basepos = Vec2f(300, 150);
	for (int i = 0;i < 10;i++) {
		ColorA color;
		if (i % 7 == 0)color = ColorA(1, 0, 0, 0);
		if (i % 7 == 1)color = ColorA(1, 165.f / 255.f, 0, 0);
		if (i % 7 == 2)color = ColorA(1, 1, 0, 0);
		if (i % 7 == 3)color = ColorA(51.f / 255.f, 153.f / 255.f, 67.f / 255.f, 0);
		if (i % 7 == 4)color = ColorA(0, 1, 1, 0);
		if (i % 7 == 5)color = ColorA(0, 0, 1, 0);
		if (i % 7 == 6)color = ColorA(165.f / 255.f, 0, 1, 0);
		CreateBlood(basepos + Vec2f(i*100.f, randFloat(-100,100)), Vec2f(300, 300), randInt(360), color);
	}
	
}

void EffectWorldClear::update()
{
	EasingManager::tCount(begin_t, 2.0f);
	Vec2f endpos = Vec2f(WINDOW_WIDTH/2.f, 150);
	uppos.x = EasingExpoOut(begin_t, endpos.x, endpos.x);
	uppos.y = EasingExpoOut(begin_t, -300.f, endpos.y);
	downpos.x = EasingExpoOut(begin_t, endpos.x, endpos.x);
	downpos.y = EasingExpoOut(begin_t, 1200.f, endpos.y);

	if (EasingManager::tCountEnd(begin_t)) {
		for (int i = 0;i < bloods.size();i++) {
			if (EasingManager::tCountEnd(bloods[i].t))continue;
			EasingManager::tCount(bloods[i].t, 0.1f);
			bloods[i].color.a = EasingCircOut(bloods[i].t, 0.0f, 1.0f);
			if (EasingManager::tCountEnd(bloods[i].t)) {
				SoundM.PlaySE("namesound.wav");
			}
			break;
		}
	}


}

void EffectWorldClear::draw(const ci::CameraPersp camera)
{
	for (int i = 0;i < bloods.size();i++) {
		DrawM.drawTextureBox(bloods[i].pos, bloods[i].size, bloods[i].rotate, blood,bloods[i].color);
	}
	DrawM.drawTextureBox(downpos+Vec2f(2,-2), Vec2f(1000, 250), 0.0f, name, ColorA(0, 0, 0, begin_t));
	DrawM.drawTextureBox(uppos, Vec2f(1000, 250), 0.0f, name, ColorA(1, 1, 1, begin_t));

}

bool EffectWorldClear::deleteThis()
{
	return false;
}

void EffectWorldClear::CreateBlood(ci::Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color)
{
	Blood buf;
	buf.pos = pos;
	buf.size = size;
	buf.rotate = rotate;
	buf.color = color;
	bloods.push_back(buf);
}
