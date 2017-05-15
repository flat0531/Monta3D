#include "MapChipGoal.h"
#include"../../WorldCreater/CharacterManager.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
MapChipGoal::MapChipGoal()
{
}
MapChipGoal::MapChipGoal(ci::Vec3f _pos, ci::Vec3f _scale, std::function<void()>& _goal)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
	goal = _goal;
}

void MapChipGoal::draw()
{
	DrawM.drawStrokeCube(pos, scale, ci::Vec3f(0, 0, 0), ci::ColorA(1, 0, 0, 1));
}

void MapChipGoal::update()
{
}

void MapChipGoal::InCollisionEnter(CharacterBase * characterbase)
{
	if (characterbase->getCharacterType() == CharacterType::CHARACTER_PLAYER&&
		KeyManager::getkey().isPush(ci::app::KeyEvent::KEY_w)) {
		goal();
	}
}
