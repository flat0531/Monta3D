#pragma once
#include"ActionBase.h"
#include<memory>
class Enemy;
class CharacterBase;
class WitchAction :public ActionBase {
public:
	WitchAction();
	WitchAction(CharacterBase* _enemy);
	void setup() override;
	void update() override;
	void draw()  override;
	void jump() override;
	void attack()  override;
private:
	Enemy* enemyptr;
	int atackdelay;
	bool isCanAtack();
	bool isDlay();
	float drawscalecorrection;
	bool atackstart;
	float houkirotate;
	float houkirotatespeed;
	float houkirotate_t;
	int controlcount;
};