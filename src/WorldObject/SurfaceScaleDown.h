#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\Surface.h"
//////�T�[�t�F�C�X�����k���ď����o��
class SurfaceScaleDown {
public:
	SurfaceScaleDown();
	void WirteImage(const ci::Surface& surface, const int downrate,const std::string pathname);
private:
	
};
