#include "MoguraAction.h"
#include "../WorldObject/Player.h"
#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../CharacterAction/ActionBase.h"
#include"../WorldObject/Bullet/CatBullet.h"
#include"../WorldCreater/BulletManager.h"
#include"../Top/SoundManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../Top/DrawManager.h"
#include"../Top/SoundManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../WorldObject/PlayerDirection.h"
#include"../WorldObject/Bullet/MoguraBullet.h"
using namespace ci;
using namespace ci::app;
MoguraAction::MoguraAction()
{
}

MoguraAction::MoguraAction(CharacterBase * _player)
{
	playerptr = dynamic_cast<Player*>(_player);
	playerptr->setDefalutColor(ColorA(1, 1, 1, 1));
	playerptr->setScale(Vec3f(1, 1, 1)*WorldScale);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	SoundM.CreateSE("cat_skil.wav");
	playerptr->setName("mogura");
	foottex = TextureM.CreateTexture("Mesh/moguraAsi.png");
	bodytex = TextureM.CreateTexture("Mesh/moguraHontai.png");

	TextureM.CreateMesh("moguraAsi.obj");
	TextureM.CreateMesh("moguraHontai.obj");
	drawrotate = Vec3f(0, 0, 0);
	playerptr->setUniqueColor(ColorA(1, 88.f / 255.f, 0, 1));
	atackdelaycount = 0;
	atackdelaytime = 60;
	playerptr->SetIsOpetate(true);
}

void MoguraAction::setup(ci::Vec3f rotate)
{
	playerptr->setRotate(rotate);
	if (rotate.y == -180.f) {
		playerptr->setPlayerDirection(PlayerDirection::RIGHT_DIRECTION);
	}
	else {
		playerptr->setPlayerDirection(PlayerDirection::LEFT_DIRECTION);
	}
	prevoperate = 0;
	playerptr->setT(1.0f);
	playerptr->setSpeed(Vec3f(0, 0, 0));
	playerptr->setCanJump(false);
	playerptr->setIsStun(false);
	playerptr->setIsinvincible(false);
	playerptr->SetIsOpetate(true);

	atacck_t = 0.0f;
	easing_atacck_rotate = 0.0f;
	atackdelaycount = 0;
	rotateangle = 0.0f;
}

void MoguraAction::update()
{
	float g = 0.015f*WorldScale;
	setPrevOperate();
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, playerptr->getSpeed().z));
	playerptr->AddForth(Vec3f(0, -g, 0));
	playerptr->setCanJump(playerptr->getjumpCount()<4);
	operate();
	if (IsAtackDelay()) {
		atackdelaycount--;
		EasingManager::tCount(atacck_t, ((float(atackdelaytime)) / 60.f)*0.8f);
		easing_atacck_rotate = EasingCubicOut(atacck_t, 0.0f, -360.f);
	}
	else {
		atacck_t = 0.0f;
	}
	if (playerptr->getSpeed().x == 0.0f || (!playerptr->getCanJump())) {
		rotateangle += 0.05f;
	}
	else {
		rotateangle += 0.15f;
	}
	if (rotateangle >= 2.0f*M_PI)
		rotateangle -= 2.0f*M_PI;
	drawrotate = Vec3f(0, 15.f*sin(rotateangle), 0);
}

