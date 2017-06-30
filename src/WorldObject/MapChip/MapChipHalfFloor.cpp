#include "MapChipHalfFloor.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
#include"../../WorldObject/CharacterBase.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
MapChipHalfFloor::MapChipHalfFloor(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
	aabb = ci::AxisAlignedBox3f(pos - scale / 2.f, pos + scale / 2.f);
}

void MapChipHalfFloor::draw()
{
	ci::Vec3f drawscale = scale*ci::Vec3f(1, 0.25f, 1);
	DrawM.drawTextureCube(pos + ci::Vec3f(0, scale.y / 2.f - drawscale.y / 2.f, 0), drawscale, ci::Vec3f(0, 0, 0),TextureM.getTexture("Map/hulffloor.png"), ci::ColorA(1, 1, 1, 1));
}

void MapChipHalfFloor::update()
{
}

void MapChipHalfFloor::UpCollisionEnter(CharacterBase * characterbase)
{
	if (characterbase->getCharacterType() == CharacterType::CHARACTER_PLAYER
		&&KeyManager::getkey().isPress(ci::app::KeyEvent::KEY_s))return;

	if (characterbase->getSpeed().y <= 0.0f && ((characterbase->getPrevPos().y-characterbase->getScale().y/2.f)>=(pos.y + scale.y / 2.f))) {
		characterbase->setPosY(pos.y + (scale.y / 2.f + characterbase->getScale().y / 2.f));
		characterbase->setCanJumpCount(0);
		if (characterbase->getSpeed().y < (-10.f)) {
			float gain = std::min(characterbase->getSpeed().y / (-50.f), 1.0f);
			SoundM.PlaySE("onground.wav", gain);
		}
		characterbase->setSpeedY(0.0f);
		characterbase->setJumpPower();
	}
}

void MapChipHalfFloor::DownCollisionEnter(CharacterBase * characterbase)
{
}

void MapChipHalfFloor::RightCollisionEnter(CharacterBase * characterbase)
{
}

void MapChipHalfFloor::LeftCollisionEnter(CharacterBase * characterbase)
{
}
