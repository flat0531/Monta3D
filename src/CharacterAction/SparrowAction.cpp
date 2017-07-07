#include "SparrowAction.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldObject/Bullet/NormalEnemyBullet.h"
#include"../Top/TextureManager.h"
#include"../Input/KeyManager.h"
using namespace ci;
using namespace ci::app;
SparrowAction::SparrowAction()
{
}

SparrowAction::SparrowAction(CharacterBase * _enemy)
{
	enemyptr = dynamic_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 10;
	enemyptr->setQuat(Quatf(0, M_PI / 2.f, 0));
	enemyptr->setMaxHp(maxhp);
	enemyptr->setHp(maxhp);
	enemyptr->setColor(ColorA(1, 1, 1, 1));
	enemyptr->setDefalutColor(ColorA(1, 1, 1, 1));
	enemyptr->setUniqueColor(ColorA(153.f / 256.f, 86.f / 256.f, 51.f / 256.f, 1));
	wingangle = 0.0f;
	enemyptr->setName("sparrow");
	TextureM.CreateMesh("sparrow.obj");
	TextureM.CreateTexture("Mesh/sparrow.png");
	TextureM.CreateMesh("sparrowlw.obj");
	TextureM.CreateTexture("Mesh/sparrowlw.png");
	TextureM.CreateMesh("sparrowrw.obj");
	TextureM.CreateTexture("Mesh/sparrowrw.png");
}

void SparrowAction::update()
{
	wingangle += 0.15f;
	float speed = 7.0f;
	enemyptr->setSpeed(enemyptr->getQuat()*Vec3f::zAxis()*speed);
}

void SparrowAction::draw()
{
	gl::pushModelView();
	float drawscalecorrection = 24.f;
	float drawposcorrection = -enemyptr->getScale().y / 2.f;
	gl::translate(enemyptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(enemyptr->getQuat());
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/sparrow.png").enableAndBind();
	gl::draw(TextureM.getMesh("sparrow.obj"));           

	TextureM.getTexture("Mesh/sparrow.png").disable();
	gl::popModelView();

	Vec3f drawleftwingposcorrection = Vec3f(0, 0.7, 0.2)*20.f;
	gl::pushModelView();
	gl::translate(enemyptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(enemyptr->getQuat());
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::translate(drawleftwingposcorrection);
	gl::rotate(Vec3f(180,0,90+15*sin(wingangle)));
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/sparrowlw.png").enableAndBind();
	gl::draw(TextureM.getMesh("sparrowlw.obj"));           
	TextureM.getTexture("Mesh/sparrowlw.png").disable();
	gl::popModelView();

	Vec3f drawrightwingposcorrection = Vec3f(0, 0.7, 0)*20.f;
	gl::pushModelView();
	gl::translate(enemyptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(enemyptr->getQuat());
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::translate(drawrightwingposcorrection);
	gl::rotate(Vec3f(180, 0, -90 - 15 * sin(wingangle)));
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/sparrowrw.png").enableAndBind();
	gl::draw(TextureM.getMesh("sparrowrw.obj"));           
	TextureM.getTexture("Mesh/sparrowrw.png").disable();
	gl::popModelView();


}

void SparrowAction::damaged()
{
	enemyptr->setSpeed(Vec3f(0, 0, 0));
}

void SparrowAction::onLeftWall()
{
	enemyptr->setQuat(Quatf(0, -M_PI / 2.f, 0));
}

void SparrowAction::onRightWall()
{
	enemyptr->setQuat(Quatf(0, M_PI / 2.f, 0));
}

