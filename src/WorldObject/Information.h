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
	bool getGoalEffectEnd();
	void updateClearTexture();
	void drawClearTexture();
private:
	struct BlackBox {
		ci::Vec2f pos;
		ci::Vec2f beginsize;
		ci::Vec2f endsize;
		ci::Vec2f size;
	};
	struct ClearTexture {
		ci::Vec2f pos;
		ci::Vec2f size;
		ci::Vec2f beginpos;
		ci::Vec2f endpos;
		ci::Vec2f beginsize;
		ci::Vec2f endsize;
		ci::ColorA color;
		float angle;
		float size_t_;
		float angle_t_;
		float delay_t_;
		ci::gl::Texture tex;
	};
	std::vector<BlackBox>blackboxs;
	std::vector<ClearTexture>cleartextures;
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
	float goaleasingtime_t = 0.0f;
	void endInit();
	void updateStageStart();
	void updateBlackBoxIn();
	void updateBlackBoxDelay();
	void updateBlackBoxreturn();
	void CreateClearTextures();
	void CreateClearTexture(ci::Vec2f pos,ci::Vec2f size,ci::Vec2f beginpos,ci::Vec2f endpos,ci::Vec2f beginsize,ci::Vec2f endsize,const ci::gl::Texture tex);
	void drawStageStart();
	void CreateBlackBox();
	void drawStageName();
	void updateStageName();
	void updateNameBegin();
	void updateNameDelay();
	void updateNameEnd();

	void updateTranceClearTexture();
	void updateRotateClearTexture();
	void updateDelayClearTexture();
	
};