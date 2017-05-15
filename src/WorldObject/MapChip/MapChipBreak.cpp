#include "MapChipBreak.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldObject/Effect/EffectExplosion.h"
#include"../../WorldObject/Effect/EffectExplodeburst.h"
MapChipBreak::MapChipBreak(ci::Vec3f _pos, ci::Vec3f _scale, EffectManager * _effectmanager)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
	effectmanager = _effectmanager;
	SoundM.CreateSE("haretu.wav");
}

void MapChipBreak::draw()
{
	if (isactive)
		DrawM.drawTextureCube(pos, scale, ci::Vec3f(0, 0, 0), TextureM.getTexture("Map/renga.png"), ci::ColorA(1, 1, 1, 1));
}

void MapChipBreak::update()
{
}

void MapChipBreak::UpCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y + (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y <= 0.0f) {
		characterbase->setCanJumpCount(0);
		characterbase->setSpeedY(0.0f);
		characterbase->setJumpPower();
	}
}

void MapChipBreak::DownCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y - (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y >= 0.0f)
		characterbase->setSpeedY(0.0f);
}

void MapChipBreak::RightCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x + (scale.x / 2.f + characterbase->getScale().x / 2.f));
}

void MapChipBreak::LeftCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x - (scale.x / 2.f + characterbase->getScale().x / 2.f));
}

void MapChipBreak::BulletCollison(BulletBase * bulletbase, bool isbreak)
{
	if (!isactive)return;
	if (isbreak) {
		int damagetobullet = 3;
		bulletbase->AddHpValue(-damagetobullet);
		isactive = false;
		effectmanager->CreateEffect(EffectExplodeburst(pos,scale,ci::Vec3f(0,0,0),ci::ColorA(1,1,0.5f,1),0.3f));
		SoundM.PlaySE("haretu.wav");
	}
	else {
		bulletbase->setCompulsiondelete(bulletbase->getismapcollision_endddelet());
	}

}