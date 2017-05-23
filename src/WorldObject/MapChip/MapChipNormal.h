#pragma once
#include"MapChipBase.h"
#include"cinder/gl/Texture.h"
class EffectManager;
class MapChipNormal : public MapChipBase {
public:
	MapChipNormal(ci::Vec3f _pos,ci::Vec3f _scale, EffectManager* _effectmanager);
	void draw();
	void update();
	void UpCollisionEnter(CharacterBase * characterbase) override;
	void DownCollisionEnter(CharacterBase * characterbase)override;
	void RightCollisionEnter(CharacterBase * characterbase)override;
	void LeftCollisionEnter(CharacterBase * characterbase)override;
	void BulletCollison(BulletBase * bulletbase, bool isbreak)override;
private:
	EffectManager* effectmanager;
	ci::gl::Texture tex;
};