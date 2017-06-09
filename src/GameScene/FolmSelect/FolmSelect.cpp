#include "FolmSelect.h"
#include"../../Top/Top.h"
#include"../../Scene/SceneManager.h"
#include"../../Top/DrawManager.h"
#include"../../Input/KeyManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../GameScene/GameMain/GameMain.h"
#include"../../Top/TextureManager.h"
#include"../../Top/MyJson.h"
#include"../../Top/SoundManager.h"
#include"../../Top/FadeManager.h"
#include"../../Top/DataManager.h"
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
	gl::enableDepthRead();
	gl::enableDepthWrite();
}

void FolmSelect::update()
{
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

}

void FolmSelect::shift()
{
	/*if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
	if (FadeM.getIsfadeinEnd()) {
		if (DataM.getNextscene() == SceneType::GANEMAIN_SCENE) {
			DataM.roadGetItems(worldnum, stagenum);
			SceneManager::createScene(GameMain());
		}
	}*/
}
