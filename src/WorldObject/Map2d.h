#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
enum Map2dUpdatetype {
	 Map2dTRANCERATE, Map2dROTATE, Map2dROTATE_RETURN, Map2dCIRCLE, Map2dNONE
};
class Map2d {
public:
	Map2d();
	Map2d(const ci::Vec3f _pos,
		const ci::Vec3f _scale,
		const ci::Vec3f _rotate,
		const ci::ColorA _color, const std::string _texturepath);
	void setuptrancerate(const ci::Vec3f _vec);
	void setupRotate(const ci::Vec3f _rotatespeed);
	void setupRotateReturn(const ci::Vec3f _centerpos,const float _maxangle,const float _return_speed,const float startrotate);
	void setupCircle(const ci::Vec2f _size,const float _circlespeed);

	void updatetrancerate();
	void updateRotate();
	void updateRotateReturn();
	void updateCircle();



	void update();
	void draw();
private:
	ci::Vec3f pos;
	ci::Vec3f startpos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	ci::Vec3f startrotate;
	ci::ColorA color;
	std::string texturepath;
	const ci::gl::Texture& tex;

	ci::Vec3f vec=ci::Vec3f(0,0,0);
	ci::Vec3f rotatespeed;
	ci::Vec3f centerpos;
	float maxangle;
	float return_angle = 0.0f;
	float return_speed;
	ci::Vec2f circlesize;
	float circle_angle = 0.0f;
	float circle_speed;
	bool isupdate[Map2dUpdatetype::Map2dNONE];
};