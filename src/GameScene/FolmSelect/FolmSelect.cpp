#include "FolmSelect.h"
#include"../../Top/Top.h"
#include"../../Scene/SceneManager.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../GameScene/GameMain/GameMain.h"
#include"../../GameScene/StageSelect/StageSelect.h"
#include"../../GameScene/Draw/Draw.h"
#include"../../Top/TextureManager.h"
#include"../../Top/MyJson.h"
#include"../../Top/SoundManager.h"
#include"../../Top/FadeManager.h"
#include"../../Top/DrawManager.h"
#include"../../Top/DataManager.h"
#include"../../GameScene/FreeDraw/FreeDraw.h"
using namespace ci;
using namespace ci::app;
void FolmSelect::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		1.0f, 1000.f);
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));
	camera.setEyePoint(Vec3f(0, 0, -5));
	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);

	FadeM.StartFadeOut(false);
	uicreater.CreateUI("Json/UI/folmselect.json");
	SoundM.PlayBGM("drawscene.wav", 0.3f);
	SoundM.SetLoopBGM("drawscene.wav", true);
	DataM.setSelectActionName("slime");
	createAsset();

	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void FolmSelect::update()
{
	shiftScene();
	if (!isselect) {
		folmtexturelist.update();
	}
	select();
	updateWindow();
	updateButton();
}

void FolmSelect::draw()
{
	camera.setEyePoint(Vec3f(0, 0, -5));
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	gl::setMatrices(camera);



}

void FolmSelect::draw2D()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);
	uicreater.draw();
	folmtexturelist.draw();
	drawWindow();
	drawButton();
}

void FolmSelect::shift()
{
	if (isfadein&&FadeM.getIsfadeinEnd()) {
		DataM.setPrevScene(SceneType::FOLMSELECT_SCENE);

		if (DataM.getNextscene() == STAGESELECT_SCENE) {
			DataM.setSelectActionName("slime");
			SceneManager::createScene(StageSelect());
			return;
		}
		if (DataM.getNextscene() == SceneType::FREE_DRAW_SCENE) {
			SceneManager::createScene(FreeDraw());
			return;
		}
		if (DataM.getNextscene() == SceneType::DRAW_SCENE) {
			SceneManager::createScene(Draw());
			return;
		}
	
	}

}

void FolmSelect::shiftScene()
{
	if (!FadeM.getIsFading()&&KeyManager::getkey().isPush(KeyEvent::KEY_l)&&isselect&&isyes) {
		FadeM.StartFadeIn();
		isfadein = true;
		SoundM.FadeNowBGM(0.0f, 1.5f, true);
		if (folmtexturelist.getIsrelease()) {
			DataM.setNextScene(SceneType::FREE_DRAW_SCENE);
		}
		else {
			DataM.setNextScene(SceneType::DRAW_SCENE);
		}
		
	}
	if (!FadeM.getIsFading() && KeyManager::getkey().isPush(KeyEvent::KEY_k) && (!isselect)) {
		FadeM.StartFadeIn();
		isfadein = true;
		SoundM.FadeNowBGM(0.0f, 1.5f, true);
		DataM.setNextScene(SceneType::STAGESELECT_SCENE);
	}
}

void FolmSelect::select()
{
	if (!FadeM.getIsFading()&&KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
		if (isselect) {
			if (!isyes) {
				isselect = false;
				isyes = true;
				SoundM.PlaySE("change.wav");
			}
		}
		else {
			isselect = true;
			SoundM.PlaySE("actionselectbegin.wav");
		}
	}
}

void FolmSelect::updateWindow()
{
	if (!FadeM.getIsFading() && isselect) {
		if (KeyManager::getkey().isPush(KeyEvent::KEY_k)) {
			SoundM.PlaySE("change.wav");
			isselect = false;
			isyes = true;
		}
	}
}

void FolmSelect::updateButton()
{
	if (isselect) {
		if (KeyManager::getkey().isPush(KeyEvent::KEY_a)) {
			SoundM.PlaySE("stagecursor.wav");
		
			isyes = true;
		}
		if (KeyManager::getkey().isPush(KeyEvent::KEY_d)) {
			SoundM.PlaySE("stagecursor.wav");
			isyes = false;
		}
	}
}

void FolmSelect::drawButton()
{
	if (isselect) {
		Vec2f leftpos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f + Vec2f(-100, 75);
		Vec2f rightpos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f + Vec2f(100, 75);
		Vec2f size = Vec2f(200, 100);
		DrawM.drawTextureBox(leftpos, size, 0.0f, TextureM.getTexture("UI/Button/hai.png"));
		DrawM.drawTextureBox(rightpos, size, 0.0f, TextureM.getTexture("UI/Button/iie.png"));
		DrawM.drawTextureBox((isyes?leftpos:rightpos)+Vec2f(0,60), Vec2f(75,75), 0.0f, TextureM.getTexture("UI/uzu.png"));
	}
}

void FolmSelect::drawWindow()
{
	if (isselect) {
		Vec2f pos = Vec2f(WINDOW_WIDTH,WINDOW_HEIGHT)/2.f;
		Vec2f size = Vec2f(500, 400);
		if (folmtexturelist.getIsrelease()) {
			DrawM.drawTextureBox(pos, size, 0.0f, TextureM.getTexture("UI/dofreenurie.png"));
		}
		else {
			DrawM.drawTextureBox(pos, size, 0.0f, TextureM.getTexture("UI/donurie.png"));
		}
	}
}

void FolmSelect::createAsset()
{
	TextureM.CreateTexture("UI/donurie.png");
	TextureM.CreateTexture("UI/dofreenurie.png");
	TextureM.CreateTexture("UI/Button/hai.png");
	TextureM.CreateTexture("UI/Button/iie.png");

	SoundM.CreateSE("stagecursor.wav");
	SoundM.CreateSE("change.wav");
	SoundM.CreateSE("actionselectbegin.wav");
	SoundM.CreateSE("actionselectend.wav");
}
