#pragma once
#include"MapChipBase.h"
class EffectManager;
class MapChipApple : public MapChipBase {
public:
	MapChipApple(ci::Vec3f _pos, ci::Vec3f _scale);
	void draw();
	void update();
	void InCollisionEnter(CharacterBase * characterbase)override;
private:
	float rotatesin_x= 0.0f;
};