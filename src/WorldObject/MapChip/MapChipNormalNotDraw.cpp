#include "MapChipNormalNotDraw.h"
#include"../../Top/DrawManager.h"
MapChipNormalNotDraw::MapChipNormalNotDraw(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
}

void MapChipNormalNotDraw::draw()
{
	DrawM.drawStrokeCube(pos, scale, ci::Vec3f(0, 0, 0), ci::ColorA(1, 0, 0, 1));
}

void MapChipNormalNotDraw::update()
{
}

void MapChipNormalNotDraw::UpCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y + (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y <= 0.0f) {
		characterbase->setCanJumpCount(0);
		characterbase->setSpeedY(0.0f);
		characterbase->setJumpPower();
	}
}

void MapChipNormalNotDraw::DownCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosY(pos.y - (scale.y / 2.f + characterbase->getScale().y / 2.f));
	if (characterbase->getSpeed().y >= 0.0f)
		characterbase->setSpeedY(0.0f);
}

void MapChipNormalNotDraw::RightCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x + (scale.x / 2.f + characterbase->getScale().x / 2.f));
}

void MapChipNormalNotDraw::LeftCollisionEnter(CharacterBase * characterbase)
{
	characterbase->setPosX(pos.x - (scale.x / 2.f + characterbase->getScale().x / 2.f));
}

void MapChipNormalNotDraw::BulletCollison(BulletBase * bulletbase, bool isbreak)
{
	bulletbase->setCompulsiondelete(bulletbase->getismapcollision_endddelet());
}
