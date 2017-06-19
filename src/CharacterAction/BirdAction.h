#pragma once
#include"ActionBase.h"
#include"cinder/gl/gl.h"
#include<memory>
class Player;
class CharacterBase;
class BirdAction :public ActionBase {
public:
	BirdAction();
	BirdAction(CharacterBase* _player);
	void setup(ci::Vec3f rotate) override;
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
	float rotateangle = 0.0f;
	float wingangle = 0.0f;
	float easingwing_t = 1.0f;
	float easingwing_rotate = 0.0f;
	int prevoperate = 0;
	ci::Vec3f getPrevOperateRotate();
	void setPrevOperate();
};
