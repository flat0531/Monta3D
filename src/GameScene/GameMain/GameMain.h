#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include"../../WorldObject/Line.h"
#include"../../WorldObject/VerticalLine.h"
#include"../../WorldCreater/MapManager.h"
#include"../../WorldCreater/CharacterManager.h"
#include"../../WorldCreater/MapChipManager.h"
#include"../../WorldObject/Information.h"
#include<vector>
#include<memory>
#include"../../UI/MainWindow.h"
#include"cinder\TriMesh.h"
#include"cinder\gl\Texture.h"

class Player;
class BulletManager;
class EffectManager;
class CameraManager;
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
	std::vector<std::shared_ptr<ShiftFloorObject>> shiftfloorobjects;
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	Information information;
	std::shared_ptr<MainWindow>mainwindow;
	int worldnum;
	int stagenum;
	int floornum;
	ci::Vec3f nextplayerpos;
	bool isshiting = false;
	bool isgoal = false;
	bool isgoaleffecting = false;
	bool isgoaleffecingend = false;
	bool isshiftstageselect = false;
	void shiftNextFloor();
	void shiftGoal();
	void ReCreateStage();
	void drawPlayer();
	void updatePlayer();
	void updateLinetoPlayer();
	void cretateShiftFloorObject();
	void updateShiftFloorObject();
	void drawShiftFloorObject();
	void playBGM();
	void updateGoal();
	bool starteffect_isend;
};