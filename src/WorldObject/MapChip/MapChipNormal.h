#pragma once
#include"MapChipBase.h"
class MapChipNormal : public MapChipBase {
public:
	MapChipNormal(ci::Vec3f _pos,ci::Vec3f _scale);
	void draw();
	void update();
	void UpCollisionEnter(CharacterBase * characterbase) override;
	void DownCollisionEnter(CharacterBase * characterbase)override;
	void RightCollisionEnter(CharacterBase * characterbase)override;
	void LeftCollisionEnter(CharacterBase * characterbase)override;
	void BulletCollison(BulletBase * bulletbase, bool isbreak)override;
private:

};