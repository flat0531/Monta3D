#pragma once
#include"MapChipBase.h"
class MapChipNone : public MapChipBase {
public:
	MapChipNone(ci::Vec3f _pos, ci::Vec3f _scale);
	void draw();
	void update();
private:

};