#include "FadeManager.h"
#include"Top.h"
#include"../Top/DrawManager.h"
#include"../Top/EasingManager.h"
#include"../Top/TextureManager.h"
#include"../Top/SoundManager.h"
#include"cinder\Rand.h"
using namespace ci;
using namespace ci::app;
void FadeManager::setup()
{
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);
	texturescale = Vec2f(0, 0);
	texturerotate = 0.0f;
	int y_num = 4;
	int x_num = 7;
	maxtexturescale = Vec2f((float)WINDOW_WIDTH / (float)x_num, (float)WINDOW_HEIGHT / (float)y_num);
	for (int y = 0;y < y_num;y++) {
		for (int x = 0;x < x_num;x++) {
			texturepos.push_back(Vec2f(x*maxtexturescale.x, y*maxtexturescale.y));
		}
	}
	SoundM.CreateSE("fadein.wav");
	SoundM.CreateSE("fadeout.wav");
	isfadeoutsound = false;
}

void FadeManager::update()
{
	isfadeinend = false;
	isfadeoutend = false;
	updateFadeIn();
	updateFadeOut();
}

void FadeManager::draw()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);

	gl::pushModelView();

	if (isfading) {
		for (int i = 0;i < texturepos.size();i++) {
			float a = ((float)i) / ((float)texturepos.size());
			ColorA color = ColorA(randomrgb[0] ? 1 : a, 1, randomrgb[2] ? 1 : a, 1);//g���P�ŌŒ肵�������悩�������߂��̂܂܂�
			DrawM.drawBox(texturepos[i] + maxtexturescale / 2.f, texturescale, texturerotate,color);
			DrawM.drawTextureBox(texturepos[i] + maxtexturescale / 2.f, texturescale, texturerotate, surface.getTexture(), ColorA(1, 1, 1, 1));
			DrawM.drawTextureBox(texturepos[i] + maxtexturescale / 2.f, texturescale, texturerotate, TextureM.getTexture("UI/fadeframe.png"), ColorA(1, 1, 1, 1));
		}
	}




	gl::popModelView();
}



void FadeManager::StartFadeIn()
{
	SoundM.PlaySE("fadein.wav",0.6f);
	easingtime.clear();
	t.clear();
	texturescale = Vec2f(0, 0);
	texturerotate = 0.0f;

	isfading = true;
	isfadein = true;

	easingtime.push_back(1.2f);
	easingtime.push_back(1.0f);

	randSeed(app::getElapsedFrames()%10000);
	
	easingtype = randInt(0, EasingManager::EasType::Return);
	gl::Texture backeefect = TextureM.CreateTexture("UI/fadeslime.png");
	TextureM.CreateTexture("UI/fadeframe.png");
	surface = SurfaceEffect(backeefect, backeefect.getSize() / 7.f, backeefect.getSize()*(1.f - (1.f / 7.f)),
		Vec3f(0, 0, 0), Vec3f(0, 0, 0), Vec3f(0, 0, 0),
		EasingManager::EasType::Linear, EasingManager::EasType::Return, 30.f,
		-M_PI / 4.f, 0.0f, 0.25f, backeefect.getSize().x*0.4f*1.414f,easingtime[FadeInStep::FADEIN_SURFACE], 0.0f, ColorA(0, 1, 0, 0.5f));
	for (int i = 0;i < 3;i++) {
		randomrgb[i] = randBool();
	}
	
	for (int i = 0;i < FADEIN_MAX;i++) {
		t.push_back(0.0f);
	}

}

void FadeManager::StartFadeOut(const bool isplayse)
{
	easingtime.clear();
	t.clear();
	easingtime.push_back(1.f);
	t.push_back(0.0f);
	isfading = true;
	isfadein = false;
	isfadeout = true;
	isfadeoutsound = isplayse;
}


bool FadeManager::getIsFading()
{
	return isfading;
}



bool FadeManager::getIsfadeinEnd()
{
	return isfadeinend;
}

bool FadeManager::getIsfadeoutEnd()
{
	return isfadeoutend;
}

bool FadeManager::getIsfadeIn()
{
	return isfadein;
}

void FadeManager::updateFadeIn()
{
	
	if (isfadein) {
		if (!EasingManager::tCountEnd(t[FadeInStep::FADEIN_SCALEUP])) {
			EasingManager::tCount(t[FadeInStep::FADEIN_SCALEUP], easingtime[FadeInStep::FADEIN_SCALEUP]);
			texturescale.x =EasingCubicOut(t[FadeInStep::FADEIN_SCALEUP], 0.0f, maxtexturescale.x);
			texturescale.y = EasingCubicOut(t[FadeInStep::FADEIN_SCALEUP], 0.0f, maxtexturescale.y);
			//texturerotate = EasingManager::getEas[easingtype](t[FadeInStep::FADEIN_SCALEUP], 0.0f, 720.f);
			texturerotate = EasingQuartOut(t[FadeInStep::FADEIN_SCALEUP], 0.0f, 720.f);
		}
		if ((!EasingManager::tCountEnd(t[FadeInStep::FADEIN_SURFACE])&&
			EasingManager::tCountEnd(t[FadeInStep::FADEIN_SCALEUP]))) {
			surface.update();
			EasingManager::tCount(t[FadeInStep::FADEIN_SURFACE], easingtime[FadeInStep::FADEIN_SURFACE]);
		}
		if (EasingManager::tCountEnd(t[FadeInStep::FADEIN_SURFACE])) {
			isfadein = false;
			isfadeinend = true;
			t.clear();
			easingtime.clear();
		}
	}
}

void FadeManager::updateFadeOut()
{
	if (isfadeout) {
		if (!EasingManager::tCountEnd(t[0])) {
			EasingManager::tCount(t[0],easingtime[0]);
			texturescale.x = EasingBackInOut(t[0],maxtexturescale.x,0.0f);
			texturescale.y = EasingBackInOut(t[0], maxtexturescale.y, 0.0f);
			float soundplay_t = 0.5f;
			if (t[0] >= soundplay_t&&isfadeoutsound) {
				isfadeoutsound = false;
				SoundM.PlaySE("fadeout.wav",0.3f);
			}
		}
		if (EasingManager::tCountEnd(t[0])) {
			isfading = false;
			isfadeout = false;
			isfadeoutend = true;
			t.clear();
			easingtime.clear();
		}
	}
}
