#include "StatusBars.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/EasingManager.h"
#include"../Top/DataManager.h"
using namespace ci;
using namespace ci::app;
using namespace ci;
using namespace ci::app;
StatusBars::StatusBars()
{
	Vec2f size = Vec2f(60, 40);
	Vec2f basepos = Vec2f(200, 150);
	float trancey = 100.f;
	red.pos = basepos;
	red.size = size;
	red.beginvalue = 0.0f;
	red.endvalue = 0.0f;
	red.value = 0.0f;
	red.t = 0.0f;
	red.color = ci::ColorA(1, 0, 0, 1);

	green.pos = basepos + Vec2f(0, trancey*1.f);
	green.size = size;
	green.beginvalue = 0.0f;
	green.endvalue = 0.0f;
	green.value = 1.0f;
	green.t = 1.0f;
	green.color = ci::ColorA(0, 1, 0, 1);

	blue.pos = basepos + Vec2f(0, trancey*2.f);
	blue.size = size;
	blue.beginvalue = 0.0f;
	blue.endvalue = 0.0f;
	blue.value = 1.0f;
	blue.t = 1.0f;
	blue.color = ci::ColorA(0, 0, 1, 1);

	white.pos = basepos + Vec2f(0, trancey*3.f);
	white.size = size;
	white.beginvalue = 0.0f;
	white.endvalue = 0.0f;
	white.value = 1.0f;
	white.t = 1.0f;
	white.color = ci::ColorA(1, 1, 1, 1);

	createAsset();

}

void StatusBars::update()
{
	EasingManager::tCount(red.t,0.5f);
	red.value = EasingCubicOut(red.t, red.beginvalue, red.endvalue);

	EasingManager::tCount(blue.t, 0.5f);
	blue.value = EasingCubicOut(blue.t, blue.beginvalue, blue.endvalue);

	EasingManager::tCount(green.t, 0.5f);
	green.value = EasingCubicOut(green.t, green.beginvalue, green.endvalue);

	EasingManager::tCount(white.t, 0.5f);
	white.value = EasingCubicOut(white.t, white.beginvalue, white.endvalue);
}

void StatusBars::draw()
{
	float trance_x = -65.f;
	Vec2f size = Vec2f(110, 55);
	DrawM.drawTextureBox(red.pos + Vec2f(trance_x, 20) + Vec2f(1, -1), size, 0.0f, attacktex, ColorA(0, 0, 0, 1));
	DrawM.drawTextureBox(red.pos + Vec2f(trance_x, 20), size, 0.0f, attacktex, ColorA(1, 0, 0, 1));
	
	DrawM.drawTextureBox(green.pos + Vec2f(trance_x, 20) + Vec2f(1, -1), size, 0.0f, speedktex, ColorA(0, 0, 0, 1));
	DrawM.drawTextureBox(green.pos + Vec2f(trance_x, 20), size, 0.0f, speedktex, ColorA(0, 1, 0, 1));

	DrawM.drawTextureBox(blue.pos + Vec2f(trance_x, 20) + Vec2f(1, -1), size, 0.0f, defensetex, ColorA(0, 0, 0, 1));
	DrawM.drawTextureBox(blue.pos + Vec2f(trance_x, 20), size, 0.0f, defensetex, ColorA(0, 0, 1, 1));
	
	DrawM.drawTextureBox(white.pos + Vec2f(trance_x, 20) + Vec2f(1, -1), size, 0.0f, flytex, ColorA(0, 0, 0, 1));
	DrawM.drawTextureBox(white.pos + Vec2f(trance_x, 20), size, 0.0f,flytex, ColorA(1, 1, 1, 1));



	DrawM.drawBoxEdge(red.pos + Vec2f(2, -2), Vec2f(red.size.x*red.value, red.size.y), ColorA(0, 0, 0, 1));
	DrawM.drawBoxEdge(red.pos, Vec2f(red.size.x*red.value,red.size.y), red.color);

	DrawM.drawBoxEdge(green.pos + Vec2f(2, -2), Vec2f(green.size.x*green.value, green.size.y), ColorA(0, 0, 0, 1));
	DrawM.drawBoxEdge(green.pos, Vec2f(green.size.x*green.value, green.size.y), green.color);


	DrawM.drawBoxEdge(blue.pos+Vec2f(2,-2), Vec2f(blue.size.x*blue.value, blue.size.y), ColorA(0, 0, 0, 1));
	DrawM.drawBoxEdge(blue.pos, Vec2f(blue.size.x*blue.value, blue.size.y),blue.color);

	DrawM.drawBoxEdge(white.pos+Vec2f(2,-2), Vec2f(white.size.x*white.value, white.size.y), ColorA(0, 0, 0, 1));
	DrawM.drawBoxEdge(white.pos, Vec2f(white.size.x*white.value, white.size.y), white.color);
}

void StatusBars::setEaing(std::string _name)
{
	red.t = 0.0f;
	blue.t = 0.0f;
	green.t = 0.0f;
	white.t = 0.0f;

	red.beginvalue = red.value;
	red.endvalue = DataM.getBaseStatus(_name).x + DataM.getPlayPowerRate() * 3;

	green.beginvalue = green.value;
	green.endvalue = DataM.getBaseStatus(_name).y + DataM.getPlaySpeedRate() * 5;

	blue.beginvalue = blue.value;
	blue.endvalue = 2 * int(DataM.getPlayDefenseRate()*3.5f) + 1;

	white.beginvalue = white.value;
	white.endvalue = DataM.getBaseStatus(_name).z*1.25f;


}

void StatusBars::createAsset()
{
	attacktex= TextureM.CreateTexture("UI/Bar/bar_kougeki.png");
	defensetex = TextureM.CreateTexture("UI/Bar/bar_bougyo.png");
	speedktex = TextureM.CreateTexture("UI/Bar/bar_speed.png");
	flytex = TextureM.CreateTexture("UI/Bar/bar_hikou.png");
}