void MoguraAction::draw()
{

	float sizerate = 1.f / 70.f;
	Vec3f drawrate = Vec3f(playerptr->getScale().x*sizerate*1.2f, playerptr->getScale().y*sizerate, playerptr->getScale().z*sizerate*1.5f);
	gl::pushModelView();
	gl::translate(playerptr->getPos() - Vec3f(0, playerptr->getScale().y / 2.f, 0));

	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0) + drawrotate);
	gl::scale(drawrate);
	gl::translate(Vec3f(0, playerptr->getScale().y / 2.f, 0));
	gl::rotate(Vec3f(easing_atacck_rotate, 0, 0));
	gl::translate(Vec3f(0, -playerptr->getScale().y / 2.f, 0));

	gl::color(playerptr->getColor());
	bodytex.enableAndBind();
	gl::draw(TextureM.getMesh("moguraHontai.obj"));
	bodytex.disable();
	gl::popModelView();



	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, -playerptr->getScale().y*sizerate*2.0f, 0));
	gl::rotate(drawrotate);
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 180));

	gl::translate(Vec3f(0, -(playerptr->getScale().y / 4.f), 0));
	gl::rotate(Vec3f(-easing_atacck_rotate, 0, 0));
	gl::translate(Vec3f(0, (playerptr->getScale().y / 4.f), 0));

	gl::translate(Vec3f(-15, 0, 0));
	gl::rotate(Vec3f(30.f*sin(rotateangle), 0, 0));
	gl::scale(drawrate);
	gl::color(playerptr->getColor());
	foottex.enableAndBind();
	gl::draw(TextureM.getMesh("moguraAsi.obj"));
	foottex.disable();
	gl::popModelView();




	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, -playerptr->getScale().y*sizerate*2.0f, 0));


	gl::rotate(drawrotate);
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 180));

	gl::translate(Vec3f(0, -(playerptr->getScale().y / 4.f), 0));
	gl::rotate(Vec3f(-easing_atacck_rotate, 0, 0));
	gl::translate(Vec3f(0, (playerptr->getScale().y / 4.f), 0));

	gl::translate(Vec3f(15, 0, 0));
	gl::rotate(Vec3f(-30.f*sin(rotateangle), 0, 0));
	gl::scale(drawrate);
	gl::color(playerptr->getColor());
	foottex.enableAndBind();
	gl::draw(TextureM.getMesh("moguraAsi.obj"));
	foottex.disable();
	gl::popModelView();
}

void MoguraAction::jump()
{
}

void MoguraAction::attack()
{
	playerptr->setRotate(getPrevOperateRotate());
	playerptr->setT(1.0f);

	float createnum = 3.f;
	float length = 13.f;

	for (float i = 0;i < createnum;i++) {
		float angle = -((createnum - 1.0f) / 2.f)*length + length*i;

		ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
			ci::toRadians(playerptr->getRotate().y+angle),
			ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();

		playerptr->getBulletManagerPointer()->CreatePlayerBullet(MoguraBullet
			(playerptr->getPos() + speed*(WorldScale / 2.f),
				ci::Vec3f(0.95, 0.95, 0.95)*WorldScale,
				ci::Vec3f(speed)*WorldScale*0.25f,
				playerptr->getRotate()));
	}
	atacck_t = 0.0f;
	atackdelaycount = atackdelaytime;
	SoundM.PlaySE("cat_skil.wav");
}

bool MoguraAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}

void MoguraAction::operate()
{
	if (playerptr->getIsStan())return;

	float dashspeed = 0.12f*WorldScale;

	if (KeyManager::getkey().isPush(KeyEvent::KEY_k) && playerptr->getCanJump()) {
		playerptr->setCanJump(false);
		playerptr->setJumming(true);
		playerptr->setSpeedY(0.0f);
		playerptr->setJumpPower();
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_k) && playerptr->IsJumpping()) {
		playerptr->AddForth(Vec3f(0, jumppower, 0));
		jumppower -= 0.009f*WorldScale;
		jumppower = std::max(0.0f, jumppower);

	}
	if (playerptr->IsJumpping() && (KeyManager::getkey().isPull(KeyEvent::KEY_k) || jumppower <= 0.0f)) {
		playerptr->setJumming(false);
		jumppower = maxjumppower;
	}

	if (KeyManager::getkey().isPress(KeyEvent::KEY_a) && (!KeyManager::getkey().isPress(KeyEvent::KEY_w))) {
		playerptr->AddForth(Vec3f(dashspeed, 0, 0));
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_d) && (!KeyManager::getkey().isPress(KeyEvent::KEY_w))) {
		playerptr->AddForth(Vec3f(-dashspeed, 0, 0));
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_l) && (!IsAtackDelay())) {
		attack();
	}
}

ci::Vec3f MoguraAction::getPrevOperateRotate()
{
	switch (prevoperate)
	{
	case 0:
		return playerptr->getRotate();
	case 1:
		return Vec3f(playerptr->getRotate().x, -90, playerptr->getRotate().z);
	case 2:
		return Vec3f(playerptr->getRotate().x, 0.f, playerptr->getRotate().z);
	case 3:
		return Vec3f(playerptr->getRotate().x, -180.f, playerptr->getRotate().z);
	}
	return playerptr->getRotate();
}

void MoguraAction::setPrevOperate()
{
	if (KeyManager::getkey().isPress(KeyEvent::KEY_w)) {
		prevoperate = 1;
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_a)) {
		prevoperate = 2;
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_d)) {
		prevoperate = 3;
	}
}
