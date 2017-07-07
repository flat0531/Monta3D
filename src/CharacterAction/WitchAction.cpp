#include "WitchAction.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldObject/Bullet/ScaleUpBullet.h"
#include"../WorldObject/Bullet/MyToras.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
WitchAction::WitchAction()
{
}

WitchAction::WitchAction(CharacterBase * _enemy)
{
	enemyptr = dynamic_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 6;
	enemyptr->setMaxHp(maxhp);
	enemyptr->setScale(Vec3f(1.5,1.5,1.5)*WorldScale);
	enemyptr->setQuat(Quatf(0, M_PI, 0));
	enemyptr->setHp(maxhp);
	enemyptr->setColor(ColorA(1, 1, 1, 1));
	atackdelay = 60;
	actioncount = atackdelay;
	enemyptr->setDefalutColor(ColorA(1,1,1,1));
	atackstart = false;
	enemyptr->setName("witch");
	enemyptr->setUniqueColor(ColorA(84.f / 256.f, 51.f / 256.f, 153.f / 256.f, 1));
	TextureM.CreateMesh("witch.obj");
	TextureM.CreateTexture("Mesh/witch.png");

	TextureM.CreateMesh("houki.obj");
	TextureM.CreateTexture("Mesh/houki.png");

	houkirotate = 30.f;
	houkirotatespeed = 0.0f;
    drawscalecorrection = 32.f;
	houkirotate_t = 0.0f;
	controlcount = 0;
}


void WitchAction::update()
{
	float g = 0.012f*WorldScale;
	enemyptr->AddForth(Vec3f(0, -g, 0));
	ci::Vec3f playerpos = enemyptr->getCharacterManager()->getPlayer()->getPos();
	Vec3f d = playerpos - enemyptr->getPos();
	d.normalize();
	d.y = 0.0f;

	Vec3f cross = (enemyptr->getQuat()* Vec3f::zAxis()).cross(d);
	float rotatespeed = 0.06f;
	Quatf buf = enemyptr->getQuat()*Quatf(cross, rotatespeed);
	Vec3f temp = buf*Vec3f::zAxis();
	if (cross.lengthSquared() > 0.0005f&&isDlay()) {
		enemyptr->setQuat(Quatf(ci::Matrix44f::createRotation(Vec3f::zAxis(), temp, Vec3f::yAxis())));
		if(cross.lengthSquared() < 0.002f)
		controlcount++;
	}
	else {
		if (isCanAtack()) {
			attack();
			controlcount = 0;
		}
	}
	if (isCanAtack() || (controlcount >= 2)) {
		attack();
		controlcount = 0;
	}
	if (isDlay()) {
		atackstart = false;
	}
	if (atackstart) {
		EasingManager::tCount(houkirotate_t, 0.5f);
		houkirotatespeed = EasingCircIn(houkirotate_t, 0,25);
	}
	else
	{
		houkirotate_t = 0.0f;
		houkirotatespeed = (houkirotatespeed / 1.5f);
	}
	houkirotate += houkirotatespeed;
	actioncount++;
}

void WitchAction::draw()
{
	
	Vec3f drawposcorrection = Vec3f(0, -enemyptr->getScale().y/2.f, 0);
	gl::pushModelView();
	gl::translate(enemyptr->getPos() + drawposcorrection);
	gl::rotate(enemyptr->getQuat());
	gl::scale(enemyptr->getScale()/drawscalecorrection);
	gl::color(enemyptr->getColor());

	TextureM.getTexture("Mesh/witch.png").enableAndBind();
	gl::draw(TextureM.getMesh("witch.obj"));           
	TextureM.getTexture("Mesh/witch.png").disable();

	gl::popModelView();

	Vec3f drawhoukiposcorrection = Vec3f(0.5, 1, 0)*20.f;
	gl::pushModelView();
	gl::translate(enemyptr->getPos() + drawposcorrection);
	gl::rotate(enemyptr->getQuat());
	gl::rotate(Vec3f(0,-90,0));
	gl::scale(enemyptr->getScale() / drawscalecorrection);
	gl::translate(drawhoukiposcorrection);
	gl::rotate(Vec3f(houkirotate,0,0));
	gl::translate(Vec3f(0,-drawhoukiposcorrection.y/1.5f,0));
	gl::color(enemyptr->getColor());

	TextureM.getTexture("Mesh/houki.png").enableAndBind();
	gl::draw(TextureM.getMesh("houki.obj"));           
	TextureM.getTexture("Mesh/houki.png").disable();

	gl::popModelView();

}

void WitchAction::jump()
{
}

void WitchAction::attack()
{
	ci::Vec3f playerpos = enemyptr->getCharacterManager()->getPlayer()->getPos();
	ci::Vec3f trancepos = ((enemyptr->getQuat()*Vec3f::zAxis())*enemyptr->getScale().x / 2.f)+Vec3f(0,enemyptr->getScale().y/4.f,0);
	Vec3f d = playerpos - (enemyptr->getPos() + trancepos);
	d.normalize();

	Vec3f cross = enemyptr->getPos().cross(d);
	
	enemyptr->setBulletQuat(Quatf(ci::Matrix44f::createRotation(Vec3f::zAxis(), d, Vec3f::yAxis())));

	ci::Vec3f speed = enemyptr->getBulletQuat()*Vec3f::zAxis();
	
	enemyptr->getBulletManagerPointer()->CreateEnemyBullet(ScaleUpBullet
		(enemyptr->getPos()+ trancepos,
			ci::Vec3f(0, 0, 0)*WorldScale, ci::Vec3f(1.1, 1.1, 1.1)*WorldScale,
			speed*WorldScale*0.15f,
			enemyptr->getRotate() + Vec3f(0, 0, 0),enemyptr,15,8,atackdelay,ColorA(1,0,0),180));
	actioncount = 0;
	atackstart = true;
}

bool WitchAction::isCanAtack()
{
	return 	actioncount > 180;
}

bool WitchAction::isDlay()
{
	return actioncount > (atackdelay*2);
}
