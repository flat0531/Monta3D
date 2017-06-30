#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../WorldObject/CharacterBase.h"
#include<memory>
class ActionBase;
class BulletManager;
class Boss :public CharacterBase {
public:
	Boss();
	Boss(ci::Vec3f _pos, ActionType _type, int _id);
	void update() override;
	void draw()override;
	void setup(ci::Vec3f _pos)override;
	int getjumpCount();
private:
};
