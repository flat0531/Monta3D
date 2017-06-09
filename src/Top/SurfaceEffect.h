#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能
#include "cinder/imageIo.h"
#include "cinder/Surface.h"
#include "EasingManager.h"
class SurfaceEffect{
public:
	SurfaceEffect();
	~SurfaceEffect();
	SurfaceEffect(const ci::gl::Texture _texture,
		const ci::Vec2i _startpos, const ci::Vec2i _endpos,
		const ci::Vec3f _drawpos, const ci::Vec3f _drawsize,const ci::Vec3f _drawrotate,
		const EasingManager::EasType _pos_eaz, const EasingManager::EasType _length_eaz,
		const float _piceldrawsize, const float _slope,
		const float _angle, const float _anglespeed,const float _maxlength,
		const float _easingtime, const float _t = 0.0f,const ci::ColorA color = ci::ColorA(1,1,1,1));
	void update();
	void draw();
	void draw2D();
	void draw2D(const ci::Vec2f pos,const ci::Vec2f size);
	void setDrawtPos(const ci::Vec3f _pos);
	void setDrawSize(const ci::Vec3f _size);
	void setDrawRotate(const ci::Vec3f _rotate);
	void Rotation(const ci::Vec3f _rotate);
	bool isEnd();
	void setIs(const bool _is_t_up);
	bool getIsUp();
	void ChangeTexture(const ci::gl::Texture _texture);
	void ChangeColor(const ci::ColorA _color);
	const ci::gl::Texture getTexture();
private:
	ci::Surface surface;
	ci::Vec2i estartpos;
	ci::Vec2i endpos;
	ci::Surface texturesurface;
	EasingManager::EasType pos_eaz;
	EasingManager::EasType length_eaz;
	ci::ColorA color;
	float pixceldrawsize;
	float slope;
	float angle;
	float anglespeed;
	float maxlength;
	float length;
	float easingtime;
	float t;
	bool t_up = true;
	ci::Vec3f drawpos;
	ci::Vec3f drawsize;
	ci::Vec3f drawrotate;
	ci::Vec2i pixcelsize;
	void reverseUpdate();
};