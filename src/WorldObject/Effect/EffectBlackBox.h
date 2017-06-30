
#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectBlackBox : public EffectBase {
public:
	EffectBlackBox();
	EffectBlackBox(const float _easingtime, const float _deleytime);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	float easingtime[2];
	float deleytime;
	float t[3];
	ci::Vec2f upboxsize;
	ci::Vec2f downboxsize;
	ci::Vec2f beginupboxsize[3];
	ci::Vec2f begindownboxsize[3];
	ci::Vec2f endupboxsize[3];
	ci::Vec2f enddownboxsize[3];
	void setSize();
};