#pragma once
#include"cinder/gl/gl.h"
enum ActionType
{
	SLIME,CAT,BIRD,ENJEL,MOGURA,RATTON,WITCH,SPARROW,GHOST,PUMPMAN,WALKRATTON,NONE
};
class ActionBase {
public:
	virtual void setup(ci::Vec3f rotate) {};
	virtual void update() {};
	virtual void draw() {};
	virtual void jump() {};
	virtual void attack() {};
	virtual void damaged() {};
	virtual void onLeftWall() {};
	virtual void onRightWall() {};
	float getJumpPower() { return jumppower; }
	void setJumpPower(const float power) { jumppower = power; }
	float getMaxJumpPower() { return maxjumppower; }
protected:
	float maxjumppower;
	float jumppower;
	int actioncount = 0;
};