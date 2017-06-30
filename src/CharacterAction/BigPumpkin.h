#pragma once
#include"ActionBase.h"
#include<memory>
class Boss;
class CharacterBase;
enum PumpkinUpdateType {
	STANDBY,DROP,WIDESHOT,COLORSHOT, JUMPROPE,BARRIERSHOT
};
class BigPumpkin :public ActionBase {
public:
	BigPumpkin();
	BigPumpkin(CharacterBase* _enemy);
	void update() override;
	void draw()  override;
	void attack()  override;
private:
	Boss* bossptr;
	PumpkinUpdateType updatetype = PumpkinUpdateType::STANDBY;
	std::vector<PumpkinUpdateType>nextcandidate;
	std::vector<ci::ColorA>rainbowcolor;
	int controlcount;
	bool isbegineffect;
	void updateBeginEffect();
	float rotate_easing_t = 0;
	void rotateStart();
	void rotateEasing();
	bool isrotate = false;
	bool getIsHpHalf();
	int begineffectcount;
	void createAsset();
	void mainUpdate();
	/////////////////
	void updateDrop();
	void updateWideshot();
	void updateStandby();
	void updateColorshot();
	void updateJumpRope();
	void updateBarriershot();
	/////////////////
	int mainupdatecount = 0;
	void setNextUpdate(const bool _isshift);
	void createNextUpdate();
	void createNextCandidate(const PumpkinUpdateType type, const int num);
	void updateSetUp();
	void createRainbowColor();
	PumpkinUpdateType getNextUpdate();
	ci::Vec3f basepos;
	///////standby
	float standby_sinangle = 0.0f;
	//////

	///////Drop
	ci::Vec3f dropbeginpos;
	ci::Vec3f dropuppos;
	ci::Vec3f dropdownpos;
	float dropstep_t[5];
	float returnbase_t;
	bool isshake = false;
	int dropcount = 0;
	int dropnum;
	void dropLockon();
	void dropDelay();
	void dropShake();
	void dropBegin();
	void dropEnd();
	void dropReturnBase();
	//////

	//////////WIDESHOT/////
	std::vector<float>wide_t;
	std::vector<ci::Vec3f>wideshotpos;
	float wide_end_t=0.0f;
	void wideShotSetUp();
	void wideMove();
	void createWideShot();
	////////

	////////ColorShot/////
	float color_t[4];
	bool ischargeshake = false;
	ci::Vec3f colorshotpos;
	void colorBeginMove();
	void colorCharge();
	void colorDelay();
	void colorEndMove();
	void colorShot();
	
	void colorShotSetUp();
	//////

	///////// jump rope///////
	void jumpRopeSetUp();
	std::vector<float>jumprope_t;
	ci::Vec3f jumproperotatepos;
	ci::Vec3f jumpropeendpos;
	ci::Vec3f jumpropeendrotate;
	float jumproperotatespeed = 0.0f;
	void jumpRopeBeginMove();
	void jumpRopeRotate();
	void jumpRopeDelay();
	void jumpRopeStop();
	void jumpRopeEndMove();
	void createJumpRope();
	/////////////////////


	///////////Barrier//////////////////
	std::vector<float>barrier_t;
	void barrierSetUp();
	void barrierCreateMapChip();
	void barrierBeginDelay();
	void barrierShot();
	void barrierEndDelay();
	void barrierReverseMapChip();
	int barriercreatecount = 0;
	void createColorChip(const int y,const int x);
	void createNoneChip(const int y, const int x);
	void barrierCreateBullet();
	void barrierUpdateBossPos();
	bool iscreatetype = true;
	bool barrierisshake = false;
	float barriersinangle = 0.0f;
	ci::Vec3f barrierendpos;
    ///////////////////////////
};
