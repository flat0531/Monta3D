#include "BulletManager.h"
#include"../WorldObject/Bullet/BulletBase.h"
#include"../Top/CollisionManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../Top/SoundManager.h"
#include"../UI/MainWindow.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldObject/Effect/EffectExplodeburst.h"

using namespace ci;
using namespace ci::app;

BulletManager::BulletManager()
{
	createAsset();
}

void BulletManager::update()
{
	for (auto itr = playerbullets.begin();
	itr != playerbullets.end();) {
		(*itr)->update();
		if ((*itr)->deleteThis()||(!(*itr)->isActive())) {
			itr = playerbullets.erase(itr);
		}
		else {
			itr++;
		}
	}
	for (auto itr = enemybullets.begin();
	itr != enemybullets.end();) {
		(*itr)->update();
		if ((*itr)->deleteThis() || (!(*itr)->isActive())) {
			itr = enemybullets.erase(itr);
		}
		else {
			itr++;
		}
	}
	for (auto itr = bossbullets.begin();
	itr != bossbullets.end();) {
		(*itr)->update();
		if ((*itr)->deleteThis() || (!(*itr)->isActive())) {
			itr = bossbullets.erase(itr);
		}
		else {
			itr++;
		}
	}
	CollisionPlayerBulletToEnemyBullet();
	CollisionPlayerBulletToEnemys();
	CollisionEnemyBulletsToPlayer();
	CollisionBossBulletToPlayer();
	CollisionPlayerBulletToBoss();
	CollisionBossBulletToPlayerBullet();
}

void BulletManager::draw()
{
	for (auto& itr : playerbullets) {
		itr->draw();
	}
	for (auto& itr : enemybullets) {
		itr->draw();
	}
	for (auto& itr : bossbullets) {
		itr->draw();
	}
}

void BulletManager::setCharacterManagerPtr(CharacterManager * charactermanager)
{
	charactermanagerptr = charactermanager;
}

void BulletManager::setEffectManagerPtr(EffectManager * effectmanager)
{
	effectmanagerptr = effectmanager;
}

void BulletManager::setMainWindowPtr(MainWindow * mainwindow)
{
	mainwindowptr = mainwindow;
}

std::list<std::shared_ptr<BulletBase>>& BulletManager::getPlayerBullets()
{
	return playerbullets;
}

std::list<std::shared_ptr<BulletBase>>& BulletManager::getEnemyBullets()
{
	return enemybullets;
}

std::list<std::shared_ptr<BulletBase>>& BulletManager::getBossBullets()
{
	return bossbullets;
}

void BulletManager::ClearEnemyBullets()
{
	enemybullets.clear();
}

void BulletManager::ClearPlayerBullets()
{
	playerbullets.clear();
}

void BulletManager::ClearBossBullets()
{
	bossbullets.clear();
}

void BulletManager::ClearBullets()
{
	ClearEnemyBullets();
	ClearPlayerBullets();
	ClearBossBullets();
}


void BulletManager::CollisionPlayerBulletToEnemys()
{
	for (auto playerbullet_itr = playerbullets.begin();
	playerbullet_itr != playerbullets.end();) {
		bool isdelete = false;
		for (auto enemysitr = charactermanagerptr->getEnemys().begin();
		enemysitr != charactermanagerptr->getEnemys().end();enemysitr++) {
			if ((*enemysitr)->getIsInvincible()|| (!(*enemysitr)->getIsAlive())) {
				continue;
			}
			if (CollisionM.isAABBAABB((*playerbullet_itr)->getAABB(), (*enemysitr)->getAABB())) {
				(*enemysitr)->setIsStun(true);
				(*enemysitr)->setIsinvincible(true);
				mainwindowptr->setPrevEnemyHp((*enemysitr)->getHp());
				(*enemysitr)->addHpValue(-((*playerbullet_itr)->getAttackPoint()));
				SoundM.PlaySE("damage.wav",0.5f);
				if (mainwindowptr->getEnemyId() == (*enemysitr)->getId()) {
					mainwindowptr->setEnemyHp((*enemysitr)->getHp());
				}
				else {
					mainwindowptr->setEnemyStatuts((*enemysitr)->getName(), (*enemysitr)->getMaxHp(),
						(*enemysitr)->getHp(), (*enemysitr)->getId(), (*enemysitr)->getUniqueColor());
				
				}
				(*playerbullet_itr)->AddHpValue(-10);//‰¼

				if ((*playerbullet_itr)->isActive()) {
					continue;
				}
				else {
					playerbullet_itr = playerbullets.erase(playerbullet_itr);
					isdelete = true;
					break;
				}
			}
		}
		if(!isdelete)
		playerbullet_itr++;
	}
}

