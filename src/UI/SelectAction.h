#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder/gl/Texture.h"
#include"ActionIcon.h"
#include"PlayTextureList.h"
#include<vector>
class SelectAction {
public:
	SelectAction();
	void update();
	void draw();
	std::string getActionName();
	int getPlayTextureNum();
private:
	std::vector<ActionIcon>actionaicons;
	PlayTextureList playtexturelist;
	void CreateActionICons();
	void ChoiceAction();
	int selectnum;
	ci::Vec2f cursorpos;
	ci::Vec2f cursorbeginpos;
	ci::Vec2f cursorendpos;
	ci::Vec2f iconsize;
	ci::gl::Texture push_a_tex;
	ci::gl::Texture push_d_tex;
	float leftedge = 0.0f;
	float cursorsinangle = 0.0f;
	float cursor_t = 1.0f;
};