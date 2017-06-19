#include "ItemObject.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
using namespace ci;
using namespace ci::app;
ItemObject::ItemObject()
{
}

ItemObject::ItemObject(const ci::Vec3f _pos, const ci::Vec3f _scale, const int _number, const std::string _itemtype, const std::string _name)
{
	pos = _pos;
	rotate = Vec3f(0, 0, 0);
	scale = _scale;
	number = _number;
	itemtype = _itemtype;
	name = _name;
	isget = false;
	tex = TextureM.CreateTexture("Mesh/paretto.png");
	TextureM.CreateMesh("paretto.obj");
}


void ItemObject::update()
{
	if (isget)return;
	rotate.y += 5.0f;
}

void ItemObject::draw()
{
	if (isget)return;
	float scalerate = 1.0f / 60.f;
	gl::pushModelView();
	gl::translate(pos-Vec3f(0,scale.y/2.f,0));
	gl::rotate(rotate);
	gl::scale(scale*scalerate);
	gl::color(ColorA(1, 1, 1, 1));
	TextureM.getTexture("Mesh/paretto.png").enableAndBind();
	gl::draw(TextureM.getMesh("paretto.obj"));
	TextureM.getTexture("Mesh/paretto.png").disable();
	gl::popModelView();
}
ci::Vec3f ItemObject::getPos()
{
	return pos;
}

ci::Vec3f ItemObject::getScale()
{
	return scale;
}

int ItemObject::getNumber()
{
	return number;
}

std::string ItemObject::getItemType()
{
	return itemtype;
}

bool ItemObject::getIsGet()
{
	return isget;
}

void ItemObject::setIsGet(const bool is)
{
	isget = is;
}
