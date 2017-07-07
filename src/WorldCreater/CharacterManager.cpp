#include "CharacterManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../WorldObject/Player.h"
#include"../CharacterAction/ActionBase.h"
#include"../WorldObject/Enemy.h"
#include"../WorldObject/Boss.h"
#include"../Top/Top.h"
#include"../Top/CollisionManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldCreater/ShadowManager.h"
#include"../WorldObject/Effect/EffectExplosion.h"
#include"../WorldObject/Effect/EffectStar.h"
#include"../WorldObject/Effect/EffectFlashBack.h"
#include"../Top/EasingManager.h"
#include"../Top/SoundManager.h"
#include"../Top/TextureManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldCreater/CameraMnager.h"
#include"../Input/KeyManager.h"
#include"../Top/MyJson.h"
#include"../Top/DataManager.h"
#include"../UI/MainWindow.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;
CharacterManager::CharacterManager()
{
	createAsset();
	selectaction = std::make_shared<SelectAction>();
}

void CharacterManager::CreatePlayer(ci::Vec3f pos)
{
	player = std::make_shared<Player>(pos,ActionType::NONE,shadowmanager->getThisPtr());
}

void CharacterManager::setBulletManagerPointer(BulletManager * _bulletmanager)
{
	bulletmanager = _bulletmanager;
}

void CharacterManager::setEffectManagerPointer(EffectManager * _effectmanager)
{
	effectmanager = _effectmanager;
}

void CharacterManager::setShadowManagerPointer(ShadowManager * _shadowmanager)
{
	shadowmanager = _shadowmanager;
}

void CharacterManager::setCameraManagerPointer(CameraManager * _cameramanager)
{
	cameramanager = _cameramanager;
}

void CharacterManager::setMapChipManagerPointer(MapChipManager * _mapchipmanager)
{
	mapchipmanager = _mapchipmanager;
}

void CharacterManager::setMainWindowPointer(MainWindow * _mainwindow)
{
	mainwondow = _mainwindow;
}

void CharacterManager::setBulletManagerPtrToPlayer()
{
	player->SetBulletManagerPointer(bulletmanager);
}

void CharacterManager::setBulletManagerPtrToEnemys()
{
	for (auto& itr : enemys) {
		itr->SetBulletManagerPointer(bulletmanager);
	}
}

void CharacterManager::setBulletManagerPtrToBoss()
{
	for (auto& itr :boss) {
		itr->SetBulletManagerPointer(bulletmanager);
	}
}

void CharacterManager::setCameratManagerPtrToBoss()
{
	for (auto& itr : boss) {
		itr->setCameraManagerPointer(cameramanager);
	}
}

void CharacterManager::setEffectManagerPtrToBoss()
{
	for (auto& itr : boss) {
		itr->SetEffectManagerPointer(effectmanager);
	}
}

void CharacterManager::setMapChipManagerPtrToBoss()
{
	for (auto& itr : boss) {
		itr->setMapChipManagerPointer(mapchipmanager);
	}
}

void CharacterManager::setPlayerAction(ActionType type)
{
	player->setActionType(type);
	player->decideAction(type);
	player->setCharacterManagerPointer(this);
}

void CharacterManager::setEnemysAction()
{
	for (auto& itr : enemys) {
		itr->decideAction(itr->getActiontype());
		itr->setCharacterManagerPointer(this);
	}
}

void CharacterManager::setBossAction()
{
	for (auto& itr : boss) {
		itr->decideAction(itr->getActiontype());
		itr->setCharacterManagerPointer(this);
		bosshpbuff = itr->getMaxHp();
	}
}


