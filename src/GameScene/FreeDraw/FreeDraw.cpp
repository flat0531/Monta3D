#include "FreeDraw.h"
#include"../../Top/Top.h"
#include"../../Scene/SceneManager.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
#include"../../GameScene/FolmSelect/FolmSelect.h"
#include"../../Top/TextureManager.h"
#include"../../Top/MyJson.h"
#include"../../Top/SoundManager.h"
#include"../../Top/FadeManager.h"
#include"../../Top/DrawManager.h"
#include"../../Top/DataManager.h"
#include"../../Top/CollisionManager.h"
#include"../../Input/MouseMamager.h"
using namespace ci;
using namespace ci::app;
FreeDraw::FreeDraw()
{
}

void FreeDraw::setup()
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
    uiback.CreateUI("Json/UI/freedrawsceneback.json");
	uifront.CreateUI("Json/UI/freedrawscenefront.json");
	SoundM.PlayBGM("drawscene.wav", 0.3f);
	SoundM.SetLoopBGM("drawscene.wav", true);
	SoundM.CreateSE("rappa.wav");
	charactername = DataM.getSelectActionName();
	Vec2f playercanvaspos = Vec2f(WINDOW_WIDTH / 2  - 440, WINDOW_HEIGHT / 2.0 - 256);
	playercanvas.setup(playercanvaspos, Vec2f(512, 512), charactername);
	
	TextureM.CreateTexture("UI/texturesavewindowpng.png");

	savewindowpos = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT) / 2.f;
	savewindowsize = Vec2f(0,0);
	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void FreeDraw::update()
{
	if (FadeM.getIsFading())return;
	updateSave();
	updateBack();
	if (!issavewindow) {
		drawmenu.update();

		drawpointer.update();
		palletmanager.update();
		drawpointer.setCircleSize(drawmenu.getSizeRangeValue());
		updateEraceCanvas();
		updateDrawCanvas();
		drawpointer.setCircleColor(palletmanager.getSelectcolor());
		drawmenu.setCircleColor(palletmanager.getSelectcolor());
		drawmenu.setSampleCircleSize(drawpointer.getCircleSize());
		drawpointer.setIsCircledraw(CollisionM.isBoxPoint(drawpointer.getPos(), playercanvas.getPos(), playercanvas.getSIze()));
	}

	updateSaveWindow();
}

void FreeDraw::draw()
{
	camera.setEyePoint(Vec3f(0, 0, -5));
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000));

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	gl::setMatrices(camera);
}

void FreeDraw::draw2D()
{
	gl::setMatrices(ortho);
	gl::pushModelView();
	uiback.draw();
	drawmenu.draw();
	playercanvas.draw();
	palletmanager.draw();
	drawpointer.draw();
	uifront.draw();
	if (issavewindow) {
		drawSaveWindow();
	}
	gl::popModelView();

}

void FreeDraw::shift()
{
	if (isshift&&FadeM.getIsfadeinEnd()) {
		DataM.setPrevScene(FREE_DRAW_SCENE);
		DataM.setNextScene(FOLMSELECT_SCENE);
		SceneManager::createScene(FolmSelect());
		return;
	}
}

void FreeDraw::updateEraceCanvas()
{
	if (FadeM.getIsFading())return;
	if (MouseManager::getMouse().isPress(MouseEvent::RIGHT_DOWN)) {
		playercanvas.updateCanvas(ColorA(1, 1, 1, 0), drawpointer.getPos(), drawpointer.getCircleSize());

	}
}

void FreeDraw::updateDrawCanvas()
{
	if (FadeM.getIsFading())return;
	if (MouseManager::getMouse().isPress(MouseEvent::LEFT_DOWN)) {
		playercanvas.updateCanvas(palletmanager.getSelectcolor(), drawpointer.getPos(), drawpointer.getCircleSize());
	}

}

void FreeDraw::updateSave()
{
	if (FadeM.getIsFading())return;
	if (isshift)return;
	if (issavewindow)return;
	Vec2f buttonpos = Vec2f(1400, 500);
	Vec2f buttonsize = Vec2f(200, 100);
	if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
		if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), buttonpos - buttonsize / 2, buttonsize)) {
			DataM.WriteImage(playercanvas.getSurface(),charactername);
			drawtex = DataM.getLastSaveTexture(charactername);
			SoundM.PlaySE("rappa.wav",0.7f);
			issavewindow = true;
		}
	}
	
}

void FreeDraw::updateBack()
{
	if (FadeM.getIsFading())return;
	if (isshift)return;
	if (issavewindow)return;
	Vec2f buttonpos = Vec2f(1400, 670);
	Vec2f buttonsize = Vec2f(200, 100);
	if (MouseManager::getMouse().isPull(MouseEvent::LEFT_DOWN)) {
		if (CollisionM.isBoxPoint(MouseManager::getMouse().getmousepos(), buttonpos - buttonsize / 2, buttonsize)) {
			isshift = true;
			FadeM.StartFadeIn();
			SoundM.FadeNowBGM(0.0f, 1.5f, false);
		}
	}
}

void FreeDraw::updateSaveWindow()
{
	if (issavewindow) {
		EasingManager::tCount(savewinodw_t,1.0f);
		savewindowsize.x = EasingQuadOut(savewinodw_t, 0.f, 1000.f);
		savewindowsize.y = EasingQuadOut(savewinodw_t, 0.f, 700.f);
		if (EasingManager::tCountEnd(savewinodw_t)) {
			EasingManager::tCount(delay_t, 1.5f);
		}
		if (EasingManager::tCountEnd(delay_t)&&(!isshift)) {
			isshift = true;
			FadeM.StartFadeIn();
			SoundM.FadeNowBGM(0.0f, 1.5f, false);
		}
	}
}

void FreeDraw::drawSaveWindow()
{
	if (issavewindow) {
		DrawM.drawTextureBox(savewindowpos,savewindowsize,0.0f,TextureM.getTexture("UI/texturesavewindowpng.png"));
		DrawM.drawTextureBox(savewindowpos+Vec2f(0,-100), savewinodw_t*Vec2f(350,350), 0.0f, drawtex);
		DrawM.drawTextureBox(savewindowpos + Vec2f(0, -100), savewinodw_t*Vec2f(350, 350), 0.0f, TextureM.getTexture("Draw/" + charactername + "/" + "frame.png"));
		
	}
}
