#include "TextureObj.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
TextureObj::TextureObj()
{
	
}

TextureObj::TextureObj(ci::Vec3f _pos, ci::Vec3f _scale, ci::Vec3f _rotate, std::string _path, bool _isalpha)
{
	pos = _pos;
	scale = _scale;
	rotate = _rotate;
	path = _path;
	isalpha = _isalpha;
	color = ci::ColorA(1, 1, 1, 1);
}

ci::Vec3f TextureObj::getPos()
{
	return pos;
}

ci::Vec3f TextureObj::getScale()
{
	return scale;
}

ci::Vec3f TextureObj::getRotate()
{
	return rotate;
}

std::string TextureObj::getPath()
{
	return path;
}

bool TextureObj::getIsAlpha()
{
	return isalpha;
}

void TextureObj::setIsAlpha(const bool is)
{
	isalpha = is;
}

void TextureObj::setPos(const ci::Vec3f _pos)
{
	pos = _pos;
}

void TextureObj::setPosX(const float _posx)
{
	pos.x = _posx;
}

void TextureObj::setPosY(const float _posy)
{
	pos.y = _posy;
}

void TextureObj::setPosZ(const float _posz)
{
	pos.z = _posz;
}

void TextureObj::setScale(const ci::Vec3f _scale)
{
	scale = _scale;
}

void TextureObj::setRotate(const ci::Vec3f _rotate)
{
	rotate = _rotate;
}

void TextureObj::setPath(const std::string _path)
{
	path = _path;
}

void TextureObj::setColor(const ci::ColorA _color)
{
	color = _color;
}

void TextureObj::draw()
{
	DrawM.drawTextureCube(pos,scale,rotate,TextureM.getTexture(path),color);
}
