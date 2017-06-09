#include "MapChipNormal.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldObject/Effect/EffectExplodeburst.h"
MapChipNormal::MapChipNormal(ci::Vec3f _pos, ci::Vec3f _scale, EffectManager * _effectmanager)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
	effectmanager = _effectmanager;
	SoundM.CreateSE("haretu.wav");
	tex = TextureM.getTexture("Map/normalbox.png");
	aabb = ci::AxisAlignedBox3f(pos - scale / 2.f, pos + scale / 2.f);
}

void MapChipNormal::draw()
{
	DrawM.drawTextureCube(pos, scale, ci::Vec3f(0, 0, 0),tex,ci::ColorA(1, 1, 1, 1));
}

void MapChipNormal::update()
{
}

void MapChipNormal::UpCollisionEnter(CharacterBase * characterbase)
{
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

void MapChipNormal::DownCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y - (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y >= 0.0f)
		characterbase->setSpeedY(0.0f);
}

void MapChipNormal::RightCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x + (scale.x / 2.f + characterbase->getScale().x / 2.f));
	characterbase->onRightWall();
}

void MapChipNormal::LeftCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x - (scale.x / 2.f + characterbase->getScale().x / 2.f));
	characterbase->onLeftWall();
}

void MapChipNormal::BulletCollison(BulletBase * bulletbase, bool isbreak)
{
	if (bulletbase->getismapcollision_endddelet()) {
		SoundM.PlaySE("haretu.wav", 0.2f);
		effectmanager->CreateEffect(EffectExplodeburst(bulletbase->getPos(),bulletbase->getScale(), ci::Vec3f(0, 0, 0),ci::ColorA(1, 1, 0.5f, 1), 0.3f));
	}
	bulletbase->setCompulsiondelete(bulletbase->getismapcollision_endddelet());
}
