#include "MapChipApple.h"
#include"../../Top/TextureManager.h"
#include"../../Top/DrawManager.h"
#include"../../Top/SoundManager.h"
using namespace ci;
using namespace ci::app;
MapChipApple::MapChipApple(ci::Vec3f _pos, ci::Vec3f _scale)
{
	pos = _pos;
	scale = _scale;
	iscollision = true;
	TextureM.CreateTexture("Mesh/apple.png");
	TextureM.CreateMesh("apple.obj");
	SoundM.CreateSE("change.wav");

}

void MapChipApple::draw()
{
	if (!isactive)return;
	float scalerate = 0.018f;
	gl::pushModelView();
	gl::translate(pos);
	gl::scale(scale*scalerate);
	gl::rotate(Vec3f(0,rotate.y,0));
	gl::translate(ci::Vec3f(0, - 1.f/scalerate/2.f, 0));
	gl::rotate(Vec3f(rotate.x,0,0));
	gl::color(ColorA(1, 1, 1, 1));
	TextureM.getTexture("Mesh/apple.png").enableAndBind();
	gl::draw(TextureM.getMesh("apple.obj"));
	TextureM.getTexture("Mesh/apple.png").disable();
	gl::popModelView();
}

void MapChipApple::update()
{
	if (!isactive)return;
	rotatesin_x += 0.02f;
	if (rotatesin_x >= 2.f*M_PI) {
		rotatesin_x -= 2.f*M_PI;
	}
	rotate.x= 10.0f*sin(rotatesin_x);
	rotate.y += 1.5f;
	if (rotate.y >= 360.f) {
		rotate.y -= 360.f;
	}
}

void MapChipApple::InCollisionEnter(CharacterBase * characterbase)
{
	if (!(characterbase->getCharacterType() == CharacterType::CHARACTER_PLAYER))return;
	if (isactive) {
		characterbase->addHpValue(30);
		SoundM.PlaySE("change.wav");
		isactive = false;
	}
}
