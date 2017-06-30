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
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../WorldObject/PlayerDirection.h"
using namespace ci;
using namespace ci::app;
CatAction::CatAction()
{
}
CatAction::CatAction(CharacterBase * _player)
{
	playerptr = dynamic_cast<Player*>(_player);
	playerptr->setDefalutColor(ColorA(1, 1, 1, 1));
	playerptr->setScale(Vec3f(1,1,1)*WorldScale);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	SoundM.CreateSE("cat_skil.wav");
	playerptr->setName("cat");
	foottex = TextureM.CreateTexture("Mesh/nekoAsi.png");
	bodytex = TextureM.CreateTexture("Mesh/nekoJouhansin.png");

	TextureM.CreateMesh("nekoAsi.obj");
	TextureM.CreateMesh("nekoJouhansin.obj");
	drawrotate = Vec3f(0, 0, 0);
	playerptr->setUniqueColor(ColorA(1, 1, 1, 1));
	atackdelaycount = 0;
	atackdelaytime = 60;
	playerptr->SetIsOpetate(true);
}

void CatAction::setup(ci::Vec3f rotate)
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

void CatAction::update()
{
	float g = 0.012f*WorldScale;
	float dashspeed = 0.2f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, playerptr->getSpeed().z));
	playerptr->AddForth(Vec3f(0, -g, 0));
	playerptr->setCanJump(playerptr->getjumpCount()<4);
	operate();
	if (IsAtackDelay()) {
		atackdelaycount--;
		EasingManager::tCount(atacck_t,((float(atackdelaytime))/60.f)*0.8f);
		easing_atacck_rotate= EasingCubicOut(atacck_t, 0.0f, -360.f);
	}
	else {
		atacck_t = 0.0f;
	}
	if (playerptr->getSpeed().x == 0.0f|| (!playerptr->getCanJump())) {
		rotateangle += 0.05f;
	}
	else {
		rotateangle += 0.15f;
	}
	if (rotateangle >= 2.0f*M_PI)
		rotateangle -= 2.0f*M_PI;
	drawrotate = Vec3f(0, 15.f*sin(rotateangle), 0);

	

}

void CatAction::draw()
{

	float sizerate = 1.f / 80.f;
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
	gl::draw(TextureM.getMesh("nekoJouhansin.obj"));
	bodytex.disable();
	gl::popModelView();



	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, -playerptr->getScale().y*sizerate*2.0f, 0));
	gl::rotate(drawrotate);
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 180));

	gl::translate(Vec3f(0, -(playerptr->getScale().y / 4.f), 0));
	gl::rotate(Vec3f(-easing_atacck_rotate, 0, 0));
	gl::translate(Vec3f(0, (playerptr->getScale().y / 4.f), 0));

	gl::translate(Vec3f(-15,0,0));
	gl::rotate(Vec3f(30.f*sin(rotateangle), 0,0));
	gl::scale(drawrate);
	gl::color(playerptr->getColor());
	foottex.enableAndBind();
	gl::draw(TextureM.getMesh("nekoAsi.obj"));
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
	gl::draw(TextureM.getMesh("nekoAsi.obj"));
	foottex.disable();
	gl::popModelView();

}

void CatAction::jump()
{
}

void CatAction::attack()
{
	playerptr->setRotate(getPrevOperateRotate());
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
		atacck_t = 0.0f;
	playerptr->getBulletManagerPointer()->CreatePlayerBullet(CatBullet(playerptr->getPos()
		+ Quatf(crossvec,angle)*  speed *WorldScale*1.4f,
		ci::Vec3f(1, 1, 1)*WorldScale,
		angle,
		playerptr->getRotate(), color,playerptr));
	}
	atackdelaycount = atackdelaytime;
	SoundM.PlaySE("cat_skil.wav",0.5f);
}

Player * CatAction::getPlayer()
{
	return playerptr;
}

bool CatAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}

void CatAction::operate()
{
	if (playerptr->getIsStan())return;
	setPrevOperate();
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
	if (KeyManager::getkey().isPush(KeyEvent::KEY_l)&& (!IsAtackDelay())) {
		attack();
	}
}

ci::Vec3f CatAction::getPrevOperateRotate()
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

void CatAction::setPrevOperate()
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
