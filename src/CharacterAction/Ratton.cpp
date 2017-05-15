#include "Ratton.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldObject/Bullet/NormalEnemyBullet.h"
#include"../Top/TextureManager.h"
#include"cinder\ObjLoader.h"
//#include"../WorldObject/Bullet/MyToras.h"
using namespace ci;
using namespace ci::app;
RattonAction::RattonAction()
{
}

RattonAction::RattonAction(CharacterBase * _enemy)
{
	enemyptr = reinterpret_cast<Enemy*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 10;
	enemyptr->setQuat(Quatf(0,M_PI/2.f,0));
	enemyptr->setMaxHp(maxhp);
	enemyptr->setHp(maxhp);
	enemyptr->setDefalutColor(ColorA(1,1,1,1));
	enemyptr->setName("ratton");
	enemyptr->setUniqueColor(ColorA(102.f / 256.f, 102.f / 256.f, 102.f / 256.f, 1));
	TextureM.CreateMesh("Rat.obj");
	TextureM.CreateTexture("Mesh/Rat.png");
}

void RattonAction::setup()
{
}

void RattonAction::update()
{
	float g = 0.012f*WorldScale;
	enemyptr->AddForth(Vec3f(0, -g, 0));
	ci::Vec3f playerpos = enemyptr->getCharacterManager()->getPlayer()->getPos();
	Vec3f d = playerpos - enemyptr->getPos();
	// 目標までの向きベクトルを正規化
	d.normalize();
	d.y = 0.0f;
	// 自分の向きベクトルと目標までの向きベクトルの外積
	// →クオータニオンの回転軸
	Vec3f cross = (enemyptr->getQuat()* Vec3f::zAxis()).cross(d);

	Quatf buf = enemyptr->getQuat()*Quatf(cross, 0.01f);
	Vec3f temp = buf*Vec3f::zAxis();
	if (cross.lengthSquared() > 0.0001f) {
		enemyptr->setQuat(Quatf(ci::Matrix44f::createRotation(Vec3f::zAxis(), temp, Vec3f::yAxis())));
	}
	else{
		if(IsCanAtack())
		attack();
	}
	atackcount++;
}

void RattonAction::draw()
{
	gl::pushModelView();
	float drawscalecorrection = 24.f;
	float drawposcorrection = -WorldScale*0.5f;
	gl::translate(enemyptr->getPos()+Vec3f(0,drawposcorrection,0));
	gl::rotate(enemyptr->getQuat());
	gl::scale(enemyptr->getScale()/ drawscalecorrection);
	gl::color(enemyptr->getColor());
	TextureM.getTexture("Mesh/Rat.png").enableAndBind();
	gl::draw(TextureM.getMesh("Rat.obj"));            // 緯度の分割数
	TextureM.getTexture("Mesh/Rat.png").disable();


	//gl::drawCube(ci::Vec3f(0, 0, 0), ci::Vec3f(1, 1, 1));
	gl::popModelView();
	//DrawM.drawCube(enemyptr->getPos(), enemyptr->getScale(),enemyptr->getRotate(),ColorA(1,1,1,1));
}

void RattonAction::jump()
{
}

void RattonAction::attack()
{
	ci::Vec3f speed = enemyptr->getQuat()*Vec3f::zAxis();

	enemyptr->getBulletManagerPointer()->CreateEnemyBullet(NormalEnemyBullet
		(enemyptr->getPos() + speed*WorldScale,
			ci::Vec3f(1, 1, 1)*WorldScale,
			speed*WorldScale*0.1f,
			enemyptr->getRotate() + Vec3f(0, 0, 0),enemyptr,5, 5, 60, ColorA(1, 1, 0, 1), 180));
	atackcount = 0;
}

bool RattonAction::IsCanAtack()
{
	return atackcount > 180;
}
