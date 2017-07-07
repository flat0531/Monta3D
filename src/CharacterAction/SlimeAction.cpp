#include "SlimeAction.h"
#include "../WorldObject/Player.h"
#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../CharacterAction/ActionBase.h"
#include"../CharacterAction/SlimeAction.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldObject/Bullet/SlimeBullet.h"
#include"../Top/SoundManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../WorldObject/Bullet/MyToras.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../WorldObject/PlayerDirection.h"
#include"../Top/DataManager.h"
using namespace ci;
using namespace ci::app;
SlimeAction::SlimeAction()
{
}
SlimeAction::SlimeAction(CharacterBase * _player)
{
	playerptr = dynamic_cast<Player*>(_player);



	addpower = int(DataM.getPlayPowerRate()*4.5f);
	
	addspeed = 0.07f*WorldScale*DataM.getPlaySpeedRate();

	playerptr->setDefense(int(DataM.getPlayDefenseRate()*3.5f));

	maxjumppower = 0.085f*WorldScale;

	jumppower = maxjumppower;
	atackdelaycount = 0;
	atackdelaytime = 45;
	playerptr->setScale(Vec3f(1,1,1)*WorldScale);
	playerptr->setName("slime");
	playerptr->setDefalutColor(ColorA(1, 1, 1, 1));
	SoundM.CreateSE("slime_skil.wav");

	TextureM.CreateTexture("Mesh/montaKahansin.png");
	TextureM.CreateTexture("Mesh/montaJouhansin.png");

	TextureM.CreateMesh("montaJouhansin.obj");
	TextureM.CreateMesh("montaKahansin.obj");
	drawrotate = Vec3f(0, 0, 0);
	playerptr->setUniqueColor(ColorA(0, 1, 1, 1));
}

void SlimeAction::setup(ci::Vec3f rotate)
{
	playerptr->setRotate(rotate);
	if (rotate.y == -180.f) {
		playerptr->setPlayerDirection(PlayerDirection::RIGHT_DIRECTION);
	}
	else {
		playerptr->setPlayerDirection(PlayerDirection::LEFT_DIRECTION);
	}
	
	playerptr->setT(1.0f);

	playerptr->setSpeed(Vec3f(0,0,0));
	playerptr->setCanJump(false);
	playerptr->setIsStun(false);
	playerptr->setIsinvincible(false);
	playerptr->SetIsOpetate(true);
	prevoperate = 0;
	atackdelaycount = 0;
}

void SlimeAction::update()
{
	float g = 0.015f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, 0));
	playerptr->AddForth(Vec3f(0, -g, 0));
	playerptr->setCanJump(playerptr->getjumpCount() < 4);
	playerptr->SetIsOpetate(!IsAtackDelay());
	operate();
	if (IsAtackDelay()) {
		atackdelaycount--;
	}
	else {
		if (playerptr->getCanJump()) {
			if (playerptr->getSpeed().x == 0.0f) {
				rotateangle += 0.05f;
			}
			else {
				rotateangle += 0.15f;
			}
		}
		else {
			rotateangle = 0.0f;
		}
	}
	drawrotate = Vec3f(0,50.f*sin(rotateangle),0);
}

void SlimeAction::draw()
{
	float sizerate = 1.f/60.f;
	gl::pushModelView();
	gl::translate(playerptr->getPos()-Vec3f(0,playerptr->getScale().y/2.f,0));
	gl::scale(playerptr->getScale()*sizerate);
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0) + drawrotate*0.3f);
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/montaKahansin.png").enableAndBind();
	gl::draw(TextureM.getMesh("montaJouhansin.obj"));
	TextureM.getTexture("Mesh/montaKahansin.png").disable();
	gl::popModelView();

	gl::pushModelView();
	gl::translate(playerptr->getPos() - Vec3f(0, playerptr->getScale().y / 2.f, 0));
	gl::scale(playerptr->getScale()*sizerate);
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0)+drawrotate);
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/montaKahansin.png").enableAndBind();
	gl::draw(TextureM.getMesh("montaKahansin.obj"));
	TextureM.getTexture("Mesh/montaKahansin.png").disable();
	gl::popModelView();

}

void SlimeAction::jump()
{

}

void SlimeAction::attack()
{
	
	atackdelaycount = atackdelaytime;
	SoundM.PlaySE("slime_skil.wav", 0.3f);
	playerptr->setT(1.0f);
	playerptr->setRotate(getPrevOperateRotate());
	playerptr->setJumming(false);
	if(playerptr->getSpeed().y>0)
	playerptr->setSpeedY(playerptr->getSpeed().y/2.f);
	jumppower = maxjumppower;
	rotateangle = 0.0f;
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();
	
	playerptr->getBulletManagerPointer()->CreatePlayerBullet(SlimeBullet
		(playerptr->getPos()+speed*(WorldScale/2.f),
		ci::Vec3f(0.95,0.95,0.95)*WorldScale,
		ci::Vec3f(speed)*WorldScale*0.1f,
		playerptr->getRotate()+Vec3f(0,0,0),5+addpower));
	
}

void SlimeAction::operate()
{
	if (IsAtackDelay() || playerptr->getIsStan())return;

	float dashspeed = 0.07f*WorldScale+addspeed;

	setPrevOperate();
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
	if (KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
		attack();
	}
}

void SlimeAction::setPrevOperate()
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

bool SlimeAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}

ci::Vec3f SlimeAction::getPrevOperateRotate()
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
