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
using namespace ci;
using namespace ci::app;
SlimeAction::SlimeAction()
{
}
SlimeAction::SlimeAction(CharacterBase * _player)
{
	playerptr = reinterpret_cast<Player*>(_player);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	atackdelaycount = 0;
	atackdelaytime = 45;
	playerptr->setDefalutColor(ColorA(0, 1, 1, 1));
	SoundM.CreateSE("slime_skil.wav");
	playerptr->setName("slime");
	playerptr->setUniqueColor(ColorA(0, 1, 1, 1));
}


void SlimeAction::setup()
{
}

void SlimeAction::update()
{
	float g = 0.015f*WorldScale;
	float dashspeed = 0.1f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, 0));
	playerptr->AddForth(Vec3f(0, -g, 0));
	if (KeyManager::getkey().isPush(KeyEvent::KEY_r)) {
		playerptr->setPos(Vec3f(-300, 700, 0));
	}


	

	if (KeyManager::getkey().isPress(KeyEvent::KEY_e)) {
		playerptr->AddForth(Vec3f(0, 0, dashspeed));
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_c)) {
		playerptr->AddForth(Vec3f(0, 0, -dashspeed));
	}
	playerptr->setCanJump(playerptr->getjumpCount() < 4);
	playerptr->SetIsOpetate(!IsAtackDelay());
	operate();
	if (IsAtackDelay())
		atackdelaycount--;
}

void SlimeAction::draw()
{
	DrawM.drawCube(playerptr->getPos(),playerptr->getScale(),playerptr->getRotate(),playerptr->getColor());
}

void SlimeAction::jump()
{

}

void SlimeAction::attack()
{
	
	atackdelaycount = atackdelaytime;
	SoundM.PlaySE("slime_skil.wav", 0.3f);
	playerptr->setT(1.0f);
	playerptr->setJumming(false);
	if(playerptr->getSpeed().y>0)
	playerptr->setSpeedY(playerptr->getSpeed().y/2.f);
	jumppower = maxjumppower;
	playerptr->setRotate(Vec3f(playerptr->getRotate().x,playerptr->getAttackRotate(),playerptr->getRotate().z));
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();
	
	playerptr->getBulletManagerPointer()->CreatePlayerBullet(SlimeBullet
		(playerptr->getPos()+speed*(WorldScale/2.f),
		ci::Vec3f(0.95,0.95,0.95)*WorldScale,
		ci::Vec3f(speed)*WorldScale*0.1f,
		playerptr->getRotate()+Vec3f(0,0,0)));
	
}

void SlimeAction::operate()
{
	if (IsAtackDelay() || playerptr->getIsStan())return;

	float dashspeed = 0.1f*WorldScale;

	if (KeyManager::getkey().isPush(KeyEvent::KEY_k) && playerptr->getCanJump()) {
		playerptr->setCanJump(false);
		playerptr->setJumming(true);
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

bool SlimeAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}