void BulletManager::CollisionPlayerBulletToEnemyBullet()
{
	for (auto playerbullet_itr = playerbullets.begin();
	playerbullet_itr != playerbullets.end();) {
		bool isplayerbulletdelete = false;
		for (auto enemybullet_itr = enemybullets.begin();
		enemybullet_itr != enemybullets.end();) {
			bool isenemybulletdelete = false;
			if (CollisionM.isAABBAABB((*playerbullet_itr)->getAABB(), (*enemybullet_itr)->getAABB())) {

				(*enemybullet_itr)->AddHpValue(-((*playerbullet_itr)->getAttackPoint()));
				(*playerbullet_itr)->AddHpValue(-((*enemybullet_itr)->getAttackPoint()));

				if ((*enemybullet_itr)->isActive()) {
				
				}
				else {
					effectmanagerptr->CreateEffect(EffectExplodeburst((*enemybullet_itr)->getPos(), (*enemybullet_itr)->getScale(),
						Vec3f(0, 0, 0), ColorA(1, 0, 0, 1), 1.0f));
					SoundM.PlaySE("skilharetu.wav");
					enemybullet_itr = enemybullets.erase(enemybullet_itr);
					isenemybulletdelete = true;
				}

				if ((*playerbullet_itr)->isActive()) {
					continue;
				}
				else {
					effectmanagerptr->CreateEffect(EffectExplodeburst((*playerbullet_itr)->getPos(), (*playerbullet_itr)->getScale(),
						Vec3f(0, 0, 0), ColorA(1, 0, 0, 1), 1.0f));
					SoundM.PlaySE("skilharetu.wav");
					playerbullet_itr = playerbullets.erase(playerbullet_itr);
					isplayerbulletdelete= true;
					break;
				}
			}
			if (!isenemybulletdelete)
				enemybullet_itr++;
		}
		if (!isplayerbulletdelete)
			playerbullet_itr++;
	}
}

void BulletManager::CollisionEnemyBulletsToPlayer()
{
	for (auto enemybullet_itr = enemybullets.begin();
	enemybullet_itr != enemybullets.end();) {
		if (charactermanagerptr->getPlayer()->getIsInvincible()) {
			enemybullet_itr++;
			continue;
		}
		if (CollisionM.isAABBAABB(charactermanagerptr->getPlayer()->getAABB(), (*enemybullet_itr)->getAABB())){

			(*enemybullet_itr)->AddHpValue(-10);
			(charactermanagerptr->getPlayer()->addHpValue(-((*enemybullet_itr)->getAttackPoint())));
			charactermanagerptr->getPlayer()->setIsStun(true);
			charactermanagerptr->getPlayer()->setIsinvincible(true);
			SoundM.PlaySE("damage.wav", 0.5f);
			if ((*enemybullet_itr)->isActive()) {
				enemybullet_itr++;
				continue;
			}
			else {
				enemybullet_itr = enemybullets.erase(enemybullet_itr);
			}
		}
		else
		{
			enemybullet_itr++;
		}
	}
}

void BulletManager::CollisionBossBulletToPlayer()
{
	for (auto bossbullet_itr = bossbullets.begin();
	bossbullet_itr != bossbullets.end();) {
		if (charactermanagerptr->getPlayer()->getIsInvincible()) {
			bossbullet_itr++;
			continue;
		}
		if (CollisionM.isAABBAABB(charactermanagerptr->getPlayer()->getAABB(), (*bossbullet_itr)->getAABB())) {

			(*bossbullet_itr)->AddHpValue(-10);
			(charactermanagerptr->getPlayer()->addHpValue(-((*bossbullet_itr)->getAttackPoint())));
			charactermanagerptr->getPlayer()->setIsStun(true);
			charactermanagerptr->getPlayer()->setIsinvincible(true);
			SoundM.PlaySE("damage.wav", 0.5f);
			if ((*bossbullet_itr)->isActive()) {
				bossbullet_itr++;
				continue;
			}
			else {
				bossbullet_itr = bossbullets.erase(bossbullet_itr);
			}
		}
		else
		{
			bossbullet_itr++;
		}
	}
}

