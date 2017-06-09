#include "PumpmanAction.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldObject/Bullet/NormalEnemyBullet.h"
#include"../Top/TextureManager.h"
#include"../Top/DataManager.h"
using namespace ci;
using namespace ci::app;
PumpmanAction::PumpmanAction()
{
}

PumpmanAction::PumpmanAction(CharacterBase * _enemy)
{
	enemyptr = dynamic_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 12;
	enemyptr->setRotate(Vec3f(0, M_PI / 2.f, 0));
	enemyptr->setScale(Vec3f(1,1,1)*WorldScale);
	enemyptr->setMaxHp(maxhp);
	enemyptr->setHp(maxhp);
	enemyptr->setDefalutColor(ColorA(1, 1, 1, 1));
	enemyptr->setName("pumpman");
	enemyptr->setUniqueColor(DataM.getColor("orange"));
	TextureM.CreateMesh("pumpman.obj");
	TextureM.CreateTexture("Mesh/pumpman.png");
}

void PumpmanAction::update()
{
	float g = 0.008f*WorldScale;
	enemyptr->AddForth(Vec3f(0, -g, 0));

	enemyptr->rotation(Vec3f(0,6.f,0));


	sinrotate += 0.075f;

	if (sinrotate >= 2.f*M_PI)sinrotate -= 2.f*M_PI;

	//enemyptr->setRotateY((90.f*direction) + 25.f*sin(sinrotate));
	enemyptr->setSpeedX(direction*WorldScale*0.1f);
	updatecount++;
}

void PumpmanAction::draw()
{
	gl::pushModelView();
	float drawscalecorrection = 40.f;
	float drawposcorrection = -WorldScale*0.3f;
	gl::translate(enemyptr->getPos()-Vec3f(0,enemyptr->getScale().y/2.f,0));
	gl::rotate(enemyptr->getRotate());
	gl::scale(Vec3f(enemyptr->getScale().x, enemyptr->getScale().y*1.2f, enemyptr->getScale().z) / drawscalecorrection);
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/pumpman.png").enableAndBind();
	gl::draw(TextureM.getMesh("pumpman.obj"));
	TextureM.getTexture("Mesh/pumpman.png").disable();
	gl::popModelView();
}

void PumpmanAction::damaged()
{

}

void PumpmanAction::onLeftWall()
{
	direction = -1;
}

void PumpmanAction::onRightWall()
{
	direction = 1;
}
