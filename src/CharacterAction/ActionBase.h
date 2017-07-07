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
	virtual void damaged() {};////�_���[�W���󂯂��ꍇ�U�O�t���[���ԌĂ΂��֐�
	virtual void onLeftWall() {};////�ǂ̍������炠�������ꍇ�Ă΂��֐�
	virtual void onRightWall() {};////�ǂ̉E�����炠�������ꍇ�Ă΂��֐�
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