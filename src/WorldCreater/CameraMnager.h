#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
#include"cinder\Json.h"
class CharacterBase;
enum CamaraUpdateType {
	PLAYER_CAMERA,EVENT_CAMERA,X_LOCK_CAMERA, Y_LOCK_CAMERA, XY_LOCK_CAMERA,BOSS_CAMERA,CAMERA_TYPE_MAX
};
class CameraManager {
public:
	CameraManager();
	void update();
	void setMinValue(const ci::Vec2f _minvalue);
	void setMaxValue(const ci::Vec2f _maxvalue);
	void unitPrevCenterOfInterestPoint(const ci::Vec3f prevpos);
	ci::Vec3f getSetEyePoint();
	ci::Vec3f getSetCenterofinterestPoint();
	void setCameraUpdateType(const CamaraUpdateType _cameratype);
    bool getDeathCameraEnd();
	void setDeatCameraT(float _t);
	CamaraUpdateType getCameraUpdateType();
	void setPlayerPtr(class CharacterBase* _playerptr);
	CamaraUpdateType JsonReadCameraType(const int worldnum, const int stagenum, const int floornum);
	ci::Vec3f getSetEyePointTrance();
	ci::Vec3f getSetCenterofinterestPointTrance();
	void updateCameraTrance();
	void ResetT();
	void drawBlackWall();
	CameraManager* getThisPtr();
	void Shake(const float value,const float time);
	ci::Vec3f getShakeEyePoint();
	ci::Vec3f getShakeCenterPoint();
private:
	ci::Vec3f prevcenterrofinterstpoint;
	ci::Vec2f minvalue;
	ci::Vec2f maxvalue;
	CamaraUpdateType cameraupdatetype;
	CharacterBase* playerptr;
	ci::Vec3f seteyepoint;
	ci::Vec3f setcenterofinterestpoint;
	ci::Vec3f seteyepointtrance = ci::Vec3f(0, 0, 0);
	ci::Vec3f setcenterofinterestpointtrance = ci::Vec3f(0, 0, 0);
	ci::Vec3f shakeeyepoint = ci::Vec3f(0, 0, 0);
	ci::Vec3f shakecenterpoint = ci::Vec3f(0, 0, 0);
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
	void updateBlackWall();
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