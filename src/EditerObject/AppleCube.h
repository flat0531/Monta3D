#pragma once
#include"CubeBase.h"
class CubeObject;
class AppleCube : public CubeBase {
public:
	AppleCube(CubeObject* ptr);
	void draw()override;
};