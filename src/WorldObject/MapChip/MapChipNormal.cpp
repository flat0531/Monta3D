#include "MapChipNormal.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
MapChipNormal::MapChipNormal(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
}

void MapChipNormal::draw()
{
	DrawM.drawTextureCube(pos, scale, ci::Vec3f(0, 0, 0), TextureM.getTexture("Map/normalbox.png"),ci::ColorA(1, 1, 1, 1));
}

void MapChipNormal::update()
{
}

void MapChipNormal::UpCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y + (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y <= 0.0f) {
		characterbase->setCanJumpCount(0);
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
}

void MapChipNormal::LeftCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x - (scale.x / 2.f + characterbase->getScale().x / 2.f));
}

void MapChipNormal::BulletCollison(BulletBase * bulletbase, bool isbreak)
{
	bulletbase->setCompulsiondelete(bulletbase->getismapcollision_endddelet());
}
