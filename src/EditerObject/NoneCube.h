#pragma once
#include"CubeBase.h"
class CubeObject;
class NoneCube : public CubeBase{
public:
	NoneCube(CubeObject* ptr);
	void draw()override;
};