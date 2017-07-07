#pragma once
#include"EffectBase.h"
#include"cinder\gl/Texture.h"
#include"../../Top/EasingManager.h"
#include<vector>
class EffectFlashBack : public EffectBase {
public:
	EffectFlashBack();
	EffectFlashBack(const float _time,const ci::ColorA _color);
	void update() override;
	void draw(const ci::CameraPersp camera) override;
	bool deleteThis()override;
private:
	float t;
	float time;
	ci::ColorA color;
};
