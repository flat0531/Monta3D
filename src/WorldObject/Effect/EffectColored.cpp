#include "EffectColored.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
using namespace ci;
using namespace ci::app;
EffectColored::EffectColored()
{
}

EffectColored::EffectColored(const ci::Vec3f _pos, const ci::Vec3f _scale, ci::Color color)
{
	objpos = _pos;
	objsize = _scale;
	SoundM.PlaySE("cubecolored.wav");
	colortex = TextureM.CreateTexture("UI/itemeffect.png");
	float createnum = 8.f;
	for (float i = 0;i < createnum;i++) {
		Particle buff;
		buff.beginangle = (i / createnum)*2.f*M_PI;
		buff.sinangle = 0.0f;
		buff.pos = Vec2f(0, 0);
		buff.scale = Vec2f(40, 40);
		buff.color = ColorA(color.r, color.g, color.b, 0.0f);
		buff.t = 0.0f;
		particles.push_back(buff);
	}
}

void EffectColored::update()
{
	for (int i = 0;i < particles.size();i++) {
		EasingManager::tCount(particles[i].t, 1.0);
		particles[i].sinangle = EasingCircIn(particles[i].t, 0.f, 4.f*M_PI);
		particles[i].color.a = particles[i].t;
		particles[i].pos = Vec2f(particles[i].t*100.f*cos(particles[i].sinangle), particles[i].t* 100.f*sin(particles[i].sinangle));
	}
}

void EffectColored::draw(const ci::CameraPersp camera)
{
	Vec2f pos = camera.worldToScreen(objpos,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0;i < particles.size();i++) {
		EasingManager::tCount(particles[i].t, 1.0);
		particles[i].sinangle = EasingCircIn(particles[i].t, 0.f, 4.f*M_PI);
		particles[i].color.a = particles[i].t;
		particles[i].pos = Vec2f(particles[i].t*150.f*cos(particles[i].sinangle+particles[i].beginangle), particles[i].t*150.f*sin(particles[i].sinangle + particles[i].beginangle));
		DrawM.drawTextureBox(pos + particles[i].pos, particles[i].scale, 0.0f, colortex, particles[i].color);
	}
}

bool EffectColored::deleteThis()
{
	return  EasingManager::tCountEnd(particles[0].t);
}

