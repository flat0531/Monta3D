#pragma once
#include<memory>
#include<list>
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class CharacterBase;
class Player;
class Enemy;
class BulletManager;
class EffectManager;
class MainWindow;
enum ActionType;
class CharacterManager {
public:
	CharacterManager();
	void CreateCharacter(CharacterBase character);
	void CreatePlayer(ci::Vec3f pos);
	void setBulletManagerPointer(BulletManager* _bulletmanager);
	void setEffectManagerPointer(EffectManager* _effectmanager);
	void setMainWindowPointer(MainWindow* _mainwindow);
	void setBulletManagerPtrToPlayer();
	void setBulletManagerPtrToEnemys();
	void setPlayerAction(ActionType type);
	void setEnemysAction();
	void setup();
	void update();
	void draw();
	void CreateEnemys(const int worldnum, const int stagenum, const int floornum);
	CharacterManager* getThisPointer();
	void updatePlayerDeath();
	std::shared_ptr<CharacterBase> getPlayer();
	std::list<std::shared_ptr<CharacterBase>>& getEnemys();
	void setActionSelectMode(const bool is);
	bool getActionSelectMode();
	void updateActionSelectMode();
	void drawActionSelectMode();
private:
	std::shared_ptr<CharacterBase>player;
	std::list<std::shared_ptr<CharacterBase>> enemys;
	BulletManager* bulletmanager;
	EffectManager* effectmanager;
	MainWindow* mainwondow;
	void CollisionPlayerToEnemy();
	ActionType stringToActionType(const std::string name);
	void SelectPlayerFolm();
	bool actionselectmode = false;
	void updateBackGround();
	void drawBackGround();
	float background_t = 0.0f;
	bool isbeginselectmode = true;
	bool isendselectmode = false;
	ci::Vec2f backgroundsize = ci::Vec2f(0,0);
};