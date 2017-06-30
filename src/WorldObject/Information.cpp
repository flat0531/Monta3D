#include "Information.h"
#include"../Top/DataManager.h"
#include"../Top/EasingManager.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/Top.h"
using namespace ci;
using namespace ci::app;
Information::Information()
{
	worldnum = DataM.getWorldNum();
	stagenum = DataM.getStageNum();

	isstagestartend =false;
	isstagestart = false;
	isgoal = false;
	fonteasing_in = false;
	blackbox_t = 0.0f;
	blackbox_delay_t = 0.0f;
	blackbox_return_t = 0.0f;
	CreateBlackBox();
	CreateClearTextures();
	coloredstagenamepos = Vec2f(0,WINDOW_HEIGHT/2.f);
	blackstagenamepos = Vec2f(0, WINDOW_HEIGHT / 2.f);
	stagenametex = TextureM.CreateTexture("UI/stagename/stagename" + std::to_string(worldnum) + "_" + std::to_string(stagenum) + ".png");
}

void Information::update()
{
	endInit();
	updateStageStart();
}

void Information::draw()
{
	drawStageStart();
	drawStageName();
}

bool Information::getIsGoalEnd()
{
	return isgoalend;
}

bool Information::getIsStartEnd()
{
	return isstagestartend;
}

void Information::setIsGoal(const bool _is)
{
	isgoal = _is;
}

void Information::setIsStageStart(const bool _is)
{
	isstagestart = _is;
}

bool Information::getIsEffecting()
{
	return (isstagestart || isgoal);
}

bool Information::getGoalEffectEnd()
{
	return EasingManager::tCountEnd(goaleasingtime_t);
}

void Information::endInit()
{
	isgoalend = false;
	isstagestartend = false;
}

void Information::updateStageStart()
{
	if (!isstagestart)return;
	updateBlackBoxIn();
	updateBlackBoxDelay();
	updateBlackBoxreturn();
	
	updateStageName();
	
}

void Information::updateBlackBoxIn()
{
	if (EasingManager::tCountEnd(blackbox_t))return;

	EasingManager::tCount(blackbox_t, 0.75f);
	for (int i = 0;i < blackboxs.size();i++) {
		blackboxs[i].size.x = EasingCubicOut(blackbox_t, blackboxs[i].beginsize.x, blackboxs[i].endsize.x);
		blackboxs[i].size.y = EasingCubicOut(blackbox_t, blackboxs[i].beginsize.y, blackboxs[i].endsize.y);
	}
}

void Information::updateBlackBoxDelay()
{
	if (EasingManager::tCountEnd(blackbox_delay_t))return;

	if (EasingManager::tCountEnd(blackbox_t)) {
		EasingManager::tCount(blackbox_delay_t, 3.0f);
	}
}

void Information::updateBlackBoxreturn()
{
	if (EasingManager::tCountEnd(blackbox_return_t))return;

	if (EasingManager::tCountEnd(blackbox_delay_t)) {
		EasingManager::tCount(blackbox_return_t, 0.75f);
		for (int i = 0;i < blackboxs.size();i++) {
			blackboxs[i].size.x = EasingCubicIn(blackbox_return_t, blackboxs[i].endsize.x, blackboxs[i].beginsize.x);
			blackboxs[i].size.y = EasingCubicIn(blackbox_return_t, blackboxs[i].endsize.y, blackboxs[i].beginsize.y);
		}
		if (EasingManager::tCountEnd(blackbox_return_t)) {
			isstagestartend = true;
			isstagestart = false;
		}
	}

}

