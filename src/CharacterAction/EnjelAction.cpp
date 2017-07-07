#include "EnjelAction.h"
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
#include"../WorldObject/Bullet/AngelBullet.h"
#include"../WorldObject/PlayerDirection.h"
#include"../Top/DataManager.h"
using namespace ci;
using namespace ci::app;

EnjelAction::EnjelAction()
{

}

EnjelAction::EnjelAction(CharacterBase * _player)
{
	playerptr = dynamic_cast<Player*>(_player);

	addpower = int(DataM.getPlayPowerRate()*4.5f);

	playerptr->setDefense(int(DataM.getPlayDefenseRate()*3.5f));

	addspeed = 0.05f*WorldScale*DataM.getPlaySpeedRate();

	maxjumppower = 0.10f*WorldScale;

	jumppower = maxjumppower;
	atackdelaycount = 0;
	atackdelaytime = 25;
	cursorpos = Vec3f(0, 0, 0);
	playerptr->setScale(Vec3f(1, 1, 1)*WorldScale);
	playerptr->setName("angel");
	playerptr->setDefalutColor(ColorA(1, 1, 1, 1));
	SoundM.CreateSE("birdwing.wav");

	TextureM.CreateTexture("Mesh/angelhaneL.png");
	TextureM.CreateTexture("Mesh/angelhaneR.png");
	TextureM.CreateTexture("Mesh/angelHontai.png");
	bullettexturepath = "yasita";
	TextureM.CreateTexture("Mesh/"+bullettexturepath+".png");
	TextureM.CreateMesh(bullettexturepath+".obj");


	TextureM.CreateMesh("angelhaneL.obj");
	TextureM.CreateMesh("angelhaneR.obj");
	TextureM.CreateMesh("angelHontai.obj");
	playerptr->setUniqueColor(ColorA(255.f / 255.f, 153.f / 255.f, 237.f / 255.f, 1));
	playerptr->SetIsOpetate(true);
}

void EnjelAction::setup(ci::Vec3f rotate)
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
	cursorangle = 0.0f;
	ischarge = false;
	iscursorup = true;
	chargecount = 0;
	rotateangle = 0.0f;
	wingangle = 0.0f;
	easingwing_t = 1.0f;
	easingwing_rotate = 0.0f;


}

void EnjelAction::update()
{
	float g = 0.0025f*WorldScale;
	playerptr->setSpeed(Vec3f(0, playerptr->getSpeed().y, playerptr->getSpeed().z));
	if (playerptr->getSpeed().y >= -WorldScale*0.08f)
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
		if (EasingManager::tCountEnd(easingwing_t))
			wingangle += 0.10f;
	}
	else {
		rotateangle += 0.15f;
		if (EasingManager::tCountEnd(easingwing_t))
			wingangle += 0.20f;
	}

	if (rotateangle >= 2.0f*M_PI)
		rotateangle -= 2.0f*M_PI;
	EasingManager::tCount(easingwing_t, 0.25f);
	easingwing_rotate = EasingReturn(easingwing_t, 0.f, 80.f);
}

