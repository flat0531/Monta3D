#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\Json.h"
class CharacterBase;
class EffectManager;
enum CamaraUpdateType {
	PLAYER_CAMERA,EVENT_CAMERA,X_LOCK_CAMERA, Y_LOCK_CAMERA, XY_LOCK_CAMERA,BOSS_CAMERA,BOSS_EFFECT_END,CAMERA_TYPE_MAX
};
class CameraManager {
public:
	CameraManager();
	void update();
	void setMinValue(const ci::Vec2f _minvalue);///マップの左端をセット
	void setMaxValue(const ci::Vec2f _maxvalue);///マップの右端をセット
	void unitPrevCenterOfInterestPoint(const ci::Vec3f prevpos);
	void setCameraUpdateType(const CamaraUpdateType _cameratype);
	void setEffectManagerPtr(EffectManager* _effectmanager);
	void setDeatCameraT(float _t);
	void setPlayerPtr(class CharacterBase* _playerptr);
	void updateCameraTrance();
	void ResetT();///変数をリセット
	void Shake(const float value, const float time);///一定時間画面を揺らす
	CameraManager* getThisPtr();
	CamaraUpdateType getCameraUpdateType();
	CamaraUpdateType JsonReadCameraType(const int worldnum, const int stagenum, const int floornum);///JSONからカメラのタイプを取得
	ci::Vec3f getSetEyePointTrance();
	ci::Vec3f getSetCenterofinterestPointTrance();
	ci::Vec3f getSetEyePoint();
	ci::Vec3f getSetCenterofinterestPoint();
	ci::Vec3f getShakeEyePoint();
	ci::Vec3f getShakeCenterPoint();
	bool getDeathCameraEnd();
	bool getIsBossDelayEnd();
private:
	ci::Vec3f prevcenterrofinterstpoint;
	ci::Vec2f minvalue;
	ci::Vec2f maxvalue;
	CamaraUpdateType cameraupdatetype;
	CharacterBase* playerptr;
	EffectManager* effectmanager;
	ci::Vec3f seteyepoint;
	ci::Vec3f setcenterofinterestpoint;
	ci::Vec3f seteyepointtrance = ci::Vec3f(0, 0, 0);
	ci::Vec3f setcenterofinterestpointtrance = ci::Vec3f(0, 0, 0);
	ci::Vec3f shakeeyepoint = ci::Vec3f(0, 0, 0);
	ci::Vec3f shakecenterpoint = ci::Vec3f(0, 0, 0);
	ci::Vec3f rotateeyepoint;
	ci::Vec3f rotateeyecenterpoint;
	bool isplayerrightmove;
	float trancex_t;
	float cameratrancex;
	float begincameratrancex;
	float endcameratrancex;
	float trancemaxvalue;
	float cameralockpos_x;
	float cameralockeyepos_y;
	float lockcenterofinterestpoint_y;
	float deathcamera_t = 0.0f;
	float deathdelay_t = 0.0f;
	float shaketime_t = 0.f;
	float bosssinrotateangle = 0.0f;
	float bossrotate_t = 0.0f;
	float bosstoplayer_t = 0.0f;
	int createbosseffectcount = 0;
	float bossdelay_t = 0.0f;
	bool isshake = false;
	float shakevalue;
	float shaketime;
	void updateShake();
	bool deathcameraend = false;
	void updatePlayerCameraType();
	void updateEventCameraType();
	void updateXLockCameraType();
	void updateYLockCameraType();
	void updateXYLockCameraType();
	void updateBossCameraType();
	void updateBossDeathEffectCamera();
	void updateBlackWall();
	void CreateBossEffect();
	std::vector<float>event_t;
	std::vector<float>easingtime;
	std::vector<ci::Vec3f>eyebeginpos;
	std::vector<ci::Vec3f>eyeendpos;
	std::vector<ci::Vec3f>eyecenterbeginpos;
	std::vector<ci::Vec3f>eyecenterendpos;
	std::vector<ci::Vec3i>easingtypeseye;
	std::vector<ci::Vec3i>easingtypescenter;
	CamaraUpdateType stringToCameraType(const std::string type);
	void setupBossCamera(const ci::JsonTree tree);
};