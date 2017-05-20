#include "CatAction.h"
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
using namespace ci;
using namespace ci::app;
CatAction::CatAction()
{
}
CatAction::CatAction(CharacterBase * _player)
{
	playerptr = reinterpret_cast<Player*>(_player);
	playerptr->setDefalutColor(ColorA(1, 0.5, 0, 1));
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	SoundM.CreateSE("cat_skil.wav");
	playerptr->setName("cat");
	playerptr->setUniqueColor(ColorA(1, 1, 1, 1));
}

void CatAction::setup()
{
}

void CatAction::update()
{
	float g = 0.012f*WorldScale;
	float dashspeed = 0.2f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, playerptr->getSpeed().z));
	playerptr->AddForth(Vec3f(0, -g, 0));
	if (KeyManager::getkey().isPush(KeyEvent::KEY_r)) {
		playerptr->setPos(Vec3f(0, 0, 0));
	}

	operate();
	playerptr->setCanJump(playerptr->getjumpCount()<4);

}

void CatAction::draw()
{
	DrawM.drawCube(playerptr->getPos(), playerptr->getScale(), playerptr->getRotate(),playerptr->getColor());
}

void CatAction::jump()
{
}

void CatAction::attack()
{
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();
	Vec3f crossvec = speed.cross(Vec3f::yAxis());
	int createnum = 20;
	for (int i = 0;i < createnum; i++ ){
		float angle = (float(i) / (float(createnum)))*(M_PI*2.f);
		ColorA color;
		if (i % 3 == 0)color = ColorA(1, 1, 1, 1);
		if (i % 3 == 1)color = ColorA(0, 1, 0, 1);
		if (i % 3 == 2)color = ColorA(1, 1, 0, 1);
	playerptr->getBulletManagerPointer()->CreatePlayerBullet(CatBullet(playerptr->getPos()
		+ Quatf(crossvec,angle)*  speed *WorldScale,
		ci::Vec3f(1.2, 1.2f, 1.2f)*WorldScale,
		angle,
		playerptr->getRotate(), color,playerptr));
	}
	SoundM.PlaySE("cat_skil.wav",0.5f);
}

Player * CatAction::getPlayer()
{
	return playerptr;
}

void CatAction::operate()
{
	if (playerptr->getIsStan())return;

	float dashspeed = 0.1f*WorldScale;

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
