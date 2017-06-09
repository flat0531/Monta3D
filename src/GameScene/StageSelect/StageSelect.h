#pragma once
#include"../../Scene/SceneBase.h"
#include"cinder/app/App.h"
#include"cinder/Camera.h"
#include "../../WorldObject/Map2d.h"
#include"../../Top/SurfaceEffect.h"
#include"../../StageSelectObject/PointRoad.h"
#include"../../StageSelectObject/StageIcon.h"
#include"../../StageSelectObject/StageNamePlate.h"
#include"../../StageSelectObject/StageSelectLogo.h"
#include"../../StageSelectObject/InformationWindowList.h"
class StageSelect :public SceneBase {
public:
	void setup() override;
	void update() override;
	void draw() override;
	void draw2D() override;
	void shift() override;
private:
	int worldnum;
	int stagenum;
	bool isiconmoving;
	bool is_move_to_next;
	bool is_move_to_back;
	float icon_move_t;
	ci::Vec2f easing_icon_beginpos;
	ci::Vec2f easing_icon_endpos;
	ci::Vec2f playericonpos = ci::Vec2f(0, 0);
	ci::Vec2f playericonspeed = ci::Vec2f(0, 0);
	ci::CameraPersp camera;
	ci::CameraOrtho ortho;
	std::vector<PointRoad>pointroads;
	std::vector<StageIcon>stageicons;
	std::vector<std::string>stagename;
	StageNamePlate stagenameplate;
	StageSelectLogo stageselectlogo;
	InformationWindowList informationwindowlist;
	void drawBackGround();
	void createpointRoads();
	void createStageIcon();
	void drawStageIcon();
	std::string backgroundpath;
	std::vector<ci::Vec2f>stagepos;
	std::vector<ci::Vec2i>easingtypes;
	std::vector<StageData>stagedatas;
	void roadStageData();
	void drawTitle();
	void selectStage();
	void updatePlayerIcon();
	void drawPlayerIcon();
	void FadeInGameMain();
	void roadStageName();
	void ShiftDrawScene();
	int animation_count = 0;
};