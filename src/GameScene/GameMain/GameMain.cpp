#include "GameMain.h"
#include"../../Input/KeyManager.h"
#include"../../Scene/SceneManager.h"
#include"../../GameScene/Title/Title.h"
#include"../../GameScene/StageSelect/StageSelect.h"
#include"../../Top/Top.h"
#include"../../Top/MyJson.h"
#include"../../Top/DrawManager.h"
#include"../../Top/DataManager.h"
#include"../../Top/TextureManager.h"
#include"../../Top/SoundManager.h"
#include"../../WorldObject/Player.h"
#include"../../WorldCreater/BulletManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldCreater/CameraMnager.h"
#include"../../Top/FadeManager.h"
#include"../../WorldObject/ShiftFloorObject.h"
#include"../../Top/DataManager.h"
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
	starteffect_isend = false;
	worldnum = DataM.getWorldNum();
	stagenum = DataM.getStageNum();
	floornum = 1;
	mapmanager.ReadData(worldnum, stagenum, 1);

	cameramanager = std::make_shared<CameraManager>();

	bulletmanager = std::make_shared<BulletManager>();
	charactermanager = std::make_shared<CharacterManager>();
	mapchipmanager = std::make_shared<MapChipManager>();
	effectmanager = std::make_shared<EffectManager>();
	mainwindow = std::make_shared<MainWindow>();


	charactermanager->setBulletManagerPointer(bulletmanager->getThisPointer());
	charactermanager->setEffectManagerPointer(effectmanager->getThisPointer());

	charactermanager->CreatePlayer(Vec3f(-22.0, 2, 0.0f)*WorldScale);
	nextplayerpos = Vec3f(-22.0, 2, 0.0f)*WorldScale;////
	charactermanager->CreateEnemys(worldnum, stagenum, floornum);//

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
	mapchipmanager->setup(worldnum, stagenum, floornum);

	

	cameramanager->setPlayerPos(charactermanager->getPlayer()->getPos());
	cameramanager->unitPrevCenterOfInterestPoint(charactermanager->getPlayer()->getPos());
	cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
	cameramanager->setMinValue(Vec2f(0, 0));
	cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
	cameramanager->update();

	FadeM.StartFadeOut(false);

	cretateShiftFloorObject();

	mainwindow->setSelectTextureNum(1);
	SoundM.CreateSE("stageclear.wav");
	SoundM.CreateSE("deathse.wav");
	SoundM.CreateSE("haretu.wav");
	SoundM.CreateSE("actionselectbegin.wav");
	TextureM.CreateTexture("UI/montaicon.png");
	TextureM.CreateTexture("UI/nisemonta.png");
	font = Font("Comic Sans MS", 65.0f);
	
	playBGM();

	charactermanager->update();

	bulletmanager->update();

	mapchipmanager->update();
}

void GameMain::update()
{
	isgoaleffecingend = false;

	if (FadeM.getIsfadeoutEnd() && (!starteffect_isend)) {
		information.setIsStageStart(true);
		starteffect_isend = true;
	}
	if (information.getIsEffecting()) {
		information.update();
	}
	
	if (!FadeM.getIsFading()&&(!isgoal)&&(!information.getIsEffecting())&& charactermanager->getPlayer()->getIsAlive()) {
		if (!charactermanager->getActionSelectMode()) {
			StartActionSelectMode();
		}
		
		if (!charactermanager->getActionSelectMode()) {
			charactermanager->update();

			bulletmanager->update();

			mapchipmanager->update();
		}
		
	}

	if (!charactermanager->getActionSelectMode()) {

		cameramanager->setPlayerPos(charactermanager->getPlayer()->getPos());
		cameramanager->setPlayerSpeed(charactermanager->getPlayer()->getSpeed());
		cameramanager->update();
		effectmanager->update();
		mainwindow->update();
		updateDeath();
		updateShiftFloorObject();
		updateGoal();
		ReCreateStage();
		DeathFadeInend();
	}
	else {
		charactermanager->updateActionSelectMode();
	}

	

}

