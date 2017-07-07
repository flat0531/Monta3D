#include "BirdAction.h"
#include "../WorldObject/Player.h"
#include"../Top/Top.h"
#include"../Input/KeyManager.h"
#include"../CharacterAction/ActionBase.h"
#include"../WorldCreater/BulletManager.h"
#include"../Top/SoundManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../WorldObject/Bullet/BirdBullet.h"
#include"../WorldObject/PlayerDirection.h"
#include"../Top/DataManager.h"
using namespace ci;
using namespace ci::app;


BirdAction::BirdAction()
{
}

BirdAction::BirdAction(CharacterBase * _player)
{
	playerptr = dynamic_cast<Player*>(_player);
	addpower = int(DataM.getPlayPowerRate()*5.5f);

	playerptr->setDefense(int(DataM.getPlayDefenseRate()*3.5f));

	addspeed = 0.05f*WorldScale*DataM.getPlaySpeedRate();

	maxjumppower = 0.15f*WorldScale;

	jumppower = maxjumppower;
	atackdelaycount = 0;
	atackdelaytime = 25;
	playerptr->setScale(Vec3f(1, 1, 1)*WorldScale);
	playerptr->setName("bird");
	playerptr->setDefalutColor(ColorA(1, 1, 1, 1));
	SoundM.CreateSE("birdwing.wav");
	SoundM.CreateSE("bird_skil.wav");
	TextureM.CreateTexture("Mesh/montaHaneL.png");
	TextureM.CreateTexture("Mesh/montaHaneR.png");
	TextureM.CreateTexture("Mesh/montaTori.png");

	TextureM.CreateMesh("montaHaneL.obj");
	TextureM.CreateMesh("montaHaneR.obj");
	TextureM.CreateMesh("montaTori.obj");
	playerptr->setUniqueColor(ColorA(157.f / 255.f, 76.f / 255.f, 229.f / 255.f, 1));
	playerptr->SetIsOpetate(true);
}

void BirdAction::setup(ci::Vec3f rotate)
{
	playerptr->setRotate(rotate);
	if (rotate.y == -180.f) {
		playerptr->setPlayerDirection(PlayerDirection::RIGHT_DIRECTION);
	}
	else {
		playerptr->setPlayerDirection(PlayerDirection::LEFT_DIRECTION);
	}

	playerptr->setT(1.0f);
	playerptr->setSpeed(Vec3f(0, 0, 0));
	playerptr->setCanJump(false);
	playerptr->setIsStun(false);
	playerptr->setIsinvincible(false);
	playerptr->SetIsOpetate(true);
	prevoperate = 0;
	atackdelaycount = 0;
	rotateangle = 0.0f;
	wingangle = 0.0f;
	easingwing_t = 1.0f;
	easingwing_rotate = 0.0f;
}


void BirdAction::update()
{
	float g = 0.005f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, playerptr->getSpeed().z));
	if(playerptr->getSpeed().y>=-WorldScale*0.12f)
	playerptr->AddForth(Vec3f(0, -g, 0));
	playerptr->setCanJump(playerptr->getjumpCount()<4);
	operate();
	if (IsAtackDelay()) {
		atackdelaycount--;
	}
	else {
	}
	if (playerptr->getSpeed().x == 0.0f || (!playerptr->getCanJump())) {
		rotateangle += 0.05f;
		if(EasingManager::tCountEnd(easingwing_t))
		wingangle += 0.10f;
	}
	else {
		rotateangle += 0.15f;
		if (EasingManager::tCountEnd(easingwing_t))
		wingangle += 0.20f;
	}

	if (rotateangle >= 2.0f*M_PI)
		rotateangle -= 2.0f*M_PI;
	EasingManager::tCount(easingwing_t,0.25f);
	easingwing_rotate = EasingReturn(easingwing_t, 0.f, 80.f);
}

void BirdAction::draw()
{

	gl::pushModelView();
	float drawscalecorrection = 65.f;
	float drawposcorrection = -playerptr->getScale().y / 2.f;
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/montaTori.png").enableAndBind();
	gl::draw(TextureM.getMesh("montaTori.obj"));           
	TextureM.getTexture("Mesh/montaTori.png").disable();
	gl::popModelView();

	Vec3f drawleftwingposcorrection = Vec3f(-0.4, 1.5, 0.3)*20.f;
	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::translate(drawleftwingposcorrection);
	gl::rotate(Vec3f(180, 0, 70 - 20 * sin(wingangle)+ easingwing_rotate));
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/montaHaneR.png").enableAndBind();
	gl::draw(TextureM.getMesh("montaHaneR.obj"));
	TextureM.getTexture("Mesh/montaHaneR.png").disable();

	gl::popModelView();

	Vec3f drawrightwingposcorrection = Vec3f(0.4, 1.5, 0.3)*20.f;
	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::translate(drawrightwingposcorrection);
	gl::rotate(Vec3f(180, 0, -70 + 20 * sin(wingangle)- easingwing_rotate));
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/montaHaneL.png").enableAndBind();
	gl::draw(TextureM.getMesh("montaHaneL.obj"));
	TextureM.getTexture("Mesh/montaHaneL.png").disable();
	gl::popModelView();

}

void BirdAction::jump()
{
}

void BirdAction::attack()
{
	atackdelaycount = atackdelaytime;
	playerptr->setT(1.0f);

	playerptr->setRotate(getPrevOperateRotate());
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();

	

	playerptr->getBulletManagerPointer()->CreatePlayerBullet(BirdBullet
		(playerptr->getPos() + speed*(WorldScale / 2.f),
			ci::Vec3f(0.95, 0.95, 0.95)*WorldScale,
			ci::Vec3f(speed)*WorldScale*0.1f,
			playerptr->getRotate() + Vec3f(0, 0, 0), 7 + addpower));

	SoundM.PlaySE("bird_skil.wav",0.5f);
}

void BirdAction::operate()
{
	if (IsAtackDelay() || playerptr->getIsStan())return;

	float dashspeed = 0.07f*WorldScale + addspeed;
	setPrevOperate();
	if (KeyManager::getkey().isPush(KeyEvent::KEY_k)) {
		playerptr->setCanJump(false);
		playerptr->setSpeedY(0.0f);
		playerptr->setJumpPower();
		playerptr->AddForth(Vec3f(0, jumppower, 0));
		easingwing_t = 0.0f;
		wingangle = 0.0f;
		SoundM.PlaySE("birdwing.wav",0.3f);
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

bool BirdAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}

ci::Vec3f BirdAction::getPrevOperateRotate()
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

void BirdAction::setPrevOperate()
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