void EnjelAction::draw()
{

	gl::pushModelView();
	float drawscalecorrection = 65.f;
	float drawposcorrection = -playerptr->getScale().y / 2.f;
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	
	gl::rotate(playerptr->getRotate());
	gl::rotate(Vec3f(0, 0, -10));
	gl::rotate(Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/angelHontai.png").enableAndBind();
	gl::draw(TextureM.getMesh("angelHontai.obj"));
	TextureM.getTexture("Mesh/angelHontai.png").disable();
	gl::popModelView();

	Vec3f drawleftwingposcorrection = Vec3f(-0.4, 1.6, -0.8)*20.f;
	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::translate(drawleftwingposcorrection);
	gl::rotate(Vec3f(-75, 0, 70 - 20 * sin(wingangle) + easingwing_rotate));
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/angelhaneR.png").enableAndBind();
	gl::draw(TextureM.getMesh("angelhaneR.obj"));
	TextureM.getTexture("Mesh/angelhaneR.png").disable();

	gl::popModelView();

	Vec3f drawrightwingposcorrection = Vec3f(0.4, 1.6, -0.8)*20.f;
	gl::pushModelView();
	gl::translate(playerptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(playerptr->getRotate() + Vec3f(0, 90, 0));
	gl::scale(playerptr->getScale() / drawscalecorrection);
	gl::translate(drawrightwingposcorrection);
	gl::rotate(Vec3f(-75, 0, -70 + 20 * sin(wingangle) - easingwing_rotate));
	gl::color(playerptr->getColor());
	TextureM.getTexture("Mesh/angelhaneL.png").enableAndBind();
	gl::draw(TextureM.getMesh("angelhaneL.obj"));
	TextureM.getTexture("Mesh/angelhaneL.png").disable();
	gl::popModelView();




	drawAttackcursor();


}

void EnjelAction::jump()
{

}

void EnjelAction::attack()
{
	atackdelaycount = atackdelaytime;
	playerptr->setT(1.0f);

	playerptr->setRotate(getPrevOperateRotate());
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();

	Vec3f crossvec = speed.cross(Vec3f::yAxis());

	playerptr->getBulletManagerPointer()->CreatePlayerBullet(AngelBullet
		(playerptr->getPos(),
			ci::Vec3f(0.75, 0.75, 0.75)*WorldScale,playerptr->getRotate().y,cursorangle,
			Quatf(crossvec, cursorangle)*  speed *WorldScale*0.3f,chargecount+20, bullettexturepath,4+addpower));
}

void EnjelAction::operate()
{
	if (playerptr->getIsStan())return;

	float dashspeed = 0.07f*WorldScale+addspeed;
	setPrevOperate();
	if (KeyManager::getkey().isPush(KeyEvent::KEY_k)) {
		playerptr->setCanJump(false);
		playerptr->setSpeedY(0.0f);
		playerptr->setJumpPower();
		playerptr->AddForth(Vec3f(0, jumppower, 0));
		easingwing_t = 0.0f;
		wingangle = 0.0f;
		SoundM.PlaySE("birdwing.wav",0.5f);
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_a) && (!KeyManager::getkey().isPress(KeyEvent::KEY_w))) {
		playerptr->AddForth(Vec3f(dashspeed, 0, 0));
	}
	if (KeyManager::getkey().isPress(KeyEvent::KEY_d) && (!KeyManager::getkey().isPress(KeyEvent::KEY_w))) {
		playerptr->AddForth(Vec3f(-dashspeed, 0, 0));
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_l) && (!IsAtackDelay())) {
		cursorangle = 0.0f;
		ischarge = true;
		chargecount = 0;
	}
	if (ischarge) {
		updateAttackcursor();
		chargecount++;
		if (chargecount >= 60)chargecount = 60;
	}
	if (ischarge&&KeyManager::getkey().isPull(KeyEvent::KEY_l)) {
		attack();
		iscursorup = true;
		ischarge = false;
	}
}

void EnjelAction::drawAttackcursor()
{
	if (ischarge) {
		DrawM.drawCube(cursorpos,Vec3f(0.5,0.5,0.5)*WorldScale,Vec3f(cursorangle,cursorangle,cursorangle)*200.f,ColorA(1,0.5+0.5*cos(cursorangle*10.f),0,1));
	}
}

void EnjelAction::updateAttackcursor()
{
	float cursorspeed = 0.015f;
	float anglemax = M_PI / 8.f;
	if (iscursorup) {
		cursorangle += cursorspeed;
		if (cursorangle >= anglemax) {
			cursorangle = anglemax;
			iscursorup = false;
		}
	}
	else {
		cursorangle -= cursorspeed;
		if (cursorangle <= -anglemax) {
			cursorangle = -anglemax;
			iscursorup = true;
		}
	}
	ci::Vec3f speed = ci::Quatf(ci::toRadians(getPrevOperateRotate().x),
		ci::toRadians(getPrevOperateRotate().y),
		ci::toRadians(getPrevOperateRotate().z))*ci::Vec3f::xAxis();
	Vec3f crossvec = speed.cross(Vec3f::yAxis());

	cursorpos = playerptr->getPos() + Quatf(crossvec, cursorangle) *  speed *WorldScale*4.0f;
	
	
}

bool EnjelAction::IsAtackDelay()
{
	return atackdelaycount != 0;
}

ci::Vec3f EnjelAction::getPrevOperateRotate()
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

void EnjelAction::setPrevOperate()
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
