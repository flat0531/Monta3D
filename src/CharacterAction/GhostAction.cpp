#include "GhostAction.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldObject/Bullet/NormalEnemyBullet.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
GhostAction::GhostAction()
{
}

GhostAction::GhostAction(CharacterBase * _enemy)
{
	enemyptr = dynamic_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 12;
	enemyptr->setRotate(Vec3f(0, M_PI / 2.f, 0));
	enemyptr->setMaxHp(maxhp);
	enemyptr->setHp(maxhp);
	enemyptr->setDefalutColor(ColorA(1, 1, 1, 1));
	enemyptr->setName("ghost");
	enemyptr->setUniqueColor(ColorA(1, 1, 1, 1));
	TextureM.CreateMesh("obake.obj");
	TextureM.CreateTexture("Mesh/obake.png");
}

void GhostAction::update()
{
	float g = 0.004f*WorldScale;
	enemyptr->AddForth(Vec3f(0, -g, 0));

	sinrotate += 0.075f;

	if (sinrotate >= 2.f*M_PI)sinrotate -= 2.f*M_PI;

	enemyptr->setRotateY((90.f*direction_left) + 25.f*sin(sinrotate));
	if (updatecount % 250<125) {
		direction_left = 1;
	}
	else {
		direction_left = -1;
	}
	enemyptr->setSpeedX(direction_left*WorldScale*0.05f);
	if (updatecount % 400 == 150) {
		enemyptr->setSpeedY(WorldScale*0.15f);
	}
	updatecount++;
}

void GhostAction::draw()
{
	gl::pushModelView();
	float drawscalecorrection = 80.f;
	float drawposcorrection = -WorldScale*0.3f;
	gl::translate(enemyptr->getPos() + Vec3f(0, drawposcorrection, 0) + Vec3f(0, (WorldScale / 3.f)*sin(sinrotate), 0));
	gl::rotate(enemyptr->getRotate());
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/obake.png").enableAndBind();
	gl::draw(TextureM.getMesh("obake.obj"));
	TextureM.getTexture("Mesh/obake.png").disable();
	gl::popModelView();
}

void GhostAction::damaged()
{
	enemyptr->setSpeed(Vec3f(0, 0, 0));
}
