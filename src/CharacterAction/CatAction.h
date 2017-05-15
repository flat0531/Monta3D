#pragma once
#include"ActionBase.h"
#include<memory>
class Player;
class CharacterBase;
class CatAction :public ActionBase {
public:
	CatAction();
	CatAction(CharacterBase* _player);
	void setup() override;
	void update() override;
	void draw()  override;
	void jump() override;
	void attack()  override;
	Player* getPlayer();
private:
	Player* playerptr;
	void operate();
};