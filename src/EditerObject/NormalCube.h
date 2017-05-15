#pragma once
#include"CubeBase.h"
class CubeObject;
class NormalCube : public CubeBase {
public:
	NormalCube(CubeObject* ptr);
	void draw()override;
};