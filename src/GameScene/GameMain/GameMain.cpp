#include "GameMain.h"
#include"../../Input/KeyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../Top/Top.h"
#include"../../Top/MyJson.h"
#include"../../Top/DrawManager.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"cinder/ObjLoader.h"
#include"../../WorldObject/Player.h"
#include"../../WorldCreater/BulletManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldCreater/CameraMnager.h"
#include"../../Top/FadeManager.h"
#include"../../WorldObject/ShiftFloorObject.h"
#include"../../Top/MyJson.h"
#include"../../Top/CollisionManager.h"
using namespace ci;
using namespace ci::app;

GameMain::GameMain()
{
}

void GameMain::setup()
{
	camera = CameraPersp(WINDOW_WIDTH, WINDOW_HEIGHT,
		60.0f,
		1.0f*WorldScale, 1000.f*WorldScale);
	camera.setCenterOfInterestPoint(Vec3f(0, 0, 1000 * WorldScale));

	ortho = CameraOrtho(0, WINDOW_WIDTH,
		WINDOW_HEIGHT, 0,
		1, 101);

	gl::enableDepthRead();
	gl::enableDepthWrite();
	isshiting = false;
	worldnum = 1;
	stagenum = 1;
	floornum = 1;

	mapmanager.ReadData(1, 1, 1);





	cameramanager = std::make_shared<CameraManager>();

	bulletmanager = std::make_shared<BulletManager>();
	charactermanager = std::make_shared<CharacterManager>();
	mapchipmanager = std::make_shared<MapChipManager>();
	effectmanager = std::make_shared<EffectManager>();
	mainwindow = std::make_shared<MainWindow>();


	charactermanager->setBulletManagerPointer(bulletmanager->getThisPointer());
	charactermanager->setEffectManagerPointer(effectmanager->getThisPointer());

	charactermanager->CreatePlayer(Vec3f(-22.0, 3, 0.0f)*WorldScale);
	charactermanager->CreateEnemys(1, 1, 1);//

	charactermanager->setBulletManagerPtrToPlayer();
	charactermanager->setBulletManagerPtrToEnemys();
	charactermanager->setMainWindowPointer(mainwindow->getThisPtr());

	charactermanager->setPlayerAction(ActionType::SLIME);
	charactermanager->setEnemysAction();

	bulletmanager->setCharacterManagerPtr(charactermanager->getThisPointer());
	bulletmanager->setEffectManagerPtr(effectmanager->getThisPointer());
	bulletmanager->setMainWindowPtr(mainwindow->getThisPtr());

	mapchipmanager->setBulletManagerPointer(bulletmanager->getThisPointer());
	mapchipmanager->setCharacterManagerPointer(charactermanager->getThisPointer());
	mapchipmanager->setEffectManagerPointer(effectmanager->getThisPointer());

	mainwindow->setCharacterManagerPtr(charactermanager->getThisPointer());

	mapchipmanager->setGoal(std::bind(&GameMain::shiftGoal, this));
	mapchipmanager->setup(1, 1, 1);

	

	cameramanager->setPlayerPos(charactermanager->getPlayer()->getPos());
	cameramanager->unitPrevCenterOfInterestPoint(charactermanager->getPlayer()->getPos());
	cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
	cameramanager->setMinValue(Vec2f(0, 0));
	cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
	cameramanager->update();

	FadeM.StartFadeOut(false);
	cretateShiftFloorObject();

	mainwindow->setSelectTextureNum(1);

	playBGM();
}

void GameMain::update()
{
	if (!FadeM.getIsfadeIn()) {

		charactermanager->update();

		bulletmanager->update();

		mapchipmanager->update();
	}
	

	cameramanager->setPlayerPos(charactermanager->getPlayer()->getPos());
	cameramanager->setPlayerSpeed(charactermanager->getPlayer()->getSpeed());
	cameramanager->update();
	effectmanager->update();
	mainwindow->update();
	updateShiftFloorObject();

	ReCreateStage();
}

