#include "EffectItem.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
EffectItem::EffectItem()
{
}

EffectItem::EffectItem(const ci::Vec2f _pos, const ci::Vec2f _endpos, const ci::Vec2f _scale)
{
	beginpos = _pos;
	pos2f = _pos;
	scale2f = _scale;
	endpos = _endpos;
	itemeffecttex = TextureM.CreateTexture("UI/itemeffect.png");
	icontex = TextureM.CreateTexture("UI/itemicon.png");

	SoundM.PlaySE("itemget.wav");
	CreateParticles();
}

void EffectItem::update()
{
	float easingtime = 1.0f;
	for (int i = 0;i < particles.size();i++) {
		if (i == 0) {
			EasingManager::tCount(particles[i].t,easingtime);
		}
		else {
			if (particles[i - 1].t >= 0.02f) {
				EasingManager::tCount(particles[i].t, easingtime);
			}
		}
		particles[i].pos.x = EasingManager::getEas[particles[i].easingtype_x]
			(particles[i].t, particles[i].beginpos.x, particles[i].endpos.x);
		particles[i].pos.y = EasingManager::getEas[particles[i].easingtype_y]
			(particles[i].t, particles[i].beginpos.y, particles[i].endpos.y);
		particles[i].color.a = EasingReturn(particles[i].t, 0.0f, 0.5f);
	}
	EasingManager::tCount(t, 1.8f);
}

void EffectItem::draw(const ci::CameraPersp camera)
{
	float addcolor = 0.8f*t;
	DrawM.drawTextureBox(endpos, scale2f*(1.1f+0.1f*sin(t*50.f)), 0, icontex, ColorA(0.2f + addcolor, 0.2f + addcolor, 0.2f + addcolor, 1));
	for (int i = 0;i < particles.size();i++) {
		DrawM.drawTextureBox(particles[i].pos, particles[i].scale, 0, itemeffecttex,particles[i].color);
	}
}

bool EffectItem::deleteThis()
{
	return t >= 1.0f;
}

void EffectItem::CreateParticles()
{
	int createnum = 30;
	for (int i = 0;i < createnum;i++) {
		Particle buff;
		float trancevalue = 5.f;
		buff.beginpos = beginpos + Vec2f(randFloat(-trancevalue, trancevalue),randFloat(trancevalue, trancevalue));
		buff.endpos = endpos + Vec2f(randFloat(-trancevalue, trancevalue), randFloat(trancevalue, trancevalue));
		buff.pos = buff.beginpos;
		buff.scale = Vec2f(50,50);
		buff.t = 0.0f;
		buff.color = ColorA(i % 3 == 0, i % 3 == 1, i % 3 == 2, 0);
		buff.easingtype_x = RandEas();
		buff.easingtype_y = RandEas();
		particles.push_back(buff);
	}
	
}

EasingManager::EasType EffectItem::RandEas()
{
	std::vector<EasingManager::EasType> type;
	type.push_back(EasingManager::EasType::BackIn);
	type.push_back(EasingManager::EasType::CubicIn);
	type.push_back(EasingManager::EasType::CubicOut);
	type.push_back(EasingManager::EasType::BackOut);
	type.push_back(EasingManager::EasType::Linear);
	return type[randInt(type.size())];
}
