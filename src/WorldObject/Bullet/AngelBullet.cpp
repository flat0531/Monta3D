#include "AngelBullet.h"
#include"../../Top/Top.h"
#include"../../Top/DrawManager.h"
#include"../../Top/EasingManager.h"
#include"../../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
AngelBullet::AngelBullet()
{
}

AngelBullet::AngelBullet(ci::Vec3f _pos, ci::Vec3f _scale, float _y_rotate, float _z_rotate, ci::Vec3f _speed, int _deletetime, std::string _texturepath)
{
	pos = _pos;
	scale = _scale;
	speed = _speed;
	rotate = Vec3f(0, 0, 0);
	atackpoint = 5;
	hp = 30;
	deletetime = _deletetime;
	y_rotate = _y_rotate;
	z_rotate = _z_rotate;
	texturepath = _texturepath;
	uniquecolor = ColorA(255.f / 255.f, 153.f / 255.f, 237.f / 255.f, 1);
}



void AngelBullet::update()
{
	timecount++;
	pos += speed;
}

void AngelBullet::draw()
{
	float scale_rate = 25;
	gl::pushModelView();
	gl::translate(pos);
	gl::rotate(Vec3f(0, y_rotate, 0));
	gl::rotate(Vec3f(0, 0,  90+z_rotate*(180.f / M_PI)));


	gl::scale(scale/scale_rate);
	
	TextureM.getTexture("Mesh/" + texturepath + ".png").enableAndBind();
	gl::draw(TextureM.getMesh(texturepath + ".obj"));
	TextureM.getTexture("Mesh/" + texturepath + ".png").disable();
	gl::popModelView();

}

bool AngelBullet::deleteThis()
{
	return timecount >deletetime || compulsiondelete;
}
