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
#include"../../WorldCreater/ShadowManager.h"
#include"../../WorldCreater/EffectManager.h"
#include"../../WorldCreater/CameraMnager.h"
#include"../../Top/FadeManager.h"
#include"../../WorldObject/ShiftFloorObject.h"
#include"../../Top/DataManager.h"
#include"../../Top/MyJson.h"
#include"../../Top/CollisionManager.h"
#include"../../WorldObject/Bullet/BulletBase.h"
#include"../../WorldObject/ItemObject.h"
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
	uicreater.CreateUI("Json/UI/gamemain.json");
	isshiting = false;
	starteffect_isend = false;
	worldnum = DataM.getWorldNum();
	stagenum = DataM.getStageNum();
	DataM.setSelectActionName("slime");
	floornum = 1;
	mapmanager.ReadData(worldnum, stagenum, floornum);
	cameramanager = std::make_shared<CameraManager>();

	bulletmanager = std::make_shared<BulletManager>();
	charactermanager = std::make_shared<CharacterManager>();
	mapchipmanager = std::make_shared<MapChipManager>();
	effectmanager = std::make_shared<EffectManager>();
	itemmanager = std::make_shared<ItemManager>();
	shadowmanager = std::make_shared<ShadowManager>();
	mainwindow = std::make_shared<MainWindow>();


	charactermanager->setBulletManagerPointer(bulletmanager->getThisPointer());
	charactermanager->setEffectManagerPointer(effectmanager->getThisPointer());
	charactermanager->setShadowManagerPointer(shadowmanager->getThisPtr());
	charactermanager->setCameraManagerPointer(cameramanager->getThisPtr());
	charactermanager->setMapChipManagerPointer(mapchipmanager->getThisPtr());
	setStartPos();
	charactermanager->CreatePlayer(nextplayerpos);

	charactermanager->CreateEnemys(worldnum, stagenum, floornum);//
	charactermanager->CreateBoss(worldnum, stagenum, floornum);
	charactermanager->setBulletManagerPtrToPlayer();
	charactermanager->setBulletManagerPtrToEnemys();
	charactermanager->setBulletManagerPtrToBoss();
	charactermanager->setCameratManagerPtrToBoss();
	charactermanager->setEffectManagerPtrToBoss();
	charactermanager->setMapChipManagerPtrToBoss();
	charactermanager->setMainWindowPointer(mainwindow->getThisPtr());

	charactermanager->setPlayerAction(DataM.stringToActionType(DataM.getSelectActionName()));
	charactermanager->getPlayer()->Reset(nextplayerrotate);///
	charactermanager->setEnemysAction();
	charactermanager->setBossAction();
	bulletmanager->setCharacterManagerPtr(charactermanager->getThisPointer());
	bulletmanager->setEffectManagerPtr(effectmanager->getThisPointer());
	bulletmanager->setMainWindowPtr(mainwindow->getThisPtr());
	
	mapchipmanager->setBulletManagerPointer(bulletmanager->getThisPointer());
	mapchipmanager->setCharacterManagerPointer(charactermanager->getThisPointer());
	mapchipmanager->setEffectManagerPointer(effectmanager->getThisPointer());

	mainwindow->setCharacterManagerPtr(charactermanager->getThisPointer());
	mainwindow->setItemManagerPtr(itemmanager->getThisPointer());

	mapchipmanager->setGoal(std::bind(&GameMain::shiftGoal, this));
	mapchipmanager->setup(worldnum, stagenum, floornum);
	
	itemmanager->SetCharacterManagerPtr(charactermanager->getThisPointer());
	itemmanager->SetEffectManagerPtr(effectmanager->getThisPointer());
	itemmanager->SetBulletManagerPtr(bulletmanager->getThisPointer());
	itemmanager->CreateItem(worldnum,stagenum,floornum);
	
	shadowmanager->setMapChipManager(mapchipmanager->getThisPtr());
	
	cameramanager->setEffectManagerPtr(effectmanager->getThisPointer());
	cameramanager->unitPrevCenterOfInterestPoint(charactermanager->getPlayer()->getPos());
	cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
	cameramanager->setMinValue(Vec2f(0, 0));
	cameramanager->setPlayerPtr(charactermanager->getPlayer()->getThisPointer());
	cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
	cameramanager->update();

	FadeM.StartFadeOut(false);

	cretateShiftFloorObject();
	
	mainwindow->setSelectTextureNum(1);

	createAsset();

	playBGM();

	charactermanager->update(camera);
	
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
			if(stagenum==4&&(floornum==2))
			mapmanager.rotateSky(Vec3f(0,0.12,0));
			charactermanager->update(camera);

			bulletmanager->update();

			mapchipmanager->update();

			itemmanager->update(camera);
		}
		
	}

	if (!charactermanager->getActionSelectMode()) {
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
		if (charactermanager->getIsBegin() || charactermanager->getIsEnd()) {
			float rate = 0.0f;
			float end = 10.0f;
			if (charactermanager->getIsBegin()) {
				rate =EasingLinear(charactermanager->getBackGround_T(), 1.0f, end);
			}
			if (charactermanager->getIsEnd()) {
				rate = EasingLinear(charactermanager->getBackGround_T(), end, 1.0f);
			}
			charactermanager->setActionSelectBackGround(ofScrean(rate));
		}
		charactermanager->updateActionSelectMode();
		if (KeyManager::getkey().isPush(KeyEvent::KEY_ESCAPE) && (!FadeM.getIsFading())) {
			isshiftstageselect = true;
			FadeM.StartFadeIn();
			SoundM.FadeNowBGM(0.0f, 0.5f, true);
		}
	}

	if (cameramanager->getIsBossDelayEnd()&&(!isbossdeathshift)) {
		isbossdeathshift = true;
		FadeM.StartFadeIn();
		DataM.saveStageData(worldnum, stagenum, true);
	}

}

