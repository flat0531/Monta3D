#pragma once
#include"CubeBase.h"
class CubeObject;
class NormalNotDrawCube : public CubeBase {
public:
	NormalNotDrawCube(CubeObject* ptr);
	void draw()override;
};