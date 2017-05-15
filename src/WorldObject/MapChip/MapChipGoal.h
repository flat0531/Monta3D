#pragma once
#include"MapChipBase.h"
class MapChipGoal : public MapChipBase {
public:
	MapChipGoal();
	MapChipGoal(ci::Vec3f _pos, ci::Vec3f _scale, std::function<void()>& _goal);
	void draw();
	void update();
	void InCollisionEnter(CharacterBase * characterbase)override;
private:
	std::function<void()>goal;
};