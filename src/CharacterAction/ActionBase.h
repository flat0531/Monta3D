#pragma once
enum ActionType
{
	SLIME,CAT,RATTON,WITCH,SPARROW,NONE
};
class ActionBase {
public:
	virtual void setup() {};
	virtual void update() {};
	virtual void draw() {};
	virtual void jump() {};
	virtual void attack() {};
	virtual void damaged() {};
	float getJumpPower() { return jumppower; }
	void setJumpPower(const float power) { jumppower = power; }
	float getMaxJumpPower() { return maxjumppower; }
protected:
	float maxjumppower;
	float jumppower;
	int actioncount = 0;
};