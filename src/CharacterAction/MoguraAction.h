#pragma once
#include"ActionBase.h"
#include"cinder/gl/Texture.h"
#include<memory>
class Player;
class CharacterBase;
class MoguraAction :public ActionBase {
public:
	MoguraAction();
	MoguraAction(CharacterBase* _player);
	void setup(ci::Vec3f rotate) override;
	void update() override;
	void draw()  override;
	void jump() override;
	void attack()  override;
private:
	Player* playerptr;
	ci::gl::Texture bodytex;
	ci::gl::Texture foottex;
	ci::Vec3f drawrotate;
	float atacck_t = 0.0f;
	float easing_atacck_rotate = 0.0f;
	int atackdelaycount;
	int atackdelaytime = 60;
	bool IsAtackDelay();
	float rotateangle = 0.0f;
	void operate();
};
