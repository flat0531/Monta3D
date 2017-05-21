#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"../WorldObject/CharacterBase.h"
#include<memory>

class ActionBase;
class BulletManager;
enum PlayerDirection;
class Player :public CharacterBase {
public:
	Player();
	Player(ci::Vec3f _pos,ActionType _actiontype);
	void update() override;
	void draw()override;
	void setup(ci::Vec3f _pos)override;
	bool IsJumpping();
	int getjumpCount();

	void setJumming(const bool is);
	void CanJumpCountUp();
	PlayerDirection getplayerdirection();
	void setPlayerDirection(PlayerDirection _playerdirection);
	float getAttackRotate();
	void setT(const float t);
	bool GetIsOperate();
	void SetIsOpetate(const bool is);
private:

	bool jumpping = false;
	PlayerDirection playerdirection;
	PlayerDirection disideDirection();
	float direction_t;
	float easing_start_rotate;
	bool isoperate;
};