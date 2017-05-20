#pragma once
#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"
class Player;
enum CamaraUpdateType {
	PLAYER_CAMERA,EVENT_CAMERA,X_LOCK_CAMERA, Y_LOCK_CAMERA, XY_LOCK_CAMERA,CAMERA_TYPE_MAX
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
	void setPlayerPos(const ci::Vec3f _pos);
	void setCameraUpdateType(const CamaraUpdateType _cameratype);
	void setPlayerSpeed(const ci::Vec3f _speed);
    bool getDeathCameraEnd();
	void setDeatCameraT(float _t);
	CamaraUpdateType getCameraUpdateType();
	CamaraUpdateType JsonReadCameraType(const int worldnum, const int stagenum, const int floornum);
	ci::Vec3f getSetEyePointTrance();
	ci::Vec3f getSetCenterofinterestPointTrance();
	void updateCameraTrance();
	void ResetT();
private:
	ci::Vec3f prevcenterrofinterstpoint;
	ci::Vec2f minvalue;
	ci::Vec2f maxvalue;
	ci::Vec3f playerpos;
	ci::Vec3f playerspeed;
	CamaraUpdateType cameraupdatetype;
	ci::Vec3f seteyepoint;
	ci::Vec3f setcenterofinterestpoint;
	ci::Vec3f seteyepointtrance = ci::Vec3f(0, 0, 0);
	ci::Vec3f setcenterofinterestpointtrance = ci::Vec3f(0, 0, 0);
	bool isplayerrightmove;
	float trancex_t;
	float cameratrancex;
	float begincameratrancex;
	float endcameratrancex;
	float trancemaxvalue;
	float cameralockpos_x;
	float cameralockeyepos_y;
	float lockcenterofinterestpoint_y;
	float deathcamera_t=0.0f;
	float deathdelay_t = 0.0f;
	bool deathcameraend = false;
	void updatePlayerCameraType();
	void updateEventCameraType();
	void updateXLockCameraType();
	void updateYLockCameraType();
	void updateXYLockCameraType();
	
	CamaraUpdateType stringToCameraType(const std::string type);

};