void CharacterManager::update(const ci::CameraPersp camera)
{
	if (getIsBossFloor()) {
		if ((isbossbegineffectend)&&(!isbossdeath)) {
			player->update();
		}
	}
	else {
		player->update();
	}
	
	for (auto itr = enemys.begin();itr != enemys.end();) {
		if ((*itr)->getIsAlive()) {
			//ci::app::console() << (*itr)->getHp() << std::endl;
			itr++;
		}
		else
		{
			(*itr)->updateDeath(0.75f);
		
			if ((*itr)->updateDeathEnd()) {
				//effectmanager->CreateEffect(EffectExplosion((*itr)->getPos(), (*itr)->getScale(), ci::Vec3f(0, 0, 0)));
				effectmanager->CreateEffect2D(EffectStar((*itr)->getPos(), (*itr)->getScale(),(*itr)->getUniqueColor()));
				itr = enemys.erase(itr);
				SoundM.PlaySE("enemy_die.wav", 0.5f);
			}
			else {
				itr++;
			}

		}
	}
	for (auto itr = boss.begin();itr != boss.end();) {
		if ((*itr)->getIsBeginEffectEnd()) {
			isbossbegineffectend = true;
		}
		if ((*itr)->getIsAlive()) {
			//ci::app::console() << (*itr)->getHp() << std::endl;
			itr++;
			
			
		}
		else
		{
			(*itr)->updateDeath(1.5f);
			bulletmanager->ClearBullets();
			if ((*itr)->updateDeathEnd()&&(!isbossdeath)) {
				isbossdeath = true;
				bossdeatheffecte_t = 0.0f;
				isbossdeatheffect = true;
				isbossdeatheffectend = false;
				SoundM.FadeNowBGM(0.0f,1.0f);
				effectmanager->CreateEffect2D(EffectFlashBack(1.0f, ColorA(1, 1, 1, 1)));
			}
			
			itr++;
		}
		
	}
	for (auto& itr : enemys) {
		if ((itr)->getIsAlive()) {
			Vec2f screen_position = camera.worldToScreen(itr->getPos(),
				WINDOW_WIDTH, WINDOW_HEIGHT);
			if (CollisionM.isBoxPoint(screen_position, Vec2f(-WINDOW_WIDTH*0.2f, -WINDOW_HEIGHT*0.2f), Vec2f(WINDOW_WIDTH*1.4f, WINDOW_HEIGHT*1.4f))) {
				itr->update();
			}
			
		}
	}
	for (auto& itr : boss) {
		if ((itr)->getIsAlive()) {
			itr->update();
		}
	}

	updatebossGage();
	CollisionPlayerToEnemy();
	CollisionPlayerToBoss();
	if (isbossdeatheffect) {
		EasingManager::tCount(bossdeatheffecte_t, 1.0f);
		if (bossdeatheffecte_t >= 0.5f&&(!ismove)) {
			ismove = true;
			SoundM.PlaySE("rope.wav");
			cameramanager->setCameraUpdateType(BOSS_EFFECT_END);
			player->setPos(Vec3f(-11.25*WorldScale, 2 * WorldScale, 0));
			player->Reset(Vec3f(0, 0, 0));
			player->setRotate(Vec3f(0, 225, 0));
			player->setColor(player->getDefaultColor());
			cameramanager->Shake(50, 5.f);
			
			for (auto& itr : boss) {
				itr->setPos(Vec3f(-11.25*WorldScale,5.f*WorldScale,35.f*WorldScale));
				itr->setRotate(Vec3f(0,180,0));
			}
			
		}
	}

}

void CharacterManager::draw(const ci::CameraPersp camera)
{
	player->draw();
	for (auto& itr : enemys) {
		Vec2f screen_position = camera.worldToScreen(itr->getPos(),
			WINDOW_WIDTH, WINDOW_HEIGHT);
		if (CollisionM.isBoxPoint(screen_position, Vec2f(-WINDOW_WIDTH*0.2f, -WINDOW_HEIGHT*0.2f), Vec2f(WINDOW_WIDTH*1.4f, WINDOW_HEIGHT*1.4f))) {
			itr->draw();
		}
	}
	for (auto& itr : boss) {
		itr->draw();
	}
}


void CharacterManager::CreateEnemys(const int worldnum, const int stagenum, const int floornum)
{
	enemys.clear();
	std::string path = "Json/Stage/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum) +
		"/Floor" + std::to_string(floornum);
	JsonTree enemyjson(loadAsset(path + "/enemy.json"));


	for (int i = 0;i < enemyjson.getNumChildren();i++) {
		JsonTree child = enemyjson.getChild(i);
		Vec3f pos = JsonM.getVec3(child, "pos")*WorldScale;
		std::string enemytype = child.getValueForKey<std::string>("enemytype");
		enemys.push_back(std::make_shared<Enemy>(pos,DataM.stringToActionType(enemytype), i + 1));
	}
}

void CharacterManager::CreateBoss(const int worldnum, const int stagenum, const int floornum)
{
	boss.clear();
	bossgage_t = 0.0f;
	isbossdeath = false;
	isbossbegineffectend = false;
	isbossfloor = false;
	isfirstgage = true;
	bossdeatheffecte_t = 0.0f;
	isbossdeatheffect = false;
	isbossdeatheffectend = false;

	bossgagebeginrate = 0.0f;
	bossgagerate = 0.0f;
	bossgageendrate = 1.0f;



	std::string path = "Json/Stage/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum) +
		"/Floor" + std::to_string(floornum);
	JsonTree bossjson(loadAsset(path + "/boss.json"));


	for (int i = 0;i <bossjson.getNumChildren();i++) {
		JsonTree child = bossjson.getChild(i);
		Vec3f pos = JsonM.getVec3(child, "pos")*WorldScale;
		std::string enemytype = child.getValueForKey<std::string>("enemytype");
		boss.push_back(std::make_shared<Boss>(pos, DataM.stringToActionType(enemytype), i + 1));
		isbossfloor = true;
	}
}

