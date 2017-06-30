#include "StageNamePlate.h"
#include"../Top/DrawManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
StageNamePlate::StageNamePlate()
{
}
StageNamePlate::StageNamePlate(const int worldnum, const int stagenum, const StageData _stagedata)
{
	TextureM.CreateTexture("UI/itemwindow.png");
	TextureM.CreateTexture("UI/itemicon.png");
	TextureM.CreateTexture("UI/itemplate.png");
	stagenametex = TextureM.CreateTexture("UI/stagename/stagename" + std::to_string(worldnum) + "_" + std::to_string(stagenum) + ".png");
	stagesnaptex = TextureM.CreateTexture("UI/stagesnap/" + std::to_string(worldnum) + "_" + std::to_string(stagenum) + "snap.png");
	float rate = 0.5f;
	pos = Vec2f(285, 350);
	size = rate*TextureM.getTexture("UI/itemwindow.png").getSize();
	slide_t = 1.0f;
	begincoloralfa = 1.0f;
	endcoloralfa = 1.0f;
	coloralpha = 1.0f;
	issliding = false;
	isslidein = false;
	isslideout = false;
	stagedata = _stagedata;
	setItemData();
}

void StageNamePlate::update()
{
	if (!issliding)return;
	updateSlideOut();
	updateSlideIn();
}

void StageNamePlate::draw()
{
	DrawM.drawTextureBox(pos,size,0.f, TextureM.getTexture("UI/itemwindow.png"),ColorA(1,1,1, coloralpha));
	DrawM.drawTextureBox(pos, Vec2f(430,250), 0.f, stagesnaptex, ColorA(1, 1, 1, coloralpha));
	if (!(itemicons.size() == 0)) {
		DrawM.drawTextureBox(pos + Vec2f(65, 92), Vec2f(300, 70), 0.f, TextureM.getTexture("UI/itemplate.png"), ColorA(1, 1, 1, coloralpha));
	}
	
	DrawM.drawTextureBox(pos + Vec2f(2, -48), Vec2f(460, 115), 0.f, stagenametex, ColorA(0, 0, 0, coloralpha));
	DrawM.drawTextureBox(pos+Vec2f(0,-50), Vec2f(460,115), 0.f,stagenametex, ColorA(1, 1, 1, coloralpha));
	drawItemIcon();
}

void StageNamePlate::SlideOut(const int worldnum, const int stagenum)
{
	isslideout = true;
	issliding = true;
	easingbeginpos = pos;
	easingendpos = Vec2f(-250, pos.y);
	slide_t = 0.0f;
	begincoloralfa = coloralpha;
	endcoloralfa = 0.f;
}

void StageNamePlate::SlideIn(const int worldnum, const int stagenum, const StageData _stagedata)
{
	isslidein = true;
	issliding = true;
	easingbeginpos = pos;
	easingendpos = Vec2f(285, 350);
	slide_t = 0.0f;
	begincoloralfa = coloralpha;
	endcoloralfa = 1.f;
	stagedata = _stagedata;
	stagesnaptex = TextureM.CreateTexture("UI/stagesnap/" + std::to_string(worldnum) + "_" + std::to_string(stagenum) + "snap.png");
	stagenametex = TextureM.CreateTexture("UI/stagename/stagename" + std::to_string(worldnum) + "_" + std::to_string(stagenum) + ".png");
	setItemData();
}

bool StageNamePlate::getIsSliding()
{
	return issliding;
}

bool StageNamePlate::getIsSlideIn()
{
	return isslidein;
}

void StageNamePlate::updateSlideOut()
{
	if (!isslideout)return;
	EasingManager::tCount(slide_t,0.3f);
	pos.x = EasingCubicIn(slide_t, easingbeginpos.x, easingendpos.x);
	pos.y = EasingCubicIn(slide_t, easingbeginpos.y, easingendpos.y);
	coloralpha = EasingLinear(slide_t,begincoloralfa,endcoloralfa);
	if (EasingManager::tCountEnd(slide_t)) {
		isslideout = false;
		issliding = false;
	}
}

void StageNamePlate::updateSlideIn()
{
	if (!isslidein)return;
	EasingManager::tCount(slide_t, 0.3f);
	pos.x = EasingCubicOut(slide_t, easingbeginpos.x, easingendpos.x);
	pos.y = EasingCubicOut(slide_t, easingbeginpos.y, easingendpos.y);
	coloralpha = EasingLinear(slide_t, begincoloralfa, endcoloralfa);
	if (EasingManager::tCountEnd(slide_t)) {
		isslidein = false;
		issliding = false;
	}
}

void StageNamePlate::drawItemIcon()
{
	for (int i = 0;i < stagedata.getIsItem().size();i++) {
		if (stagedata.getIsItem()[i]) {
			DrawM.drawTextureBox(pos + itemicons[i].trancepos, itemicons[i].size, 0, TextureM.getTexture("UI/itemicon.png"),ColorA(1, 1, 1, coloralpha));
		}
		else {
			DrawM.drawTextureBox(pos + itemicons[i].trancepos, itemicons[i].size, 0, TextureM.getTexture("UI/itemicon.png"), ColorA(0.2, 0.2, 0.2, coloralpha));
		}
	}
}

void StageNamePlate::setItemData()
{
	itemicons.clear();
	for (int i = 0;i < stagedata.getIsItem().size();i++) {
		ItemIcon buff;
	    buff.size = Vec2f(75, 75);
		float rate = 1.3f;
		buff.trancepos = Vec2f(65-(float(stagedata.getIsItem().size()))*(buff.size.x / 2.f)*rate+buff.size.x/2.f*rate+i*buff.size.x*rate, 92);
		buff.isget = stagedata.getIsClear();
		itemicons.push_back(buff);
	}
}
