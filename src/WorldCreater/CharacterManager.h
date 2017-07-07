#pragma once
#include<memory>
#include<list>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\gl\Texture.h"
#include"../UI/SelectAction.h"
#include"cinder\Camera.h"
class CharacterBase;
class Player;
class Enemy;
class Boss;
class BulletManager;
class EffectManager;
class CameraManager;
class MapChipManager;
class MainWindow;
class ShadowManager;
enum ActionType;
class CharacterManager {
public:
	CharacterManager();
	void CreatePlayer(ci::Vec3f pos);
	void setBulletManagerPointer(BulletManager* _bulletmanager);
	void setEffectManagerPointer(EffectManager* _effectmanager);
	void setShadowManagerPointer(ShadowManager* _shadowmanager);
	void setCameraManagerPointer(CameraManager* _cameramanager);
	void setMapChipManagerPointer(MapChipManager* _mapchipmanager);
	void setMainWindowPointer(MainWindow* _mainwindow);
	void setBulletManagerPtrToPlayer();
	void setBulletManagerPtrToEnemys();
	void setBulletManagerPtrToBoss();
	void setCameratManagerPtrToBoss();
	void setEffectManagerPtrToBoss();
	void setMapChipManagerPtrToBoss();
	void setPlayerAction(ActionType type);
	void setEnemysAction();
	void setBossAction();
	void update(const ci::CameraPersp camera);
	void draw(const ci::CameraPersp camera);
	void CreateEnemys(const int worldnum, const int stagenum, const int floornum);
	void CreateBoss(const int worldnum, const int stagenum, const int floornum);
	CharacterManager* getThisPointer();
	void updatePlayerDeath();
	std::shared_ptr<CharacterBase> getPlayer();
	std::list<std::shared_ptr<CharacterBase>>& getEnemys();
	std::list<std::shared_ptr<CharacterBase>>& getBoss();
	void setActionSelectMode(const bool is);
	bool getActionSelectMode();
	void updateActionSelectMode();
	void drawActionSelectMode();
	void drawActionSelecBackGround();
	void setActionSelectBackGround(const ci::gl::Texture& tex);
	void drawBossHpGage();
	float getBackGround_T();
	bool getIsBegin();
	bool getIsEnd();
	int  getPlayTextureNum();
	bool getIsBossDeath();
	bool getIsBossFloor();
	std::string getActionName();
private:
	std::shared_ptr<CharacterBase>player;
	std::list<std::shared_ptr<CharacterBase>> enemys;
	std::list<std::shared_ptr<CharacterBase>>boss;
	BulletManager* bulletmanager;
	CameraManager* cameramanager;
	EffectManager* effectmanager;
	ShadowManager* shadowmanager;
	MapChipManager* mapchipmanager;
	MainWindow* mainwondow;
	std::shared_ptr<SelectAction>selectaction;
	bool actionselectmode = false;
	float background_t = 0.0f;
	bool isbeginselectmode = true;
	bool isendselectmode = false;
	ci::gl::Texture background;
	ci::Vec2f backgroundsize = ci::Vec2f(0,0);
	bool isbossdeath = false;
	bool isbossfloor = false;
	bool isbossbegineffectend = false;
	///////////////////////////////////////ƒ{ƒXŠÖ˜A
	int bosshpbuff;
	float bossgage_t = 0.0f;
	float bossgagebeginrate=0.0f;
	float bossgagerate = 0.0f;
	float bossgageendrate = 1.0f;
	float bossdeatheffecte_t = 0.0f;
	bool isbossdeatheffect = false;
	bool isbossdeatheffectend = false;
	bool isfirstgage = true;
	bool ismove = false;
	///////////////////////////////
	void CollisionPlayerToEnemy();
	void CollisionPlayerToBoss();
	void createAsset();
	void updatebossGage();
	void SelectPlayerFolm(const ActionType _actiontype);
};