void GameMain::draw()
{

	camera.setEyePoint(cameramanager->getSetEyePoint()+cameramanager->getSetEyePointTrance()+
		cameramanager->getShakeCenterPoint());
	camera.setCenterOfInterestPoint(cameramanager->getSetCenterofinterestPoint()
		+cameramanager->getSetCenterofinterestPointTrance()+
		cameramanager->getShakeCenterPoint());

	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();

	








	gl::setMatrices(camera);

	gl::pushModelView();

	if (!charactermanager->getActionSelectMode()) {

		gl::disable(GL_FOG);
		mapmanager.drawSky();
		
		//mapmanager.drawMap2d();

		gl::enable(GL_FOG);
		// モード: GL_LINEAR、GL_EXP、GL_EXP2のいずれか
		glFogi(GL_FOG_MODE, GL_LINEAR);

		// GL_EXP、GL_EXP2で使う密度係数
		glFogf(GL_FOG_DENSITY, 1.0f);

		// GL_LINEARで使用する近景位置
		glFogf(GL_FOG_START, 7*WorldScale);
		// GL_LINEARで使用する遠景位置
		glFogf(GL_FOG_END, 100 * WorldScale);

		// 色指定
		GLfloat fog_color[] = { 1.0f, 1.0f, 1.0f, 0.5f };
		glFogfv(GL_FOG_COLOR, fog_color);




		



		mapchipmanager->draw();
		charactermanager->draw(camera);
		bulletmanager->draw();
		itemmanager->draw();

		drawShiftFloorObject();
		effectmanager->draw(camera);
		
		mapmanager.drawTexureObjct(camera);
		drawShadow();

	
		//mapmanager.drawMap2dFront();
	}
	

	
	gl::popModelView();


}

