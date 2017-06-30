#include "EffectBossName.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../Top/DataManager.h"
using namespace ci;
using namespace ci::app;
EffectBossName::EffectBossName(const std::string path)
{
	blood = TextureM.getTexture("UI/blood.png");
	name = TextureM.getTexture(path);
	Vec2f size = Vec2f(350,350);
	for (int i = 0; i < 5; i++)
	{
		alpha[i] = 0.0f;
		t[i] = 0.0f;
	}
	CreateBlood(Vec2f(WINDOW_WIDTH/2-400,600), size, 0.0f, DataM.getColor("red"));
	CreateBlood(Vec2f(WINDOW_WIDTH/2 - 150, 700), size, 60.0f, DataM.getColor("yellow"));
	CreateBlood(Vec2f(WINDOW_WIDTH/2 + 150, 625), size, 40.0f, DataM.getColor("blue"));
	CreateBlood(Vec2f(WINDOW_WIDTH/2 + 400, 680), size, 120.0f, DataM.getColor("green"));
}

void EffectBossName::update()
{

	if (isend) {
		for (int i = 0;i < 5;i++) {
			EasingManager::tCount(t[i],-2.0f);
			alpha[i] = EasingExpoOut(t[i], 0.0f, i == 0 ? 1.0f : 0.8f);
		}
	}
	else {
		for (int i = 0;i < 5;i++) {
			if (EasingManager::tCountEnd(t[i]))continue;
			EasingManager::tCount(t[i], i == 0 ? 1.0f : 0.1f);
			alpha[i] = EasingCircOut(t[i], 0.0f, i == 0 ? 1.0f : 0.8f);
			if (EasingManager::tCountEnd(t[i])) {
				SoundM.PlaySE("namesound.wav");
			}
		
			if (i == 4 && EasingManager::tCountEnd(t[i])) {
				isend = true;
			}
			break;
		}
	}
	
}

void EffectBossName::draw(const ci::CameraPersp camera)
{
	for (int i = 0;i < bloods.size();i++) {
		DrawM.drawTextureBox(bloods[i].pos, bloods[i].size, bloods[i].rotate, blood, ColorA(bloods[i].color.r, bloods[i].color.g, bloods[i].color.b, alpha[i + 1]));
	}
	DrawM.drawTextureBox(Vec2f(WINDOW_WIDTH / 2, 650)+Vec2f(2,-2), Vec2f(1000, 250), 0.0f, name, ColorA(0, 0, 0, alpha[0]));
	DrawM.drawTextureBox(Vec2f(WINDOW_WIDTH / 2, 650), Vec2f(1000, 250), 0.0f, name, ColorA(1, 1, 1, alpha[0]));
}

bool EffectBossName::deleteThis()
{
	return isend&&EasingManager::tCountEnd(t[4], false);
}

void EffectBossName::CreateBlood(ci::Vec2f pos, ci::Vec2f size, float rotate, ci::ColorA color)
{
	Blood buf;
	buf.pos = pos;
	buf.size = size;
	buf.rotate = rotate;
	buf.color = color;
	bloods.push_back(buf);
}
