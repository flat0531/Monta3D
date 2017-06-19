#include "CatBullet.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../CharacterAction/CatAction.h"
#include"../../WorldObject/Player.h"
using namespace ci;
using namespace ci::app;
CatBullet::CatBullet()
{
}

CatBullet::CatBullet(ci::Vec3f _pos, ci::Vec3f _scale, float _angle, ci::Vec3f _rotate, ci::ColorA _color, Player * _playerptr)
{
	pos = _pos;
	scale = _scale;
	angle = _angle;
	rotate = _rotate;
	uniquecolor = ColorA(1, 1, 1, 1);
	bullettype = BulletType::PLAYER_BULLET;
	color = _color;
	playerptr = _playerptr;
	hp = 100;
	atackpoint = 6;
	ismapcollision_endddelet = false;
}



void CatBullet::setup()
{
}

void CatBullet::update()
{
	//console() << pos << std::endl;
	timecount++;
	ci::Vec3f speed = ci::Quatf(ci::toRadians(playerptr->getRotate().x),
		ci::toRadians(playerptr->getRotate().y),
		ci::toRadians(playerptr->getRotate().z))*ci::Vec3f::xAxis();
	Vec3f crossvec = speed.cross(Vec3f::yAxis());

	pos = playerptr->getPos() + Quatf(crossvec, angle) *  speed *WorldScale*1.4f;
	rotate = playerptr->getRotate();
	angle += 0.2f;
	//pos = parent->getDrawPos();
}

void CatBullet::draw()
{
	DrawM.drawSphere(pos,scale*Vec3f(0.6,0.6,0.1f),rotate,12,color);
	//DrawM.drawCube(pos,scale,rotate,color);
}

bool CatBullet::deleteThis()
{
	return timecount > 40||compulsiondelete;
}