CharacterManager * CharacterManager::getThisPointer()
{
	return this;
}

void CharacterManager::updatePlayerDeath()
{
	player->updateDeath(1.5f);
}

std::shared_ptr<CharacterBase> CharacterManager::getPlayer()
{
	return player;
}

std::list<std::shared_ptr<CharacterBase>>& CharacterManager::getEnemys()
{
	return enemys;
}

std::list<std::shared_ptr<CharacterBase>>& CharacterManager::getBoss()
{
	return boss;
}

void CharacterManager::setActionSelectMode(const bool is)
{
	actionselectmode = is;
}

bool CharacterManager::getActionSelectMode()
{
	return actionselectmode;
}

void CharacterManager::updateActionSelectMode()
{
	if (isbeginselectmode) {
		EasingManager::tCount(background_t,0.3f);
		backgroundsize.x = EasingQuadOut(background_t, 0.f, WINDOW_WIDTH);
		backgroundsize.y = EasingQuadOut(background_t, 0.f, WINDOW_HEIGHT);
		if (EasingManager::tCountEnd(background_t)) {
			isbeginselectmode = false;
			background_t = 0.0f;
		}
	}
	if (isendselectmode) {
		EasingManager::tCount(background_t, 0.3f);
		backgroundsize.x = EasingQuadIn(background_t, WINDOW_WIDTH, 0.0f);
		backgroundsize.y = EasingQuadIn(background_t, WINDOW_HEIGHT, 0.0f);
		if (EasingManager::tCountEnd(background_t)) {
			isendselectmode = false;
			isbeginselectmode = true;
			actionselectmode = false;
			SoundM.FadeNowBGM(SoundM.getPlayStartGain(),0.5f,false);
			background_t = 0.0f;
		}
	}
	if ((!isbeginselectmode)&&(!isendselectmode)) {
		if (KeyManager::getkey().isPush(KeyEvent::KEY_l)) {
			////////////////////////////////ここでアクション変更
			SelectPlayerFolm(DataM.stringToActionType(getActionName()));
			mainwondow->setSelectTextureNum(getPlayTextureNum());
			isendselectmode = true;
			SoundM.PlaySE("actionselectend.wav");
		}
	}
	if ((!isbeginselectmode) && (!isendselectmode)) {
		selectaction->update();
	}
}

void CharacterManager::drawActionSelectMode()
{
	if (actionselectmode) {
		float alfa = 0.2f;
		DrawM.drawBoxEdge(Vec2f(0, WINDOW_HEIGHT), Vec2f(backgroundsize.x,-backgroundsize.y), ColorA(1, 0, 0, alfa));
		DrawM.drawBoxEdge(Vec2f(WINDOW_WIDTH,0), Vec2f(-backgroundsize.x,backgroundsize.y), ColorA(0, 1, 0, alfa));
		DrawM.drawBoxEdge(Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT), -backgroundsize, ColorA(0, 0, 1, alfa));
		DrawM.drawBoxEdge(Vec2f(0, 0), backgroundsize, ColorA(0, 0, 0, alfa));
		if ((!isbeginselectmode) && (!isendselectmode)) {
			selectaction->draw();
		}
	}
	
}

void CharacterManager::drawActionSelecBackGround()
{
	Vec2f pos=Vec2f(WINDOW_WIDTH/2.f,WINDOW_HEIGHT/2.f);
	Vec2f size = Vec2f(WINDOW_WIDTH, WINDOW_HEIGHT);
	DrawM.drawTextureBox(pos,Vec2f(size.x,-size.y),0.0f,background,ColorA(1,1,1,1));
}

void CharacterManager::setActionSelectBackGround(const ci::gl::Texture & tex)
{
	background = tex;
}

void CharacterManager::drawBossHpGage()
{
	if (!isbossbegineffectend)return;
	for (auto& itr : boss) {
		Vec2f pos = Vec2f(1500, 600);
		Vec2f size = Vec2f(50, -500);
		float hprate = (float(itr->getHp()) / float(itr->getMaxHp()));
		DrawM.drawBoxEdge(pos + Vec2f(-5, 5), size + Vec2f(10, -10), ColorA(1, 1, 1, 1));
		DrawM.drawBoxEdge(pos, Vec2f(size.x, size.y), ColorA(0, 0, 0, 1));
		if (isfirstgage) {
			DrawM.drawBoxEdge(pos, Vec2f(size.x, size.y*bossgagerate), ColorA(0, 1, 0, 1));
		}
		else {
			DrawM.drawBoxEdge(pos, Vec2f(size.x, size.y*bossgagerate), ColorA(0.5, 0.5, 0.5, 1));
			DrawM.drawBoxEdge(pos, Vec2f(size.x, hprate*size.y), ColorA(hprate > 0.5f ? 0 : 1, hprate > 0.33f ? 1 : 0, 0, 1));
		}
		DrawM.drawTextureBoxEdge(Vec2f(pos.x-5,35), Vec2f(60,60), TextureM.getTexture("UI/dokuro.png"),ColorA(1, 1, 1, 1));
	}
	
}

