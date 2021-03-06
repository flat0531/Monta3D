#pragma once
#include"cinder/gl/gl.h"
enum ActionType
{
	SLIME,CAT,BIRD,ENJEL,MOGURA,RATTON,WITCH,SPARROW,GHOST,PUMPMAN,WALKRATTON,BIGPUMPKIN,NONE
};
class ActionBase {
public:
	virtual void setup(ci::Vec3f rotate) {};
	virtual void update() {};
	virtual void draw() {};
	virtual void jump() {};
	virtual void attack() {};
	virtual void damaged() {};////ダメージを受けた場合６０フレーム間呼ばれる関数
	virtual void onLeftWall() {};////壁の左側からあたった場合呼ばれる関数
	virtual void onRightWall() {};////壁の右側からあたった場合呼ばれる関数
	float getJumpPower() { return jumppower; }
	void setJumpPower(const float power) { jumppower = power; }
	float getMaxJumpPower() { return maxjumppower; }
protected:
	float maxjumppower;
	float jumppower;
	int actioncount = 0;
	float addspeed = 0.0f;
	int addpower = 0;
};