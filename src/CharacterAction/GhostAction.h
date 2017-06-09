#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class GhostAction :public ActionBase {
public:
	GhostAction();
	GhostAction(CharacterBase* _enemy);
	void update() override;
	void draw()  override;
	void damaged()override;
private:
	Enemy* enemyptr;
	float sinrotate = 0.0f;
	int updatecount = 0;
	int direction_left = 1;
};
