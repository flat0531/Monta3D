#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class RattonAction :public ActionBase {
public:
	RattonAction();
	RattonAction(CharacterBase* _enemy);
	void setup() override;
	void update() override;
	void draw()  override;
	void jump() override;
	void attack()  override;
private:
	Enemy* enemyptr;
	int atackcount = 0;
	bool IsCanAtack();
};