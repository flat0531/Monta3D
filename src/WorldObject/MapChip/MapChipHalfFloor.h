#pragma once
#include"MapChipBase.h"
class MapChipHalfFloor : public MapChipBase {
public:
	MapChipHalfFloor(ci::Vec3f _pos, ci::Vec3f _scale);
	void draw();
	void update();
	void UpCollisionEnter(CharacterBase * characterbase) override;
	void DownCollisionEnter(CharacterBase * characterbase)override;
	void RightCollisionEnter(CharacterBase * characterbase)override;
	void LeftCollisionEnter(CharacterBase * characterbase)override;
private:

};