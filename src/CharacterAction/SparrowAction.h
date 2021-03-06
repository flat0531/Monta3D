#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class SparrowAction :public ActionBase {
public:
	SparrowAction();
	SparrowAction(CharacterBase* _enemy);
	void update() override;
	void draw()  override;
	void damaged()override;
private:
	Enemy* enemyptr;
	int atackcount = 0;
	float wingangle;
	void onLeftWall() override;
	void onRightWall() override;
};