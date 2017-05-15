#pragma once
#include"CubeBase.h"
class CubeObject;
class BreakCube: public CubeBase {
public:
	BreakCube(CubeObject* ptr);
	void draw()override;
};