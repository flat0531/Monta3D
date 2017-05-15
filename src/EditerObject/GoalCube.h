#pragma once
#include"CubeBase.h"
class CubeObject;
class GoalCube : public CubeBase {
public:
	GoalCube(CubeObject* ptr);
	void draw()override;
};