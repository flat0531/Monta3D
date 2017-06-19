#include "MapChipColored.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldObject/Effect/EffectColored.h"
#include"../../WorldObject/Effect/EffectExplodeburst.h"
using namespace ci;
using namespace ci::app;
MapChipColored::MapChipColored(ci::Vec3f _pos, ci::Vec3f _scale, EffectManager * _effectmanager)
{
	pos = _pos;
	scale = _scale;
	rotate = Vec3f(0,0,0);
	iscollision = true;
	effectmanager = _effectmanager;

	aabb = ci::AxisAlignedBox3f(pos - scale / 2.f, pos + scale / 2.f);
	surfacesize = 50;
	surface = Surface(surfacesize, surfacesize, true);

	for (int y = 0; y < surfacesize; y++)
	{
		for (int x = 0; x <surfacesize; x++)
		{
			surface.setPixel(Vec2i(x, y), ColorA(0, 0, 0, 0));
		}
	}
}

void MapChipColored::draw()
{
	if (!istouch) {
		DrawM.drawStrokeCube(pos, scale, ci::Vec3f(0, 0, 0), ci::ColorA(1, 1, 1, 1));
	}
	if (istouch&&!effectend) {
		gl::Texture tex = surface;
		DrawM.drawStrokeCube(pos, scale,rotate, ci::ColorA(1, 1, 1, 1));
		DrawM.drawTextureCube(pos, scale, rotate, tex, ci::ColorA(1, 1, 1, 1));
	}
	if (effectend) {
		DrawM.drawCube(pos, scale, ci::Vec3f(0, 0, 0),color);
	}

}

void MapChipColored::update()
{
	if (istouch&&(!effectend)) {
		rotate += Vec3f(10 ,10, 0);
		for (int x = 0;x < surfacesize;x++) {
			surface.setPixel(Vec2i(x, count), color);
			surface.setPixel(Vec2i(x, surfacesize - (count + 1)), color);
		}
		count++;
		if (count == (surfacesize/2)) {
			effectend = true;
			rotate = Vec3f(0, 0, 0);
		}
	}
}

void MapChipColored::UpCollisionEnter(CharacterBase * characterbase)
{
	if (istouch) {
		characterbase->setPosY(pos.y + (scale.y / 2.f + characterbase->getScale().y / 2.f));
		if (characterbase->getSpeed().y <= 0.0f) {
			characterbase->setCanJumpCount(0);
			if (characterbase->getSpeed().y < (-10.f)) {
				float gain = std::min(characterbase->getSpeed().y / (-50.f), 1.0f);
				SoundM.PlaySE("onground.wav", gain);
			}
			characterbase->setSpeedY(0.0f);
			characterbase->setJumpPower();
		}
	}
	
}

void MapChipColored::DownCollisionEnter(CharacterBase * characterbase)
{
	if (istouch) {
		characterbase->setPosY(pos.y - (scale.y / 2.f + characterbase->getScale().y / 2.f));
		if (characterbase->getSpeed().y >= 0.0f)
			characterbase->setSpeedY(0.0f);
	}
}

void MapChipColored::RightCollisionEnter(CharacterBase * characterbase)
{
	if (istouch) {
		characterbase->setPosX(pos.x + (scale.x / 2.f + characterbase->getScale().x / 2.f));
		characterbase->onRightWall();
	}
}

void MapChipColored::LeftCollisionEnter(CharacterBase * characterbase)
{
	if (istouch) {
		characterbase->setPosX(pos.x - (scale.x / 2.f + characterbase->getScale().x / 2.f));
		characterbase->onLeftWall();
	}
}

void MapChipColored::BulletCollison(BulletBase * bulletbase, bool isbreak)
{
	if (!istouch&&isbreak) {
		color = bulletbase->getUniqueColor();
		istouch = true;
		effectmanager->CreateEffect2D(EffectColored(pos, scale, bulletbase->getUniqueColor()));
	}
	if (effectend) {
		if (bulletbase->getismapcollision_endddelet()) {
			SoundM.PlaySE("haretu.wav", 0.2f);
			effectmanager->CreateEffect(EffectExplodeburst(bulletbase->getPos(), bulletbase->getScale(), ci::Vec3f(0, 0, 0), ci::ColorA(1, 1, 0.5f, 1), 0.3f));
		}
		bulletbase->setCompulsiondelete(bulletbase->getismapcollision_endddelet());
	}
}
