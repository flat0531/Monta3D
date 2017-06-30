#include "EffectColorShot.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DataManager.h"
using namespace ci;
using namespace ci::app;
EffectColorShot::EffectColorShot()
{

}

EffectColorShot::EffectColorShot(const ci::Vec3f scale)
{
	color_alfa = 0.0f;
	blood = TextureM.getTexture("UI/blood.png");
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*1.f, 300), Vec2f(scale.x, scale.y)*(2.f/3.f), 100.0f, ColorA(1, 0, 0, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*2.f, 600), Vec2f(scale.x, scale.y)*(2.f / 3.f), 200.0f, ColorA(1, 165.f / 255.f, 0, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*3.f, 200), Vec2f(scale.x, scale.y)*(2.f / 3.f), 50.0f, ColorA(1, 1, 0, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*4.f, 500), Vec2f(scale.x, scale.y)*(2.f / 3.f), 0.0f, ColorA(51.f / 255.f, 153.f / 255.f, 67.f / 255.f, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*5.f, 100), Vec2f(scale.x, scale.y)*(2.f / 3.f), 220.0f, ColorA(0, 1, 1, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*6.f, 400), Vec2f(scale.x, scale.y)*(2.f / 3.f), 40.0f, ColorA(0, 0, 1, 1));
	CreateBlood(Vec2f((WINDOW_WIDTH / 7.f)*7.f, 700), Vec2f(scale.x, scale.y)*(2.f / 3.f), 340.0f, ColorA(165.f / 255.f, 0, 1, 1));
	SoundM.PlaySE("colorblood.wav");
}

void EffectColorShot::update()
{
	if (!isend) {
		EasingManager::tCount(begin_alpha_t, 0.2f);
		color_alfa = EasingCubicOut(begin_alpha_t, 0.f, 0.8f);
		if (EasingManager::tCountEnd(begin_alpha_t)) {
			isend = true;	
		}
	}
	else {
		EasingManager::tCount(end_alpha_t, 15.0f);
		color_alfa = EasingCubicIn(end_alpha_t, 0.8f, 0.f);
		for (int i = 0;i < bloods.size();i++) {
			bloods[i].pos.y = EasingCubicIn(end_alpha_t, bloods[i].beginpos.y, bloods[i].beginpos.y+300.f);
		}
	}
	
}

void EffectColorShot::draw(const ci::CameraPersp camera)
{
	for (int i = 0;i < bloods.size();i++) {
		DrawM.drawTextureBox(bloods[i].pos, bloods[i].size, bloods[i].rotate, blood, ColorA(bloods[i].color.r, bloods[i].color.g, bloods[i].color.b,color_alfa));
	}
}

bool EffectColorShot::deleteThis()
{
	return EasingManager::tCountEnd(end_alpha_t);
}

void EffectColorShot::CreateBlood(ci::Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color)
{
	Blood buf;
	buf.pos = pos;
	buf.beginpos = pos;
	buf.size = size;
	buf.rotate = rotate;
	buf.color = color;
	bloods.push_back(buf);
}