float CharacterManager::getBackGround_T()
{
	return background_t;
}

bool CharacterManager::getIsBegin()
{
	return isbeginselectmode;
}

bool CharacterManager::getIsEnd()
{
	return isendselectmode;
}

int CharacterManager::getPlayTextureNum()
{
	return selectaction->getPlayTextureNum();
}

bool CharacterManager::getIsBossDeath()
{
	return isbossdeath;
}

bool CharacterManager::getIsBossFloor()
{
	return isbossfloor;
}

std::string CharacterManager::getActionName()
{
	return selectaction->getActionName();
}

void CharacterManager::CollisionPlayerToEnemy()
{
	for (auto enemy_itr = enemys.begin();
	enemy_itr != enemys.end();) {

		if (CollisionM.isAABBAABB(player->getAABB(), (*enemy_itr)->getAABB())) {
			if (!(*enemy_itr)->getIsAlive()) {
				enemy_itr++;
				continue;
			}
			if (!player->getIsInvincible()) {
				int damage = 10 - player->getDefense();
				if (damage <= 0)damage = 1;
				player->addHpValue(-damage);
				player->setIsStun(true);
				player->setIsinvincible(true);
				SoundM.PlaySE("damage.wav", 0.5f);
			}
			if (!(*enemy_itr)->getIsInvincible()) {
				mainwondow->setPrevEnemyHp((*enemy_itr)->getHp());
				(*enemy_itr)->addHpValue(-3);
				(*enemy_itr)->setIsStun(true);
				(*enemy_itr)->setIsinvincible(true);
				SoundM.PlaySE("damage.wav", 0.5f);
			}
			if ((mainwondow->getEnemyId() == (*enemy_itr)->getId())) {
				mainwondow->setEnemyHp((*enemy_itr)->getHp());
			
			}
			else {
				mainwondow->setEnemyStatuts((*enemy_itr)->getName(), (*enemy_itr)->getMaxHp(),
					(*enemy_itr)->getHp(), (*enemy_itr)->getId(), (*enemy_itr)->getUniqueColor());
			}
			enemy_itr++;
			continue;
		}
		else
		{
			enemy_itr++;
		}
	}
}

void CharacterManager::CollisionPlayerToBoss()
{
	for (auto boss_itr = boss.begin();
	boss_itr != boss.end();boss_itr++) {
		if (isbossdeatheffect)continue;
		if (!(*boss_itr)->getIsAlive())continue;
		if (CollisionM.isAABBAABB(player->getAABB(), (*boss_itr)->getAABB())) {
			if (!player->getIsInvincible()) {
				int damage = 10 - player->getDefense();
				if (damage <= 0)damage = 1;
				player->addHpValue(-damage);
				player->setIsStun(true);
				player->setIsinvincible(true);
				SoundM.PlaySE("damage.wav", 0.5f);
			}
		}
	}
}

void CharacterManager::SelectPlayerFolm(const ActionType _actiontype)
{
	float begin_scale_y = player->getScale().y;
	player->decideAction(_actiontype);
	player->setActionType(_actiontype);
	float next_scale_y = player->getScale().y;
	float trance_y = next_scale_y - begin_scale_y;
	player->setPosY(player->getPos().y + trance_y/2.f);
}

void CharacterManager::createAsset()
{
	SoundM.CreateSE("enemy_die.wav");
	SoundM.CreateSE("actionselectend.wav");
	TextureM.CreateTexture("UI/dokuro.png");
}

void CharacterManager::updatebossGage()
{
	if (!isbossbegineffectend)return;
	for (auto& itr : boss) {
		if (!(bosshpbuff == itr->getHp())) {
			bossgage_t = 0.0f;
			bossgagebeginrate = bossgagerate;
			bossgageendrate = float(itr->getHp()) / float(itr->getMaxHp());
			bosshpbuff = itr->getHp();
		}
		EasingManager::tCount(bossgage_t, isfirstgage ? 2.0f : 0.5f);
		if (isfirstgage) {
			bossgagerate = EasingLinear(bossgage_t, bossgagebeginrate, bossgageendrate);
		}else{
			bossgagerate = EasingCubicIn(bossgage_t, bossgagebeginrate, bossgageendrate);
		}
	
		if (EasingManager::tCountEnd(bossgage_t)) {
			isfirstgage = false;
		}
	}
}