void BulletManager::CollisionPlayerBulletToBoss()
{
	for (auto playerbullet_itr = playerbullets.begin();
	playerbullet_itr != playerbullets.end();) {
		bool isdelete = false;
		for (auto bossitr = charactermanagerptr->getBoss().begin();
		bossitr != charactermanagerptr->getBoss().end();bossitr++) {
			if ((!(*bossitr)->getIsAlive())) {
				continue;
			}
			if (CollisionM.isAABBAABB((*playerbullet_itr)->getAABB(), (*bossitr)->getAABB())) {
				//(*bossitr)->setIsStun(true);
				if (!(*bossitr)->getIsInvincible()) {
					(*bossitr)->addHpValue(-((*playerbullet_itr)->getAttackPoint()));
				}
				(*bossitr)->setIsinvincible(true);
				
				SoundM.PlaySE("damage.wav", 0.5f);
				(*playerbullet_itr)->AddHpValue(-100000);//‰¼
			
				if ((*playerbullet_itr)->isActive()) {
					continue;
				}
				else {
					SoundM.PlaySE("skilharetu.wav");
					effectmanagerptr->CreateEffect(EffectExplodeburst((*playerbullet_itr)->getPos(), (*playerbullet_itr)->getScale(),
						Vec3f(0, 0, 0), ColorA(1, 1, 0, 1), 1.0f));
					playerbullet_itr = playerbullets.erase(playerbullet_itr);
					isdelete = true;
					break;
				}
			}
		}
		if (!isdelete)
			playerbullet_itr++;
	}
}

void BulletManager::CollisionBossBulletToPlayerBullet()
{
	for (auto playerbullet_itr = playerbullets.begin();
	playerbullet_itr != playerbullets.end();) {
		bool isplayerbulletdelete = false;
		for (auto bossbullet_itr = bossbullets.begin();
		bossbullet_itr != bossbullets.end();) {
			bool isenemybulletdelete = false;
			if (CollisionM.isAABBAABB((*playerbullet_itr)->getAABB(), (*bossbullet_itr)->getAABB())) {

				(*bossbullet_itr)->AddHpValue(-((*playerbullet_itr)->getAttackPoint()));
				(*playerbullet_itr)->AddHpValue(-((*bossbullet_itr)->getAttackPoint()));

				if ((*bossbullet_itr)->isActive()) {

				}
				else {
					effectmanagerptr->CreateEffect(EffectExplodeburst((*bossbullet_itr)->getPos(), (*bossbullet_itr)->getScale(),
						Vec3f(0, 0, 0), ColorA(1, 0, 0, 1), 1.0f));
					SoundM.PlaySE("skilharetu.wav");
					bossbullet_itr = bossbullets.erase(bossbullet_itr);
					isenemybulletdelete = true;
				}

				if ((*playerbullet_itr)->isActive()) {
					continue;
				}
				else {
					effectmanagerptr->CreateEffect(EffectExplodeburst((*playerbullet_itr)->getPos(), (*playerbullet_itr)->getScale(),
						Vec3f(0, 0, 0), ColorA(1, 0, 0, 1), 1.0f));
					SoundM.PlaySE("skilharetu.wav");
					playerbullet_itr = playerbullets.erase(playerbullet_itr);
					isplayerbulletdelete = true;
					break;
				}
			}
			if (!isenemybulletdelete)
				bossbullet_itr++;
		}
		if (!isplayerbulletdelete)
			playerbullet_itr++;
	}
}

void BulletManager::createAsset()
{
	SoundM.CreateSE("damage.wav");
	SoundM.CreateSE("skilharetu.wav");
}
