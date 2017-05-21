#include "CharacterManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../WorldObject/Player.h"
#include"../CharacterAction/ActionBase.h"
#include"../WorldObject/Enemy.h"
#include"../Top/Top.h"
#include"../Top/CollisionManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldObject/Effect/EffectExplosion.h"
#include"../Top/EasingManager.h"
#include"../Top/SoundManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../Input/KeyManager.h"
#include"../Top/MyJson.h"
#include"../UI/MainWindow.h"
#include"../Top/DrawManager.h"
using namespace ci;
using namespace ci::app;
CharacterManager::CharacterManager()
{
	SoundM.CreateSE("enemy_die.wav");
	SoundM.CreateSE("actionselectend.wav");
}

void CharacterManager::CreateCharacter(CharacterBase character)
{
	
}

void CharacterManager::CreatePlayer(ci::Vec3f pos)
{
	player = std::make_shared<Player>(pos,ActionType::NONE);
}

void CharacterManager::setBulletManagerPointer(BulletManager * _bulletmanager)
{
	bulletmanager = _bulletmanager;
}

void CharacterManager::setEffectManagerPointer(EffectManager * _effectmanager)
{
	effectmanager = _effectmanager;
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


void CharacterManager::setup()
{
	CreateEnemys(1,1,1);//////////////
}

void CharacterManager::update()
{
	player->update();
	SelectPlayerFolm();
	for (auto itr = enemys.begin();itr != enemys.end();) {
		if ((*itr)->getIsAlive()) {
		     //ci::app::console() << (*itr)->getHp() << std::endl;
			itr++;
		}
		else
		{
			(*itr)->updateDeath(0.75f);
			if ((*itr)->updateDeathEnd()) {
				effectmanager->CreateEffect(EffectExplosion((*itr)->getPos(), (*itr)->getScale(), ci::Vec3f(0, 0, 0)));
				itr = enemys.erase(itr);
				SoundM.PlaySE("enemy_die.wav", 0.5f);
			}
			else {
				itr++;
			}

		}
	}
	for (auto& itr : enemys) {
		if ((itr)->getIsAlive()) {
			itr->update();
		}
	}
	CollisionPlayerToEnemy();
}

void CharacterManager::draw()
{
	player->draw();
	for (auto& itr : enemys) {
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
		enemys.push_back(std::make_shared<Enemy>(pos, stringToActionType(enemytype), i + 1));
	}



	/*ci::Vec3f pos2 = ci::Vec3f(-30.5, 10, 0.1)*WorldScale;
	enemys.push_back(std::make_shared<Enemy>(pos2, ActionType::WITCH));
	ci::Vec3f pos = ci::Vec3f(-60.5, 10, 0.1)*WorldScale;
	enemys.push_back(std::make_shared<Enemy>(pos,ActionType::RATTON));
	ci::Vec3f pos3 = ci::Vec3f(-17.5, 2, 0.1)*WorldScale;
	enemys.push_back(std::make_shared<Enemy>(pos3, ActionType::SPARROW));*/
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
		if (KeyManager::getkey().isPush(KeyEvent::KEY_i)) {
			isendselectmode = true;
			SoundM.PlaySE("actionselectend.wav");
		}
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
	}
	
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
				player->addHpValue(-10);
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

ActionType CharacterManager::stringToActionType(const std::string name)
{
	if (name=="ratton") {
		return ActionType::RATTON;
	}
	if (name == "witch") {
		return ActionType::WITCH;
	}
	if (name == "sparrow") {
		return ActionType::SPARROW;
	}
	console() << "ƒoƒO‚Å‚·" << std::endl;
	return ActionType::RATTON;
}

void CharacterManager::SelectPlayerFolm()
{
	if (KeyManager::getkey().isPush(KeyEvent::KEY_m)) {
		if (player->getActiontype() != SLIME) {
			player->decideAction(SLIME);
			player->setActionType(SLIME);
		}

	}
	if (KeyManager::getkey().isPush(KeyEvent::KEY_n)) {
		if (player->getActiontype() != CAT) {
			player->decideAction(CAT);
			player->setActionType(CAT);
		}
	}
}

void CharacterManager::updateBackGround()
{
}

void CharacterManager::drawBackGround()
{
}
