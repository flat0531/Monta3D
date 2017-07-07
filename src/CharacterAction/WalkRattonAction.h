#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class WalkRattonAction :public ActionBase {
public:
	WalkRattonAction();
	WalkRattonAction(CharacterBase* _enemy);
	void update() override;
	void draw()  override;
	void onLeftWall() override;
	void onRightWall() override;
	void damaged()override;
private:
	Enemy* enemyptr;
	void updateOnload();///プレイヤーのZ座標まで移動
	bool isonload = false;
	int direction = 1;
	float sinrotate = 0.0f;
};