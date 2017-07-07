#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "../UI/ColorObject.h"
#include <vector>
//////カラーオブジェクトと束ねるもの
class Pallet {
public:
	Pallet();
	Pallet(ci::Vec2f _pos);
	void draw();
	void update();
	void addColorObject(ci::ColorA _color, bool _isnecessary, int _num);
	int getColorObjectNum();
	void setPos(ci::Vec2f _pos);
	int getSelectNum();
	ci::ColorA getSelectColor();
	void selectcolor();
	void selectColorPosition();
	void setup();
private:
	int selectnum;
	std::vector<ColorObject> colorobjects;
	ci::Vec2f palletpos;
	ci::Vec2f palletsize;
	
};