void GameMain::draw2D()
{
	gl::disableDepthRead();
	gl::disableDepthWrite();
	gl::disable(GL_CULL_FACE);
	gl::setMatrices(ortho);

	gl::pushModelView();
	if (charactermanager->getActionSelectMode()) {
		charactermanager->drawActionSelecBackGround();
	}
	
	mainwindow->draw();
	uicreater.draw();
	effectmanager->draw2D(camera);
	charactermanager->drawBossHpGage();
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
	if (FadeM.getIsfadeinEnd()&&isshiftstageselect) {
		DataM.setPrevScene(SceneType::GANEMAIN_SCENE);
		DataM.setNextScene(SceneType::STAGESELECT_SCENE);
		SceneManager::createScene(StageSelect());
	}
	if (FadeM.getIsfadeinEnd() && isbossdeathshift) {
		effectmanager->clearEffects();
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
	DataM.saveStageData(worldnum, stagenum, true);
	itemmanager->saveItems(worldnum,stagenum);
}

void GameMain::ReCreateStage()
{
	if (isshiting&&FadeM.getIsfadeinEnd()) {
		bulletmanager->ClearBullets();
		effectmanager->clearEffects();
		mapmanager.ReadData(worldnum, stagenum, floornum);
		charactermanager->CreateEnemys(worldnum, stagenum, floornum);
		charactermanager->CreateBoss(worldnum, stagenum, floornum);
		charactermanager->setBulletManagerPtrToEnemys();
		charactermanager->setBulletManagerPtrToBoss();
		charactermanager->setEffectManagerPtrToBoss();
		charactermanager->setMapChipManagerPtrToBoss();
		charactermanager->setCameratManagerPtrToBoss();
		charactermanager->setEnemysAction();
		charactermanager->setBossAction();
		mapchipmanager->setup(worldnum, stagenum, floornum);
		charactermanager->getPlayer()->setPos(nextplayerpos);
		charactermanager->getPlayer()->Reset(nextplayerrotate);
		itemmanager->CreateItem(worldnum, stagenum, floornum);
		cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
		cameramanager->setMinValue(Vec2f(0, 0));
		cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
		cretateShiftFloorObject();
		isshiting = false;
		mainwindow->setup();
		FadeM.StartFadeOut(true);
	}
	
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
		Vec3f pos = JsonM.getVec3(child, "pos")*WorldScale;
		Vec3f scale = JsonM.getVec3(child, "size")*WorldScale;
		int next = child.getValueForKey<int>("next");
		Vec3f playerpos = JsonM.getVec3(child, "nextplayerpos")*WorldScale;
		Vec3f playerrotate= JsonM.getVec3(child, "nextplayerrotate");
		shiftfloorobjects.push_back(std::make_shared<ShiftFloorObject>(pos,scale, next,playerpos, playerrotate));
	}




	
}

void GameMain::updateShiftFloorObject()
{
	if (isshiting)return;
	if (FadeM.getIsFading())return;
	for (int i = 0;i < shiftfloorobjects.size();i++) {
		if (KeyManager::getkey().isPress(KeyEvent::KEY_w)) {
			if (CollisionM.isBoxPoint(charactermanager->getPlayer()->getPos2f(),
				Vec2f(shiftfloorobjects[i]->getPos().x-shiftfloorobjects[i]->getSize().x / 2.f, shiftfloorobjects[i]->getPos().y- shiftfloorobjects[i]->getSize().y / 2.f),
				Vec2f(shiftfloorobjects[i]->getSize().x, shiftfloorobjects[i]->getSize().y))) {
				nextplayerpos = shiftfloorobjects[i]->getNextPlayerPos();
				nextplayerrotate = shiftfloorobjects[i]->getNextPlayerRotate();
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
		DrawM.drawFont(u8"×", iconpos + Vec2f(100, -70), Vec2f(2, 2), 0.0f, ColorA(1, 1, 1, zankicolor_t), font);
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
		if (mainwindow->getZankiNum() >= 0){
			playBGM();
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
			effectmanager->clearEffects();
			mapmanager.ReadData(worldnum, stagenum, floornum);
			charactermanager->CreateEnemys(worldnum, stagenum, floornum);
			charactermanager->CreateBoss(worldnum, stagenum, floornum);
			charactermanager->setBulletManagerPtrToEnemys();
			charactermanager->setBulletManagerPtrToBoss();
			charactermanager->setCameratManagerPtrToBoss();
			charactermanager->setEffectManagerPtrToBoss();
			charactermanager->setMapChipManagerPtrToBoss();
			charactermanager->setEnemysAction();
			charactermanager->setBossAction();
			mapchipmanager->setup(worldnum, stagenum, floornum);
			charactermanager->getPlayer()->setPos(nextplayerpos);
			itemmanager->CreateItem(worldnum, stagenum, floornum);
			cameramanager->setMaxValue(mapchipmanager->getChipsSize()*WorldScale);
			cameramanager->setMinValue(Vec2f(0, 0));
			cameramanager->setCameraUpdateType(cameramanager->JsonReadCameraType(worldnum, stagenum, floornum));
			cretateShiftFloorObject();
			isshiting = false;
			mainwindow->setup();
			charactermanager->getPlayer()->setSpeed(Vec3f(0, 0, 0));
			charactermanager->getPlayer()->setHp(charactermanager->getPlayer()->getMaxHp());
			charactermanager->getPlayer()->RsetDeathColorT();
			charactermanager->getPlayer()->Reset(nextplayerrotate);
			cameramanager->ResetT();
			
		}
	}
}

void GameMain::StartActionSelectMode()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_i)&&(!charactermanager->getIsBossDeath())) {
		if (charactermanager->getPlayer()->getCanJump()) {
			charactermanager->setActionSelectMode(true);
			SoundM.FadeNowBGM(0.05f, 0.5f, false);
			SoundM.PlaySE("actionselectbegin.wav");
			charactermanager->setActionSelectBackGround(ofScrean(1.0f));
		}
	}
	
}

