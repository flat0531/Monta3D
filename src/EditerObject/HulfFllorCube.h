#pragma once
#include"CubeBase.h"
class CubeObject;
class HulfFllorCube : public CubeBase {
public:
	HulfFllorCube(CubeObject* ptr);
	void draw()override;
};