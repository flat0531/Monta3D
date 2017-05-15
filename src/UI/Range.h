#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

class Range {
public:
	Range();
	Range(ci::Vec2f _centerpos, float _length, ci::Vec2f _iconsize,
		std::string _rangetexturepath,std::string _icontexturepath, 
		float _minvalue, float _maxvalue, float _rangevalue);
	void update();
	void draw();
	float getIconValue();
	void setIsTouch(bool _istouch);
	ci::Vec2f getIconLeftUpPos();
	ci::Vec2f getIconSize();
	void setRangeValue(const float _rangevalue);
	void AddRangevalue(const float addvalue);
private:
	float getRangeValue();
	ci::Vec2f centerpos;
	ci::Vec2f startpos;
	ci::Vec2f endpos;
	ci::Vec2f rangepos;
	ci::Vec2f lookpos;
	ci::Vec2f iconpos;
	ci::Vec2f iconsize;
	std::string rangetexturepath;
	std::string icontexturepath;
	float minvalue;
	float maxvalue;
	float rangevalue;
	float length;
	bool istouch;
};