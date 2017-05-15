// 
// Cinder雛型
//

#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"Input\KeyManager.h"
#include"Input\MouseMamager.h"
#include"Scene/SceneManager.h"
#include"GameScene/Title/Title.h"
using namespace ci;
using namespace ci::app;
#include "cinder/MayaCamUI.h"
#include"Top\Top.h"
#include"Top/SortManager.h"
#include"Top\EasingStream.h"
#include"Top/FadeManager.h"
void drawGrid(float size,float step) {
	//for (float i = -size;i <= size; i += step) {
	//	gl::drawLine(Vec3f(i, 0.0f, -size), Vec3f(i, 0.0f, size));
	//	gl::drawLine(Vec3f( - size, 0.0f, i), Vec3f(size, 0.0f, i));

	//}

}


class TemplateProjectApp : public AppNative {

public:
	void prepareSettings(Settings* settings);
	void setup();
	void mouseDown(MouseEvent event) override;
	void mouseUp(MouseEvent event) override;
	void mouseDrag(MouseEvent event) override;
	void mouseMove(MouseEvent event) override;
	void mouseWheel(MouseEvent event) override;
	void keyDown(KeyEvent event) override; 
	void keyUp(KeyEvent event) override;
	void update();
	void draw();
	void shutdown()override;
	void updateGamePad();
	void setGamePad();
private:
	ColorA color;
	MayaCamUI camera;

};

void TemplateProjectApp::setup()
{
	FadeM.setup();
	SceneManager::createScene(Title());
	color = ColorA(0,0,0,1);
	//setGamePad();
	//CameraPersp cam;
	//cam.setPerspective(60, getWindowAspectRatio(), 1, 1000);
	//cam.setCenterOfInterest(20);
	//camera.setCurrentCam(cam);

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

}

void TemplateProjectApp::prepareSettings(Settings* settings) {
	// 画面サイズを変更する
	settings->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	settings->enableMultiTouch();
}
void TemplateProjectApp::mouseDown(MouseEvent event)
{
	MouseManager::getMouse().registerDown(event);
	
	//camera.mouseDown(event.getPos());
}

void TemplateProjectApp::mouseUp(MouseEvent event)
{
	MouseManager::getMouse().registerUp(event);
}

void TemplateProjectApp::mouseDrag(MouseEvent event)
{
	MouseManager::getMouse().registerMove(event);
	//camera.mouseDrag(event.getPos(), event.isRightDown(), event.isMiddleDown(), false);
}

void TemplateProjectApp::mouseMove(MouseEvent event)
{
	MouseManager::getMouse().registerMove(event);
}

void TemplateProjectApp::mouseWheel(MouseEvent event)
{
	//CameraPersp cam = camera.getCamera();
	//cam.setEyePoint(cam.getEyePoint() + cam.getViewDirection()*event.getWheelIncrement());
	//camera.setCurrentCam(cam);
	MouseManager::getMouse().registerWheel(event);
	
}

void TemplateProjectApp::keyDown(KeyEvent event)
{
	KeyManager::getkey().registerDown(event);
}

void TemplateProjectApp::keyUp(KeyEvent event)
{
	KeyManager::getkey().registerUp(event);
}

void TemplateProjectApp::update()
{
	//updateGamePad();
	SceneManager::update();
	FadeM.update();
	EasStr.update();
}

void TemplateProjectApp::draw()
{
	// clear out the window with black
	gl::clear(color);
	//gl::pushModelView();
	//Vec2f size(100, 100);
	//gl::translate(MouseManager::getMouse().getmousepos());
	//gl::drawSolidRect(Rectf(-size, size));
	//gl::popModelView();
	//gl::clear(Color(0,0,0));
	//gl::setMatrices(camera.getCamera());
	//gl::color(Color(.5f, .5f, .5f));
	//drawGrid(50, 1);
	//gl::pushModelView();
	//gl::translate(Vec3f(0,10,0));
	//gl::drawCoordinateFrame();
	//gl::popModelView();

	//CameraPersp cam;
	//cam.setPerspective(60, getWindowAspectRatio(), 1, 300);
	//gl::drawFrustum(cam);

	SceneManager::draw();
	SceneManager::draw2D();
	FadeM.draw();
	SortManager::getSort().setSortCount(SortManager::getSort().BASESORT);
	SceneManager::shift();

	KeyManager::getkey().registerEnd();
	MouseManager::getMouse().registerEnd();
	//Gamepad_processEvents();
	//console() << getElapsedSeconds() << std::endl;
	//console() << getAverageFps() << std::endl;

}

void TemplateProjectApp::shutdown()
{
	//Gamepad_shutdown();
}

void TemplateProjectApp::updateGamePad()
{
	/*static unsigned int iterationsToNextPoll = POLL_ITERATION_INTERVAL;
	iterationsToNextPoll--;
	if (iterationsToNextPoll == 0) {
		Gamepad_detectDevices();
		iterationsToNextPoll = POLL_ITERATION_INTERVAL;
	}*/
}

void TemplateProjectApp::setGamePad()
{
	/*Gamepad_deviceAttachFunc(onDeviceAttached, (void *)0x1);
	Gamepad_deviceRemoveFunc(onDeviceRemoved, (void *)0x2);
	Gamepad_buttonDownFunc(onButtonDown, (void *)0x3);
	Gamepad_buttonUpFunc(onButtonUp, (void *)0x4);
	Gamepad_axisMoveFunc(onAxisMoved, (void *)0x5);
	Gamepad_init();*/
}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)
