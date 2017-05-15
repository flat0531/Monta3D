#pragma once
#include"ActionBase.h"
#include<memory>
class Player;
class CharacterBase;
class SlimeAction :public ActionBase{
public:
	SlimeAction();
	SlimeAction(CharacterBase* _player);
	void setup() override;
	void update() override;
	void draw()  override;
	void jump() override;
	void attack()  override;
	void operate();
private:
	Player* playerptr;
	int atackdelaycount;
	int atackdelaytime = 60;
	bool IsAtackDelay();
};