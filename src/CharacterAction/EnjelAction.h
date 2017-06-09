#pragma once
#include"ActionBase.h"
#include"cinder/gl/gl.h"
#include<memory>
class Player;
class CharacterBase;
class EnjelAction :public ActionBase {
public:
	EnjelAction();
	EnjelAction(CharacterBase* _player);
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
	void drawAttackcursor();
	void updateAttackcursor();
	float cursorangle = 0.0f;
	bool IsAtackDelay();
	bool ischarge = false;
	bool iscursorup = true;
	int chargecount = 0;
	ci::Vec3f cursorpos;
	std::string bullettexturepath;
	float rotateangle = 0.0f;
	float wingangle = 0.0f;
	float easingwing_t = 1.0f;
	float easingwing_rotate = 0.0f;
};
