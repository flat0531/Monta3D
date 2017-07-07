#pragma once
#include"ActionBase.h"
#include"cinder/gl/gl.h"
#include<memory>
class Player;
class CharacterBase;
class SlimeAction :public ActionBase{
public:
	SlimeAction();
	SlimeAction(CharacterBase* _player);
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
	int prevoperate = 0;
	void setPrevOperate();
	ci::Vec3f getPrevOperateRotate();
	ci::Vec3f drawrotate;
};