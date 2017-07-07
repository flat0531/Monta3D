#include "WalkRattonAction.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
WalkRattonAction::WalkRattonAction()
{
}

WalkRattonAction::WalkRattonAction(CharacterBase * _enemy)
{
	enemyptr = dynamic_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 7;
	enemyptr->setRotate(Vec3f(0, 180, 0));
	enemyptr->setMaxHp(maxhp);
	enemyptr->setHp(maxhp);
	enemyptr->setDefalutColor(ColorA(1, 1, 1, 1));
	enemyptr->setColor(ColorA(1, 1, 1, 1));
	enemyptr->setName("ratton");
	enemyptr->setUniqueColor(ColorA(102.f / 256.f, 102.f / 256.f, 102.f / 256.f, 1));
	TextureM.CreateMesh("Rat.obj");
	TextureM.CreateTexture("Mesh/Rat.png");
}

void WalkRattonAction::update()
{
	float g = 0.012f*WorldScale;
	enemyptr->AddForth(Vec3f(0, -g, 0));
	enemyptr->setCanJump(enemyptr->getjumpCount() < 4);
	updateOnload();
	if (isonload) {
		if (actioncount % 15 == 0) {
			bool isdirection = enemyptr->getCharacterManager()->getPlayer()->getPos().x >= enemyptr->getPos().x;
			if (isdirection)direction = 1;
			else direction = -1;
			enemyptr->setSpeedX(direction*WorldScale*0.05f);
			if (isdirection)enemyptr->setRotate(Vec3f(0,90,0));
			else enemyptr->setRotate(Vec3f(0, -90, 0));
		}
		actioncount++;
	}
	sinrotate += 0.15f;
	if (sinrotate > 2.0f*M_PI)sinrotate -= 2.0f*M_PI;

}

void WalkRattonAction::draw()
{
	gl::pushModelView();
	float drawscalecorrection = 24.f;
	float drawposcorrection = -WorldScale*0.5f;
	gl::translate(enemyptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(enemyptr->getRotate() + Vec3f(0, 20 * sin(sinrotate), 0));
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/Rat.png").enableAndBind();
	gl::draw(TextureM.getMesh("Rat.obj"));
	TextureM.getTexture("Mesh/Rat.png").disable();
	gl::popModelView();
}

void WalkRattonAction::onLeftWall()
{
	if (enemyptr->getSpeed().y <= 0.0f&&enemyptr->getCanJump()) {
		enemyptr->AddForth(Vec3f(0, WorldScale*0.2f, 0));
		enemyptr->setCanJump(false);
	}
}

void WalkRattonAction::onRightWall()
{
	if (enemyptr->getSpeed().y <= 0.0f&&enemyptr->getCanJump()) {
		enemyptr->AddForth(Vec3f(0, WorldScale*0.2f, 0));
		enemyptr->setCanJump(false);
	}
}

void WalkRattonAction::damaged()
{
	enemyptr->setSpeed(Vec3f(0,0,0));
}

void WalkRattonAction::updateOnload()
{
	if (!isonload) {
		if (enemyptr->getPos().z>0) {
			if (std::abs(enemyptr->getCharacterManager()->getPlayer()->getPos().x - enemyptr->getPos().x) < WorldScale*15.f) {
				enemyptr->setSpeedZ(-WorldScale*0.06f);
			}
			enemyptr->setRotate(Vec3f(0, 180, 0));
		}
		else {
			enemyptr->setSpeedZ(0.0f);
			enemyptr->setPosZ(0.0f);
			isonload = true;
		}
	}
}
