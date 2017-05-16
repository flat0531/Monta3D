#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\gl\Texture.h"
#include<vector>
class Information{
public:
	Information();
	void update();
	void draw();
	bool getIsGoalEnd();
	bool getIsStartEnd();
	void setIsGoal(const bool _is);
	void setIsStageStart(const bool _is);
	bool getIsEffecting();
private:
	struct BlackBox {
		ci::Vec2f pos;
		ci::Vec2f beginsize;
		ci::Vec2f endsize;
		ci::Vec2f size;
	};
	std::vector<BlackBox>blackboxs;
	ci::gl::Texture stagenametex;
	ci::Vec2f coloredstagenamepos;
	ci::Vec2f blackstagenamepos;
	float name_alfa;
	bool isstagestartend;
	bool isgoalend;
	bool isgoal;
	bool isstagestart;
	bool fonteasing_in;
	int worldnum;
	int stagenum;
	float blackbox_t;
	float blackbox_delay_t;
	float blackbox_return_t;
	float begin_name_t;
	float delay_name_t;
	float end_name_t;
	void endInit();
	void updateStageStart();
	void updateBlackBoxIn();
	void updateBlackBoxDelay();
	void updateBlackBoxreturn();
	void drawStageStart();
	void CreateBlackBox();
	void drawStageName();
	void updateStageName();
	void updateNameBegin();
	void updateNameDelay();
	void updateNameEnd();
};