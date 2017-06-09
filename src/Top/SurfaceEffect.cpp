#include"SurfaceEffect.h"
#include"TextureManager.h"
#include"EasingManager.h"
#include"CollisionManager.h"
#include"DrawManager.h"
#include"../Input/KeyManager.h"
using namespace ci;
using namespace ci::app;
SurfaceEffect::SurfaceEffect()
{

}
SurfaceEffect::SurfaceEffect(const ci::gl::Texture _texture,
	const ci::Vec2i _startpos, const ci::Vec2i _endpos,
	const ci::Vec3f _drawpos, const ci::Vec3f _drawsize, const ci::Vec3f _drawrotate,
	const EasingManager::EasType _pos_eaz, const EasingManager::EasType _length_eaz,
	const float _piceldrawsize, const float _slope,
	const float _angle, const float _anglespeed, const float _maxlength,
	const float _easingtime, const float _t,const ColorA _color)
{
	Vec2i texturesize = _texture.getSize();
	surface = Surface(texturesize.x, texturesize.y, true);
	for (int y = 0; y <texturesize.y; y++)
	{
		for (int x = 0; x < texturesize.x; x++)
		{
			surface.setPixel(Vec2i(x, y), ColorA(0, 0, 0, 0));
		}
	}

	texturesurface = Surface(_texture);
	estartpos = _startpos;
	endpos = _endpos;
	pos_eaz = _pos_eaz;
	length_eaz = _length_eaz;
	drawpos = _drawpos;
	drawsize = _drawsize;
	drawrotate = _drawrotate;
	slope = _slope;
	angle = _angle;
	anglespeed = _anglespeed;
	pixceldrawsize = _piceldrawsize;
	length = 0;
	maxlength = _maxlength;
	easingtime = _easingtime;
	t = _t;
	pixcelsize = surface.getSize();
	color = _color;
}


void SurfaceEffect::update()
{
	if (isEnd())return;
	if (t_up) {	
		EasingManager::tCount(t, easingtime);
	}
	else {
		EasingManager::tCount(t, -easingtime);
	}
	
	Vec2i pos;
	pos.x = EasingManager::getEas[pos_eaz](t, estartpos.x, endpos.x);
	pos.y = EasingManager::getEas[pos_eaz](t, estartpos.y, endpos.y);

	length = EasingReturn(t, 0, maxlength)*sinf(angle);
	angle += anglespeed;
	Vec2i movepos = pos + Vec2i(length*cosf(slope), length*sin(slope));
	for (int y = 0;y < 2 * pixceldrawsize;y++) {
		for (int x = 0;x < 2 * pixceldrawsize;x++) {
			Vec2f setpos = movepos - Vec2f(pixceldrawsize, pixceldrawsize) + Vec2f(x, y);
			if (setpos.x < 0)continue;
			if (setpos.y < 0)continue;
			if (setpos.x >= pixcelsize.x)continue;
			if (setpos.y >= pixcelsize.y)continue;
			if (CollisionM.isCirclePoint(setpos, movepos, pixceldrawsize)) {
				if (t_up) {
					surface.setPixel(setpos, texturesurface.getPixel(setpos));
				}
				else {
					surface.setPixel(setpos, ColorA(1, 1, 1, 0));
				}
				
			}
		}
	}
	
}

void SurfaceEffect::draw()
{
	gl::Texture tex = surface;
	DrawM.drawTextureCube(drawpos,drawsize,drawrotate,tex,color);
}

void SurfaceEffect::draw2D()
{
	gl::Texture tex = surface;
	DrawM.drawTextureBox(Vec2f(drawpos.x,drawpos.y), Vec2f(drawsize.x, drawsize.y),drawrotate.z, tex, color);
}

void SurfaceEffect::draw2D(const ci::Vec2f pos, const ci::Vec2f size)
{
	gl::Texture tex = surface;
	DrawM.drawTextureBox(pos, size, drawrotate.z, tex, color);
}

void SurfaceEffect::setDrawtPos(const ci::Vec3f _pos)
{
	drawpos = _pos;
}

void SurfaceEffect::setDrawSize(const ci::Vec3f _size)
{
	drawsize = _size;
}

void SurfaceEffect::setDrawRotate(const ci::Vec3f _rotate)
{
	drawrotate = _rotate;
}

void SurfaceEffect::Rotation(const ci::Vec3f _rotate)
{
	drawrotate += _rotate;
}

bool SurfaceEffect::isEnd()
{
	if (t_up) {
		return t >= 1.0f;
	}
	else
	{
		return t <= 0.0f;
	}
	
}

void SurfaceEffect::setIs(const bool _is_t_up)
{
	t_up = _is_t_up;
}

bool SurfaceEffect::getIsUp()
{
	return t_up;
}

void SurfaceEffect::ChangeTexture(const ci::gl::Texture _texture)
{
	Vec2i texturesize = _texture.getSize();
	surface = Surface(texturesize.x, texturesize.y, true);
	texturesurface = Surface(_texture);
	for (int y = 0; y <texturesize.y; y++)
	{
		for (int x = 0; x < texturesize.x; x++)
		{
			surface.setPixel(Vec2i(x, y), ColorA(0, 0, 0, 0));
		}
	}
}

void SurfaceEffect::ChangeColor(const ci::ColorA _color)
{
	color = _color;
}

const ci::gl::Texture SurfaceEffect::getTexture()
{
	return surface;
}







void SurfaceEffect::reverseUpdate()
{
}

SurfaceEffect::~SurfaceEffect()
{

}















