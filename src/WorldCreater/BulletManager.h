#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include<memory>
#include<list>
class BulletBase;
class CharacterManager;
class EffectManager;
class MainWindow;
class BulletManager {
public:
	BulletManager();
	void update();
	void draw();

	template<class T>
	void CreateEnemyBullet(T enemybullet);
	template<class T>
	void CreatePlayerBullet(T playerbullet);
	template<class T>
	void CreateBossBullet(T bossbullet);
	BulletManager* getThisPointer() {
		return this;
	}
	void setCharacterManagerPtr(CharacterManager* charactermanager);
	void setEffectManagerPtr(EffectManager* effectmanager);
	void setMainWindowPtr(MainWindow* mainwindow);
	std::list<std::shared_ptr<BulletBase>>& getPlayerBullets();
	std::list<std::shared_ptr<BulletBase>>& getEnemyBullets();
	std::list<std::shared_ptr<BulletBase>>& getBossBullets();
	void ClearEnemyBullets();
	void ClearPlayerBullets();
	void ClearBossBullets();
	void ClearBullets();
private:
	void CollisionPlayerBulletToEnemys();
	void CollisionPlayerBulletToEnemyBullet();
	void CollisionEnemyBulletsToPlayer();
	void CollisionBossBulletToPlayer();
	void CollisionPlayerBulletToBoss();
	void CollisionBossBulletToPlayerBullet();
	void createAsset();
	CharacterManager* charactermanagerptr;
	EffectManager* effectmanagerptr;
	MainWindow* mainwindowptr;
	std::list<std::shared_ptr<BulletBase>> enemybullets;
	std::list<std::shared_ptr<BulletBase>> bossbullets;
	std::list<std::shared_ptr<BulletBase>> playerbullets;
	
};

template<class T>
inline void BulletManager::CreateEnemyBullet(T enemybullet)
{
	enemybullets.push_back(std::make_shared<T>(enemybullet));
}

template<class T>
inline void BulletManager::CreatePlayerBullet(T playerbullet)
{
	playerbullets.push_back(std::make_shared<T>(playerbullet));
}

template<class T>
inline void BulletManager::CreateBossBullet(T bossbullet)
{
	bossbullets.push_back(std::make_shared<T>(bossbullet));
}