void GameMain::drawShadow()
{
	gl::enableDepthWrite(false);
	for (auto it : charactermanager->getEnemys()) {
		Vec2f screen_position = camera.worldToScreen(it->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it->getPos(), it->getScale());
		}
	}
	for (auto it : bulletmanager->getPlayerBullets()) {
		if (it->getPos().z >= WorldScale*8.f)continue;
		Vec2f screen_position = camera.worldToScreen(it->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it->getPos(), it->getScale());
		}
	}
	for (auto it : bulletmanager->getEnemyBullets()) {
		if (it->getPos().z >= WorldScale*8.f)continue;
		Vec2f screen_position = camera.worldToScreen(it->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it->getPos(), it->getScale());
		}
	}
	for (auto it : bulletmanager->getBossBullets()) {
		Vec2f screen_position = camera.worldToScreen(it->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it->getPos(), it->getScale());
		}
	}
	for (auto it : itemmanager->getIteObjects()) {
		if (it.getPos().z >= WorldScale*8.f)continue;
		if (it.getIsGet())continue;
		Vec2f screen_position = camera.worldToScreen(it.getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it.getPos(), it.getScale());
		}
	}
	for (auto it : charactermanager->getBoss()) {
		Vec2f screen_position = camera.worldToScreen(it->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(0, 0), Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT))) {
			shadowmanager->draw(it->getPos(), it->getScale());
		}
	}
	shadowmanager->draw(charactermanager->getPlayer()->getPos(), charactermanager->getPlayer()->getScale());
	gl::enableAlphaBlending();
	gl::enableDepthWrite(true);
}

void GameMain::setStartPos()
{
	JsonTree set(loadAsset("Json/Stage/World"+std::to_string(worldnum)+"/startpos.json"));
	JsonTree child = set.getChild(stagenum - 1);
	nextplayerpos = JsonM.getVec3(child,"pos")*WorldScale;
	nextplayerrotate = JsonM.getVec3(child, "rotate");
}

void GameMain::createAsset()
{
	SoundM.CreateSE("stageclear.wav");
	SoundM.CreateSE("deathse.wav");
	SoundM.CreateSE("haretu.wav");
	SoundM.CreateSE("actionselectbegin.wav");
	TextureM.CreateTexture("UI/montaicon.png");
	TextureM.CreateTexture("UI/nisemonta.png");
	font = Font("Comic Sans MS", 65.0f);
}

ci::gl::Texture GameMain::ofScrean(const float rate)
{
	ci::gl::Fbo fbo;
	fbo = gl::Fbo(WINDOW_WIDTH / rate, WINDOW_HEIGHT / rate, true, true, true);
	fbo.bindFramebuffer();
	gl::setViewport(fbo.getBounds());

	gl::clear(Color(0, 0, 0));
	gl::enable(GL_CULL_FACE);
	gl::enableDepthRead();
	gl::enableDepthWrite();
	gl::enableAlphaBlending();
	gl::setMatrices(camera);
	//mapmanager.drawMap2d();
	gl::disable(GL_FOG);
	mapmanager.drawSky();

	//mapmanager.drawMap2d();

	gl::enable(GL_FOG);
	// モード: GL_LINEAR、GL_EXP、GL_EXP2のいずれか
	glFogi(GL_FOG_MODE, GL_LINEAR);

	// GL_EXP、GL_EXP2で使う密度係数
	glFogf(GL_FOG_DENSITY, 1.0f);

	// GL_LINEARで使用する近景位置
	glFogf(GL_FOG_START, 7 * WorldScale);
	// GL_LINEARで使用する遠景位置
	glFogf(GL_FOG_END, 100 * WorldScale);

	// 色指定
	GLfloat fog_color[] = { 1.0f, 1.0f, 1.0f, 0.5f };
	glFogfv(GL_FOG_COLOR, fog_color);

	mapchipmanager->draw();
	charactermanager->draw(camera);
	bulletmanager->draw();
	itemmanager->draw();
	drawShiftFloorObject();
	effectmanager->draw(camera);

	mapmanager.drawTexureObjct(camera);
	drawShadow();
	// 描画対象を元に戻す
	gl::Fbo::unbindFramebuffer();
	gl::setViewport(getWindowBounds());

	return fbo.getTexture();
}
