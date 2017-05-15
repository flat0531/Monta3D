#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class CubeObject;
class CubeBase {
public:
	CubeBase();
	virtual void draw() {};
protected:
	CubeObject* cubeobjectptr;
};