void Information::CreateClearTextures()
{
	Vec2f beginpos = Vec2f(WINDOW_WIDTH / 2.f, WINDOW_HEIGHT / 2.f);
	Vec2f beginsize = Vec2f(100, 100);
	float endposy = WINDOW_HEIGHT / 2.f - 150.f;
	Vec2f endsize = Vec2f(200,200);
	CreateClearTexture(beginpos, beginsize, beginpos, Vec2f(WINDOW_WIDTH / 2.f - 200, endposy), beginsize, endsize, TextureM.CreateTexture("UI/Clear/clear_c.png"));
	CreateClearTexture(beginpos, beginsize, beginpos, Vec2f(WINDOW_WIDTH / 2.f - 100, endposy), beginsize, endsize, TextureM.CreateTexture("UI/Clear/clear_l.png"));
	CreateClearTexture(beginpos, beginsize, beginpos, Vec2f(WINDOW_WIDTH / 2.f, endposy+25.f), beginsize, endsize, TextureM.CreateTexture("UI/Clear/clear_e.png"));
	CreateClearTexture(beginpos, beginsize, beginpos, Vec2f(WINDOW_WIDTH / 2.f+100, endposy + 25.f), beginsize, endsize, TextureM.CreateTexture("UI/Clear/clear_a.png"));
	CreateClearTexture(beginpos, beginsize, beginpos, Vec2f(WINDOW_WIDTH / 2.f +200, endposy + 25.f), beginsize, endsize, TextureM.CreateTexture("UI/Clear/clear_r.png"));
}

void Information::CreateClearTexture(ci::Vec2f pos, ci::Vec2f size, ci::Vec2f beginpos, ci::Vec2f endpos, ci::Vec2f beginsize, ci::Vec2f endsize, ci::gl::Texture tex)
{
	ClearTexture buff;
	buff.pos = pos;
	buff.size = size;
	buff.beginpos = beginpos;
	buff.endpos = endpos;
	buff.beginsize = beginsize;
	buff.endsize = endsize;
	buff.tex = tex;
	buff.size_t_ = 0.0f;
	buff.angle_t_ = 0.0f;
	buff.angle = 0.0f;
	buff.color = ColorA(1, 1, 1, 1);
	buff.delay_t_ = 0.0f;
	cleartextures.push_back(buff);
}

void Information::drawStageStart()
{
	for (int i = 0;i < blackboxs.size();i++) {
		DrawM.drawBoxEdge(blackboxs[i].pos, blackboxs[i].size, ColorA(0, 0, 0, 1));
	}
}

void Information::CreateBlackBox()
{
	BlackBox up;
	up.pos = Vec2f(0, 0);
	up.beginsize = Vec2f(WINDOW_WIDTH, 0);
	up.endsize = Vec2f(WINDOW_WIDTH, 150);
	up.size = up.beginsize;
	blackboxs.push_back(up);
	BlackBox down;
	down.pos = Vec2f(0, WINDOW_HEIGHT);
	down.beginsize = Vec2f(WINDOW_WIDTH, 0);
	down.endsize = Vec2f(WINDOW_WIDTH, -235);
	down.size = down.beginsize;
	blackboxs.push_back(down);
}

void Information::drawStageName()
{
	if (!EasingManager::tCountEnd(blackbox_t))return;
	Vec2f size=Vec2f(1000,250);
	DrawM.drawTextureBox(blackstagenamepos+Vec2f(3,-3), size, 0.0f, stagenametex, ColorA(0, 0, 0, name_alfa));
	DrawM.drawTextureBox(coloredstagenamepos, size, 0.0f, stagenametex, ColorA(1, 1, 0, name_alfa));
	
}

void Information::updateStageName()
{
	if (!EasingManager::tCountEnd(blackbox_t))return;
	if (EasingManager::tCountEnd(end_name_t))return;
	updateNameBegin();
	updateNameDelay();
	updateNameEnd();
}

void Information::updateNameBegin()
{

	if (EasingManager::tCountEnd(begin_name_t))return;
	EasingManager::tCount(begin_name_t, 1.0f);
	coloredstagenamepos.x = EasingCubicOut(begin_name_t, -800.f , WINDOW_WIDTH / 2.f);
	blackstagenamepos.x = EasingCubicOut(begin_name_t, 2400.f, WINDOW_WIDTH / 2.f);
	name_alfa = begin_name_t;
}

void Information::updateNameDelay()
{
	if (!EasingManager::tCountEnd(begin_name_t))return;
	if (EasingManager::tCountEnd(delay_name_t))return;
	EasingManager::tCount(delay_name_t, 1.5f);
	name_alfa = 1.0f;
}

