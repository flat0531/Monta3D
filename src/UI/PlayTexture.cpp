#include "PlayTexture.h"
#include"../Top/TextureManager.h"
#include"../Top/DrawManager.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
PlayTexture::PlayTexture()
{

}

PlayTexture::PlayTexture(const ci::Vec2f _pos, const std::string _actionname, const int _number)
{
	pos = _pos;
	size = Vec2f(300, 300);
	tex = TextureM.CreateTexture("UserPlay/" + _actionname + "/" + "play" + std::to_string(_number) + ".png");
	frametex = TextureM.CreateTexture("Draw/" + _actionname + "/frame.png");
	wakutex = TextureM.CreateTexture("UI/waku.png");
	coloralfa = 0.2f;
	number = _number;
	alfa_t = 0.0f;
}

void PlayTexture::update(const int selectnum)
{
	if (selectnum==number) {
		EasingManager::tCount(alfa_t, 0.5f);
	}
	else {
		EasingManager::tCount(alfa_t, -0.5f);
	}
	coloralfa = EasingLinear(alfa_t, 0.2f, 1.0f);
}

void PlayTexture::draw(const ci::Vec2f trancepos)
{
	DrawM.drawTextureBox(pos + trancepos, size, 0.0f, wakutex, ColorA(1, 1, 1, coloralfa));
	DrawM.drawTextureBox(pos + trancepos, size, 0.0f, tex, ColorA(1, 1, 1, coloralfa));
	DrawM.drawTextureBox(pos + trancepos, size, 0.0f, frametex, ColorA(1, 1, 1, coloralfa));
}

ci::Surface PlayTexture::getSurface()
{
	return tex;
}
