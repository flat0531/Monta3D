#pragma once
#include"ActionBase.h"
class Player;
class PlayerActionBase :public ActionBase {
public:
	Player* getPlayer();
private:
	Player* playerptr;
};