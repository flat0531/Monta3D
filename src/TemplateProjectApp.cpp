// 
// Cinder—Œ^
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
#include"Top/SoundManager.h"

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
private:
	ColorA color;
	MayaCamUI camera;

};

void TemplateProjectApp::setup()
{
	FadeM.setup();
	SceneManager::createScene(Title());
	color = ColorA(0,0,0,1);
	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

}

void TemplateProjectApp::prepareSettings(Settings* settings) {
	settings->setWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
	settings->enableMultiTouch();
}
void TemplateProjectApp::mouseDown(MouseEvent event)
{
	MouseManager::getMouse().registerDown(event);
}

void TemplateProjectApp::mouseUp(MouseEvent event)
{
	MouseManager::getMouse().registerUp(event);
}

void TemplateProjectApp::mouseDrag(MouseEvent event)
{
	MouseManager::getMouse().registerMove(event);
}

void TemplateProjectApp::mouseMove(MouseEvent event)
{
	MouseManager::getMouse().registerMove(event);
}

void TemplateProjectApp::mouseWheel(MouseEvent event)
{

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
	SceneManager::update();
	FadeM.update();
	EasStr.update();
	SoundM.updateGainFadeT();
}

void TemplateProjectApp::draw()
{
	gl::clear(color);


	SceneManager::draw();
	SceneManager::draw2D();
	FadeM.draw();
	SortManager::getSort().setSortCount(SortManager::getSort().BASESORT);
	SceneManager::shift();

	KeyManager::getkey().registerEnd();
	MouseManager::getMouse().registerEnd();

}

void TemplateProjectApp::shutdown()
{

}

CINDER_APP_NATIVE(TemplateProjectApp, RendererGl)
