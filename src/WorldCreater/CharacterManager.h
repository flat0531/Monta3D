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
class BulletManager;
class EffectManager;
class MainWindow;
class ShadowManager;
enum ActionType;
class CharacterManager {
public:
	CharacterManager();
	void CreateCharacter(CharacterBase character);
	void CreatePlayer(ci::Vec3f pos);
	void setBulletManagerPointer(BulletManager* _bulletmanager);
	void setEffectManagerPointer(EffectManager* _effectmanager);
	void setShadowManagerPointer(ShadowManager* _shadowmanager);
	void setMainWindowPointer(MainWindow* _mainwindow);
	void setBulletManagerPtrToPlayer();
	void setBulletManagerPtrToEnemys();
	void setPlayerAction(ActionType type);
	void setEnemysAction();
	void setup();
	void update(const ci::CameraPersp camera);
	void draw(const ci::CameraPersp camera);
	void CreateEnemys(const int worldnum, const int stagenum, const int floornum);
	CharacterManager* getThisPointer();
	void updatePlayerDeath();
	std::shared_ptr<CharacterBase> getPlayer();
	std::list<std::shared_ptr<CharacterBase>>& getEnemys();
	void setActionSelectMode(const bool is);
	bool getActionSelectMode();
	void updateActionSelectMode();
	void drawActionSelectMode();
	void drawActionSelecBackGround();
	void setActionSelectBackGround(const ci::gl::Texture& tex);
	float getBackGround_T();
	bool getIsBegin();
	bool getIsEnd();
	int  getPlayTextureNum();
	std::string getActionName();
private:
	std::shared_ptr<CharacterBase>player;
	std::list<std::shared_ptr<CharacterBase>> enemys;
	BulletManager* bulletmanager;
	EffectManager* effectmanager;
	ShadowManager* shadowmanager;
	MainWindow* mainwondow;
	std::shared_ptr<SelectAction>selectaction;
	bool actionselectmode = false;
	float background_t = 0.0f;
	bool isbeginselectmode = true;
	bool isendselectmode = false;
	ci::gl::Texture background;
	ci::Vec2f backgroundsize = ci::Vec2f(0,0);

	void CollisionPlayerToEnemy();
	void updateBackGround();
	void drawBackGround();
	ActionType stringToActionType(const std::string name);
	void SelectPlayerFolm(const ActionType _actiontype);
};