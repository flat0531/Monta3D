#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class PumpmanAction :public ActionBase {
public:
	PumpmanAction();
	PumpmanAction(CharacterBase* _enemy);
	void update() override;
	void draw()  override;
	void damaged()override;
	void onLeftWall() override;
	void onRightWall() override;
private:
	Enemy* enemyptr;
	float direction = 1.f;
	float sinrotate = 0.0f;
	float rotate_y = 0.f;
	int updatecount = 0;
};
