#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class VerticalLine {
	
public:
	VerticalLine();
	VerticalLine(const ci::Vec2f &start_Position, const ci::Vec2f &end_Position);



	//	線の描画をします。
	void draw();

	//	線分との当たり判定をした際の、交点を返します。
	bool is_Hit_Position(ci::Vec3f *position, ci::Vec3f *speed, const double size);

private:
	ci::Vec2f start_Position_;
	ci::Vec2f end_Position_;
	ci::Vec2f normal_vector_;
	ci::Vec3f centerpos;
	ci::Vec3f scale;
	ci::Vec3f rotate;
	float angle;
};