void Information::updateNameEnd()
{
	if (!EasingManager::tCountEnd(delay_name_t))return;
	EasingManager::tCount(end_name_t, 0.5f);
	coloredstagenamepos.x = EasingCubicIn(end_name_t, WINDOW_WIDTH / 2.f, 2400.f);
	blackstagenamepos.x = EasingCubicIn(end_name_t, WINDOW_WIDTH / 2.f, -800.f );
	name_alfa = 1.f - end_name_t;
}

void Information::updateClearTexture()
{
	updateTranceClearTexture();
	updateRotateClearTexture();
	updateDelayClearTexture();
}

void Information::updateTranceClearTexture()
{
	if (EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].size_t_))return;
	for (int i = 0;i < cleartextures.size();i++) {
		EasingManager::tCount(cleartextures[i].size_t_, 0.5f);
		cleartextures[i].pos.x = EasingCubicOut(cleartextures[i].size_t_, cleartextures[i].beginpos.x, cleartextures[i].endpos.x);
		cleartextures[i].pos.y = EasingCubicOut(cleartextures[i].size_t_, cleartextures[i].beginpos.y, cleartextures[i].endpos.y);
		cleartextures[i].size.x = EasingCubicOut(cleartextures[i].size_t_, cleartextures[i].beginsize.x, cleartextures[i].endsize.x);
		cleartextures[i].size.y = EasingCubicOut(cleartextures[i].size_t_, cleartextures[i].beginsize.y, cleartextures[i].endsize.y);
	}
}

void Information::updateRotateClearTexture()
{
	if (!EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].size_t_))return;

	EasingManager::tCount(goaleasingtime_t,6.0f);

	for (int i = 0;i < cleartextures.size();i++) {
		float colorspeed = 60.f;
		cleartextures[i].color = ColorA(1, 0.75+0.5f*sin(goaleasingtime_t*colorspeed),0.5f+0.5f*sin(goaleasingtime_t*colorspeed), 1);//ƒJƒ‰[‚ð•Ï‚¦‚Ü‚·
	}


	if (EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].angle_t_))return;

	for (int i = 0;i < cleartextures.size();i++) {
		EasingManager::tCount(cleartextures[i].angle_t_, 0.5f);
		float endrotate = (i % 2 == 0 ? 360.f : -360.f);
		cleartextures[i].angle = EasingCubicOut(cleartextures[i].angle_t_, 0.0f, endrotate);
		cleartextures[i].pos.y = EasingReturn(cleartextures[i].angle_t_, cleartextures[i].endpos.y, -30.f);
		cleartextures[i].size.x = EasingReturn(cleartextures[i].angle_t_, cleartextures[i].endsize.x, 30.f);
		cleartextures[i].size.y = EasingReturn(cleartextures[i].angle_t_, cleartextures[i].endsize.y, 30.f);
	}
}

void Information::updateDelayClearTexture()
{
	if (!EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].angle_t_))return;
	if (EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].delay_t_))return;
	for (int i = 0;i < cleartextures.size();i++) {
		EasingManager::tCount(cleartextures[i].delay_t_, 1.0f);
	}
	if (EasingManager::tCountEnd(cleartextures[cleartextures.size() - 1].delay_t_)) {
		for (int i = 0;i < cleartextures.size();i++) {
			cleartextures[i].angle_t_ = 0.0f;
			cleartextures[i].delay_t_ = 0.0f;
		}
	}
}

void Information::drawClearTexture()
{
	for (int i = 0;i < cleartextures.size();i++) {
		DrawM.drawTextureBox(cleartextures[i].pos + Vec2f(4, -4), cleartextures[i].size, cleartextures[i].angle, cleartextures[i].tex, ColorA(0, 0, 0, 1));
		DrawM.drawTextureBox(cleartextures[i].pos,cleartextures[i].size,cleartextures[i].angle,cleartextures[i].tex,cleartextures[i].color);
		
	}
}
