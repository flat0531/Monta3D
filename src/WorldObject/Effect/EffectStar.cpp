#include "EffectStar.h"
#include "EffectColored.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/Top.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
EffectStar::EffectStar()
{
}

EffectStar::EffectStar(const ci::Vec3f _pos, const ci::Vec3f _scale, ci::Color color)
{
	objpos = _pos;
	objsize = _scale;
	z = _pos.z + WorldScale;
	if (z < WorldScale)z = WorldScale;
	if (z > WorldScale*5.f)WorldScale*5.f;
	colortex = TextureM.CreateTexture("UI/star.png");
	float createnum = 8.f;
	for (float i = 0;i < createnum;i++) {
		Particle buff;
		buff.rotate = 0.0f;
		buff.length = 0.0f;
		buff.sinangle = (i / createnum)*2.f*M_PI;
		buff.pos = Vec2f(0, 0);
		buff.scale = Vec2f(75, 75)*(_scale.x / WorldScale);
		if (buff.scale.x >= 75)buff.scale = Vec2f(75,75);
		buff.color = ColorA(color.r, color.g, color.b, 0.0f);
		for (int k = 0;k < 3;k++) {
			buff.t[k] = 0.0f;
		}
		particles.push_back(buff);
	}
}

void EffectStar::update()
{

	for (int i = 0;i < particles.size();i++) {
		for (int k = 0;k < 3;k++) {
			if (k == 0) {
				EasingManager::tCount(particles[i].t[k], 0.2f);
			}
			else {
				if (EasingManager::tCountEnd(particles[i].t[k - 1])) {
					EasingManager::tCount(particles[i].t[k], 0.2f);
				}
			}
		}
		particles[i].color.a = particles[i].t[0] / 2.f;
		if (EasingManager::tCountEnd(particles[i].t[1])){
			particles[i].length = EasingCircIn(particles[i].t[2], 0.0f, particles[i].scale.x*2.f);
			particles[i].color.a = 0.5f - particles[i].t[1] / 2.f;
		}
		
		particles[i].rotate = EasingLinear(particles[i].t[1], 0.f, 360.f);
		
		particles[i].pos = Vec2f(particles[i].length*cos(particles[i].sinangle), particles[i].length*sin(particles[i].sinangle));
	}
	EasingManager::tCount(scale_t, 0.4f);
	scalerate = EasingReturn(scale_t, 0, 1.0f);
}

void EffectStar::draw(const ci::CameraPersp camera)
{
	Vec2f pos = camera.worldToScreen(objpos,
		WINDOW_WIDTH, WINDOW_HEIGHT);
	for (int i = 0;i < particles.size();i++) {
		DrawM.drawTextureBox(pos, particles[i].scale*2.0f*scalerate, particles[i].rotate, colortex, ColorA(1, 1, 1, particles[i].color.a));
		DrawM.drawTextureBox(pos, particles[i].scale*1.8f*scalerate, particles[i].rotate, colortex, particles[i].color);
		DrawM.drawTextureBox(pos + particles[i].pos, particles[i].scale, particles[i].rotate, colortex,ColorA(particles[i].color.r, particles[i].color.g, particles[i].color.b, 0.5f));
	}
}

bool EffectStar::deleteThis()
{
	return EasingManager::tCountEnd(particles[0].t[2]);
}