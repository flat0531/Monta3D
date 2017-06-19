#pragma once
#include"CubeBase.h"
class CubeObject;
class ColoredCube : public CubeBase {
public:
	ColoredCube(CubeObject* ptr);
	void draw()override;
};