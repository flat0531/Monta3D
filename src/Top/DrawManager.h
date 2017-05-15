#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能
#include "cinder/imageIo.h"
#include "cinder/Surface.h"
class DrawManager{
public:
	static DrawManager& getDraw() {
		static DrawManager drawmanager;
		return  drawmanager;
	}
	//3D
	void drawStrokeCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const ci::ColorA color);
	void drawCube(const ci::Vec3f pos,const ci::Vec3f size,const ci::Vec3f rotate, const ci::ColorA color);
	void drawColorCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate);
	void drawTextureCube(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate,const ci::gl::Texture& texture,const ci::ColorA color,ci::Vec3f centerpos = ci::Vec3f(0,0,0));
	void drawSphere(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const float segment, const ci::ColorA color);
	void drawTextureSphere(const ci::Vec3f pos, const ci::Vec3f size, const ci::Vec3f rotate, const float segment, const ci::gl::Texture& texture, const ci::ColorA color);
	void drawTaurus(const ci::Vec3f pos, const float sizeout, const float sizein, const ci::Vec3f rotate, const ci::ColorA color, const float segmentout=12, const float segmentin=12 );
	//2D
	void drawBox(const ci::Vec2f pos,const ci::Vec2f size,const float angle, const ci::ColorA color);
	void drawBox(const ci::Vec2f pos, const  ci::Vec2f size, const float angle, const ci::ColorA color,float sort);
	void drawBoxEdge(const ci::Vec2f pos, const ci::Vec2f size, const ci::ColorA color = ci::ColorA::white());
	void drawTextureArea(const cinder::Vec2f pos, const ci::Vec2f scale, const ci::gl::Texture&tex, cinder::Area area, float size);
	void drawTextureBox(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::gl::Texture& tex, const ci::ColorA color = ci::ColorA::white());
	void drawTextureBox(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::gl::Texture& tex, const ci::ColorA color, const float sort);
	void drawTextureBoxEdge(const ci::Vec2f pos, const ci::Vec2f size, const ci::gl::Texture& tex, const ci::ColorA color = ci::ColorA::white());
	void drawTextureBoxEdge(const ci::Vec2f pos,const ci::Vec2f size, const ci::gl::Texture& tex, const ci::ColorA color, const float sort);
	void drawSurface(const ci::Vec2f pos, const ci::Vec2f size, const ci::Surface surface);
	void drawSurface(const ci::Vec2f pos, const ci::Vec2f size, const ci::Surface surface, const float sort);
	void drawCenterSurface(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::Surface surface);
	void drawCenterSurface(const ci::Vec2f pos, const ci::Vec2f size, const float angle, const ci::Surface surface,float sort);
	void drawFont(const std::string text,const ci::Vec2f pos, const ci::Vec2f size, const float angle,const ci::ColorA color,const ci::Font& font);
private:
	
};
#define DrawM (DrawManager::getDraw().getDraw())