void GameMain::draw()
{


	camera.setEyePoint(cameramanager->getSetEyePoint());
	camera.setCenterOfInterestPoint(cameramanager->getSetCenterofinterestPoint());
	/*camera.setCenterOfInterestPoint(Vec3f(charactermanager->getPlayer()->getPos().x - WorldScale*2.f, 
		charactermanager->getPlayer()->getPos().y / 1.5f + camerapos.y*WorldScale,
		charactermanager->getPlayer()->getPos().z));*/

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();
	gl::setMatrices(camera);

	gl::pushModelView();

	mapmanager.drawSky();
	//mapmanager.drawMap2d();
	
	mapchipmanager->draw();
	drawPlayer();
	charactermanager->draw();
	bulletmanager->draw();
	drawShiftFloorObject();
	effectmanager->draw();
	mapmanager.drawTexureObjct();
	
	//mapmanager.drawMap2dFront();

	
	gl::popModelView();
}

void GameMain::draw2D()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);

	gl::pushModelView();

	mainwindow->draw();

	gl::popModelView();
}

void GameMain::shift()
{
	if (!charactermanager->getPlayer()->getIsAlive()) {
		SceneManager::createScene(Title());
	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
}


void GameMain::shiftNextFloor()
{
	FadeM.StartFadeIn();
	isshiting = true;
}

void GameMain::shiftGoal()
{

}

void GameMain::ReCreateStage()
{
	if (isshiting&&FadeM.getIsfadeinEnd()) {
		mapmanager.ReadData(worldnum, stagenum, floornum);
		charactermanager->CreateEnemys(worldnum, stagenum, floornum);
		charactermanager->setBulletManagerPtrToEnemys();
		charactermanager->setEnemysAction();
		mapchipmanager->setup(worldnum, stagenum, floornum);
		charactermanager->getPlayer()->setPos(nextplayerpos);
		cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
		cameramanager->setMinValue(Vec2f(0, 0));
		cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
		cretateShiftFloorObject();
		isshiting = false;
		mainwindow->setup();
		FadeM.StartFadeOut(true);
	}
	
}

void GameMain::drawPlayer()
{
}

void GameMain::updatePlayer()
{
}

void GameMain::updateLinetoPlayer()
{
}

void GameMain::cretateShiftFloorObject()
{
	shiftfloorobjects.clear();
	std::string path = "Json/Stage/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum) +
		"/Floor" + std::to_string(floornum);
	JsonTree shiftfllorjson(loadAsset(path + "/shiftfloor.json"));

	for (int i = 0;i < shiftfllorjson.getNumChildren();i++) {
		JsonTree child = shiftfllorjson.getChild(i);
		Vec3f pos = JsonM.getVec3(child, "pos");
		Vec3f scale = JsonM.getVec3(child, "size");
		int next = child.getValueForKey<int>("next");
		Vec3f nextpos = JsonM.getVec3(child, "nextplayerpos");
		shiftfloorobjects.push_back(std::make_shared<ShiftFloorObject>(pos,scale, next,nextpos));
	}




	
}

void GameMain::updateShiftFloorObject()
{
	if (isshiting)return;
	for (int i = 0;i < shiftfloorobjects.size();i++) {
		if (KeyManager::getkey().isPress(KeyEvent::KEY_w)) {
			if (CollisionM.isBoxPoint(charactermanager->getPlayer()->getPos2f(),
				Vec2f(shiftfloorobjects[i]->getPos().x-shiftfloorobjects[i]->getSize().x / 2.f, shiftfloorobjects[i]->getPos().y- shiftfloorobjects[i]->getSize().y / 2.f),
				Vec2f(shiftfloorobjects[i]->getSize().x, shiftfloorobjects[i]->getSize().y))) {
				nextplayerpos = shiftfloorobjects[i]->getNextPlayerPos();
				floornum = shiftfloorobjects[i]->getNextFloorNum();
				shiftNextFloor();
			}
		}
	}
}

void GameMain::drawShiftFloorObject()
{
	for (int i = 0;i < shiftfloorobjects.size();i++) {
		shiftfloorobjects[i]->draw();
	}
}

void GameMain::playBGM()
{
	std::string path = "enjoy.wav";
	SoundM.PlayBGM(path);
	SoundM.SetLoopBGM(path, true);
}