void GameMain::draw()
{


	camera.setEyePoint(cameramanager->getSetEyePoint()+cameramanager->getSetEyePointTrance());
	camera.setCenterOfInterestPoint(cameramanager->getSetCenterofinterestPoint()+cameramanager->getSetCenterofinterestPointTrance());
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
	information.draw();
	if (isgoal) {
		information.drawClearTexture();
	}
	if (charactermanager->getActionSelectMode()) {
		charactermanager->drawActionSelectMode();
	}
	drawDeathBlackBox();
	gl::popModelView();
}

void GameMain::shift()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_t)) {
		SceneManager::createScene(Title());
	}
	if (FadeM.getIsfadeinEnd()&&isshiftstageselect) {
		DataM.setPrevScene(SceneType::GANEMAIN_SCENE);
		DataM.setNextScene(SceneType::STAGESELECT_SCENE);
		SceneManager::createScene(StageSelect());
	}
}


void GameMain::shiftNextFloor()
{
	FadeM.StartFadeIn();
	isshiting = true;
}

void GameMain::shiftGoal()
{
	isgoal = true;
	SoundM.FadeNowBGM(0.0f,0.5f);
	SoundM.PlaySE("stageclear.wav",0.5f);
}

void GameMain::ReCreateStage()
{
	if (isshiting&&FadeM.getIsfadeinEnd()) {
		bulletmanager->ClearBullets();
		mapmanager.ReadData(worldnum, stagenum, floornum);
		charactermanager->CreateEnemys(worldnum, stagenum, floornum);
		charactermanager->setBulletManagerPtrToEnemys();
		charactermanager->setEnemysAction();
		mapchipmanager->setup(worldnum, stagenum, floornum);
		charactermanager->getPlayer()->setPos(nextplayerpos);
		charactermanager->getPlayer()->setSpeed(Vec3f(0,0,0));
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
	JsonTree bgm(loadAsset("Json/bgm.json"));
	bgmname = bgm.getValueForKey<std::string>(std::to_string(worldnum) + "_" + std::to_string(stagenum)) + ".wav";
	SoundM.PlayBGM(bgmname,0.4f);
	SoundM.SetLoopBGM(bgmname, true);
}

void GameMain::updateGoal()
{
	if (isgoal) {
		information.updateClearTexture();
		if (information.getGoalEffectEnd()) {
			isgoaleffecingend = true;
		}
	}
	if (isgoaleffecingend&&(!FadeM.getIsFading())) {
		FadeM.StartFadeIn();
		isshiftstageselect = true;
	}
}

void GameMain::updateDeath()
{
	if ((!charactermanager->getPlayer()->getIsAlive())) {
		cameramanager->updateCameraTrance();
		charactermanager->updatePlayerDeath();
	}
	if (cameramanager->getDeathCameraEnd()) {
		SoundM.PlaySE("deathse.wav",0.5f);
		isdeathblackboxstart = true;
	}
	updateDeathBlackBox();
	updateZanki();
}

void GameMain::drawDeathBlackBox()
{
	if (!isdeathblackboxstart)return;
	DrawM.drawBox(Vec2f(WINDOW_WIDTH/2.f,WINDOW_HEIGHT/2.f),deathblackboxsize,deathblackboxangle,ColorA(0,0,0,1));
	drawZankiIcon();
}

void GameMain::drawZankiIcon()
{
	if (EasingManager::tCountEnd(deathblackbox_t)){
		Vec2f iconpos = Vec2f(WINDOW_WIDTH/2.f-100.f,WINDOW_HEIGHT/2.f);
		Vec2f iconsize = Vec2f(200,200);
		DrawM.drawFont(u8"~", iconpos + Vec2f(100, -70), Vec2f(2, 2), 0.0f, ColorA(1, 1, 1, zankicolor_t), font);
		if (mainwindow->getZankiNum() >= 0) {
			DrawM.drawTextureBox(iconpos, iconsize, 0.0f, TextureM.getTexture("UI/montaicon.png"), ColorA(1, 1, 1, zankicolor_t));
			DrawM.drawFont(std::to_string(mainwindow->getZankiNum()), iconpos + Vec2f(200, -70 + zanki_trancepos_y), Vec2f(2, 2)*zankisizerate, 0.0f, ColorA(1, 1, 1, zankicolor_t), font);
		}
		else {
			DrawM.drawTextureBox(iconpos, iconsize, 0.0f, TextureM.getTexture("UI/nisemonta.png"), ColorA(1, 1, 1, zankicolor_t));
			
		}
	
	}
}

void GameMain::updateDeathBlackBox()
{
	if (EasingManager::tCountEnd(zanki_delay_t))return;
	if (isdeathblackboxstart) {
		EasingManager::tCount(deathblackbox_t,2.0f);
		deathblackboxsize.x = EasingQuadIn(deathblackbox_t, 0.0f, WINDOW_WIDTH);
		deathblackboxsize.y = EasingQuadOut(deathblackbox_t, 0.0f, WINDOW_HEIGHT);
		deathblackboxangle = EasingQuadIn(deathblackbox_t, 0.0f, 720.f);
	}
	
	if (EasingManager::tCountEnd(deathblackbox_t)) {
		EasingManager::tCount(zankicolor_t, 1.0f);
		if (EasingManager::tCountEnd(zankicolor_t)) {
			EasingManager::tCount(zanki_delay_t, 1.0f);
			if (EasingManager::tCountEnd(zanki_delay_t)) {
				mainwindow->setZankiNum(mainwindow->getZankiNum()-1);
				SoundM.PlaySE("haretu.wav");
			}
		}
	}
}

void GameMain::updateZanki()
{
	if (EasingManager::tCountEnd(zanki_size_t))return;
	if (EasingManager::tCountEnd(zanki_delay_t)) {
		EasingManager::tCount(zanki_size_t,0.3f);
		zankisizerate = EasingReturn(zanki_size_t,1.0f,0.3f);
		zanki_trancepos_y = EasingReturn(zanki_size_t, 0, -100.f);
		if (EasingManager::tCountEnd(zanki_size_t)) {

			FadeM.StartFadeIn();
			isshiftdeath = true;
			if (mainwindow->getZankiNum() < 0) {
				isshiftstageselect = true;
			}
			//////////////////////////
	
		}
	}
}

void GameMain::DeathFadeInend()
{
	if (isshiftdeath&&FadeM.getIsfadeinEnd()) {
		if (mainwindow->getZankiNum() >= 0) {

			FadeM.StartFadeOut(false);
			isshiftdeath = false;
			   playerdead = false;
			isdeathblackboxstart = false;
			deathblackbox_t = 0.0f;
			zankicolor_t = 0.0f;
			zanki_delay_t = 0.0f;
			zanki_size_t = 0.0f;
			zankisizerate = 1.0f;
			zanki_trancepos_y = 0.0f;
			bulletmanager->ClearBullets();
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
			charactermanager->getPlayer()->setSpeed(Vec3f(0, 0, 0));
			charactermanager->getPlayer()->setHp(charactermanager->getPlayer()->getMaxHp());
			charactermanager->getPlayer()->RsetDeathColorT();
			charactermanager->getPlayer()->setIsinvincible(false);
			charactermanager->getPlayer()->setIsStun(false);
			cameramanager->ResetT();
			playBGM();
		}
	}
}

void GameMain::StartActionSelectMode()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_i)) {
		if (charactermanager->getPlayer()->getCanJump()) {
			charactermanager->setActionSelectMode(true);
			SoundM.FadeNowBGM(0.05f, 0.5f, false);
			SoundM.PlaySE("actionselectbegin.wav");
		}
	}
	
}
