#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include"../../WorldObject/Line.h"
#include"../../WorldObject/VerticalLine.h"
#include"../../WorldCreater/MapManager.h"
#include"../../WorldCreater/CharacterManager.h"
#include"../../WorldCreater/MapChipManager.h"
#include"../../WorldCreater/ItemManager.h"
#include"../../WorldObject/Information.h"
#include<vector>
#include<memory>
#include"../../UI/MainWindow.h"
#include"cinder\TriMesh.h"
#include"cinder\gl\Texture.h"
#include"cinder\gl/Fbo.h"
#include"../../UI/UICreater.h"
class Player;
class BulletManager;
class EffectManager;
class CameraManager;
class ShadowManager;
class ShiftFloorObject;
class GameMain :public SceneBase {
public:
	GameMain::GameMain();
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	MapManager mapmanager;
	std::shared_ptr<CameraManager>cameramanager;
	std::shared_ptr<BulletManager>bulletmanager;
	std::shared_ptr<CharacterManager> charactermanager;
	std::shared_ptr<MapChipManager> mapchipmanager;
	std::shared_ptr<EffectManager> effectmanager;
	std::shared_ptr<ItemManager>itemmanager;
	std::shared_ptr<ShadowManager>shadowmanager;
	std::shared_ptr<MainWindow>mainwindow;
	std::vector<std::shared_ptr<ShiftFloorObject>> shiftfloorobjects;
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	Information information;
	UICretaer uicreater;
	std::string bgmname;
	int worldnum;
	int stagenum;
	int floornum;
	ci::Font font;
	ci::Vec3f nextplayerpos;
	ci::Vec3f nextplayerrotate;
	bool isshiting = false;
	bool isgoal = false;
	bool isgoaleffecting = false;
	bool isgoaleffecingend = false;
	bool isshiftstageselect = false;
	bool playerdead = false;
	bool isdeathblackboxstart = false;
	float deathblackbox_t = 0.0f;
	float zankicolor_t = 0.0f;
	float zanki_delay_t = 0.0f;
	float zanki_size_t = 0.0f;
	float zankisizerate = 1.0f;
	float zanki_trancepos_y = 0.0f;
	ci::Vec2f deathblackboxsize = ci::Vec2f(0, 0);
	float deathblackboxangle = 0.0f;
	bool isshiftdeath = false;
	bool isdeathshifttitle = false;
	bool starteffect_isend;
	void shiftNextFloor();
	void shiftGoal();
	void ReCreateStage();
	void cretateShiftFloorObject();
	void updateShiftFloorObject();
	void drawShiftFloorObject();
	void playBGM();
	void updateGoal();
	void updateDeath();
	void drawDeathBlackBox();
	void drawZankiIcon();
	void updateDeathBlackBox();
	void updateZanki();
	void DeathFadeInend();
	void StartActionSelectMode();
	void drawShadow();
	void setStartPos();
	ci::gl::Texture ofScrean(const float rate);
};