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
	stagenum = DataM.getWorldNum();

	isstagestartend =false;
	isstagestart = false;
	isgoal = false;
	fonteasing_in = false;
	blackbox_t = 0.0f;
	blackbox_delay_t = 0.0f;
	blackbox_return_t = 0.0f;
	CreateBlackBox();
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
	down.endsize = Vec2f(WINDOW_WIDTH, -150);
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
