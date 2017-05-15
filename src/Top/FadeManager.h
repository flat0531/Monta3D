#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"      // テクスチャ機能
#include "cinder/imageIo.h"
#include"cinder\Camera.h"
#include"SurfaceEffect.h"
#include<vector>
enum FadeInStep {
	FADEIN_SCALEUP,FADEIN_SURFACE,FADEIN_MAX
};
class FadeManager {
public:
	static FadeManager& getFade() {
		static FadeManager fademanager;
		return  fademanager;
	}
	void draw();
	void update();
	void StartFadeIn();
	void StartFadeOut(const bool isplayse);
	bool getIsFading();
	void setup();
	bool getIsfadeinEnd();
	bool getIsfadeoutEnd();
	bool getIsfadeIn();
private:
	ci::CameraOrtho ortho;
	void updateFadeIn();
	void updateFadeOut();
	bool isfading = false;
	bool isfadein = false;
	bool isfadeout = false;
	bool isfadeinend = false;
	bool isfadeoutend = false;
	bool isfadeoutsound;
	std::vector<ci::Vec2f>texturepos;
	ci::Vec2f maxtexturescale;
	ci::Vec2f texturescale;
	bool randomrgb[3];//テクスチャのrgbをランダムで決めます
	float texturerotate;
	std::vector<float>t;
	std::vector<float>easingtime;
	int easingtype = 0;
	SurfaceEffect surface;
};
#define FadeM (FadeManager::getFade().getFade())