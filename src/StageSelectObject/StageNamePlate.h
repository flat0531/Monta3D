#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"StageData.h"
class StageNamePlate {
public:
	StageNamePlate();
	StageNamePlate(const int worldnum,const int stagenum, const StageData _stagedata);
	void update();
	void draw();
	void SlideOut(const int worldnum, const int stagenum);
	void SlideIn(const int worldnum, const int stagenum,const StageData _stagedata);
	bool getIsSliding();
	bool getIsSlideIn();
private:
	struct ItemIcon {
		ci::Vec2f trancepos;
		ci::Vec2f size;
		bool isget;
	};
	ci::Vec2f pos;
	ci::Vec2f size;
	ci::Vec2f easingbeginpos;
	ci::Vec2f easingendpos;
	std::string thumbnailpath;
	std::vector<ItemIcon>itemicons;
	float slide_t;
	bool issliding;
	bool isslideout;
	bool isslidein;
	void updateSlideOut();
	void updateSlideIn();
	void drawItemIcon();
	float coloralpha;
	float begincoloralfa;
	float endcoloralfa;
	StageData stagedata;
	void setItemData();

};