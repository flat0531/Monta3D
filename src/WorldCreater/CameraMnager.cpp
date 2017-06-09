#include "CameraMnager.h"
#include"../Top/Top.h"
#include"../Top/EasingManager.h"
#include"../Top/MyJson.h"
#include"../Top/SoundManager.h"
#include"../WorldObject/CharacterBase.h"
using namespace ci;
using namespace ci::app;
CameraManager::CameraManager()
{
	cameraupdatetype = CamaraUpdateType::PLAYER_CAMERA;
	cameraupdatetype = CamaraUpdateType::X_LOCK_CAMERA;
	setMinValue(Vec2f(0, 0));
	begincameratrancex = 0.0f;
	trancemaxvalue = 1.5f*WorldScale;
	endcameratrancex = -trancemaxvalue;
	cameralockpos_x = 0.0f;
	cameralockeyepos_y = 0.0f;
	lockcenterofinterestpoint_y = 0.0f;
	deathcamera_t = 0.0f;
	cameratrancex = 0.0f;
	trancex_t = 0.0f;
	isplayerrightmove = true;
	SoundM.CreateSE("montavoice.wav");
}

void CameraManager::update()
{
	deathcameraend = false;

	switch (cameraupdatetype)
	{
	case PLAYER_CAMERA:
		updatePlayerCameraType();
		break;
	case EVENT_CAMERA:
		updateEventCameraType();
		break;
	case X_LOCK_CAMERA:
		updateXLockCameraType();
		break;
	case Y_LOCK_CAMERA:
		updateYLockCameraType();
		break;
	case XY_LOCK_CAMERA:
		updateXYLockCameraType();
		break;
	case CAMERA_TYPE_MAX:
		break;
	default:
		break;
	}
}

void CameraManager::setMinValue(const ci::Vec2f _minvalue)
{
	minvalue = _minvalue;
}

void CameraManager::setMaxValue(const ci::Vec2f _maxvalue)
{
	maxvalue = _maxvalue;
}

void CameraManager::unitPrevCenterOfInterestPoint(const ci::Vec3f prevpos)
{
	prevcenterrofinterstpoint = prevpos;
}


bool CameraManager::getDeathCameraEnd()
{
	return deathcameraend;
}

void CameraManager::setDeatCameraT(float _t)
{
	deathcamera_t = _t;
}

void CameraManager::updatePlayerCameraType()
{
	/////////y軸徐々にプレイヤーのポスに近づける///////////
	float cameraposy;
	cameraposy = 2.f * WorldScale + playerptr->getPos().y;
	cameraposy = std::min(cameraposy, maxvalue.y - 3.f * WorldScale);//上限
	cameraposy = std::max(cameraposy, 2.f * WorldScale);//下限
	float trancespeed = 40.f;//プレイヤーがカメラから上に向かっているとき遅く
	if (((cameraposy - 2.f * WorldScale) - prevcenterrofinterstpoint.y)<=0.0f)trancespeed = 10.0f;//プレイヤーがカメラから上に向かっているとき素早く
	//カメラを前のフレームから少し目的値まで近づける
	setcenterofinterestpoint.y = prevcenterrofinterstpoint.y+(((cameraposy-2.f*WorldScale)-prevcenterrofinterstpoint.y) / trancespeed);
	///////////////////////////////////////////////////


	///////////x軸をプレイヤーの進行方向別にイージング///////////
	
	float easingtime = 2.0f;
	EasingManager::tCount(trancex_t, easingtime);

	if (isplayerrightmove) {
		if (playerptr->getSpeed().x > 0) {
			isplayerrightmove = false;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = trancemaxvalue;
		}
	}
	else {
		if (playerptr->getSpeed().x < 0) {
			isplayerrightmove = true;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = -trancemaxvalue;
		}
	}

	float centerofinterestpointx = playerptr->getPos().x+cameratrancex*1.5f;
	centerofinterestpointx = std::min(centerofinterestpointx, -minvalue.x - WorldScale * 17.f);
	centerofinterestpointx = std::max(centerofinterestpointx, -maxvalue.x + WorldScale * 17.f);

	cameratrancex = EasingQuadOut(trancex_t, begincameratrancex, endcameratrancex);

	float seteyepointx = playerptr->getPos().x + cameratrancex;
	seteyepointx = std::min(seteyepointx, -minvalue.x - WorldScale * 19.f);
	seteyepointx = std::max(seteyepointx, -maxvalue.x + WorldScale * 19.f);

	//////////////////////////////////////////////////////////////

	seteyepoint = Vec3f(seteyepointx,
		setcenterofinterestpoint.y+2*WorldScale,
		-10.5f*WorldScale);

	setcenterofinterestpoint = Vec3f(centerofinterestpointx,
		setcenterofinterestpoint.y,
		playerptr->getPos().z);


	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateEventCameraType()
{
	
}

void CameraManager::updateXLockCameraType()
{
	float cameraposy;
	cameraposy = 2 * WorldScale + playerptr->getPos().y;
	cameraposy = std::min(cameraposy, maxvalue.y - 3 * WorldScale);//上限
	cameraposy = std::max(cameraposy, 2 * WorldScale);//下限
	float trancespeed = 40.f;//プレイヤーがカメラから上に向かっているとき遅く
	if (((cameraposy - 2 * WorldScale) - prevcenterrofinterstpoint.y) <= 0.0f)trancespeed = 10.0f;//プレイヤーがカメラから上に向かっているとき素早く
																								  //カメラを前のフレームから少し目的値まで近づける
	setcenterofinterestpoint.y = prevcenterrofinterstpoint.y + (((cameraposy - 2 * WorldScale) - prevcenterrofinterstpoint.y) / trancespeed);


	seteyepoint = Vec3f(cameralockpos_x,
		setcenterofinterestpoint.y + 2 * WorldScale,
		-10.5*WorldScale);

	setcenterofinterestpoint = Vec3f(cameralockpos_x,
		setcenterofinterestpoint.y,
		playerptr->getPos().z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateYLockCameraType()
{

	float easingtime = 2.0f;
	EasingManager::tCount(trancex_t, easingtime);

	if (isplayerrightmove) {
		if (playerptr->getSpeed().x > 0) {
			isplayerrightmove = false;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = trancemaxvalue;
		}
	}
	else {
		if (playerptr->getSpeed().x < 0) {
			isplayerrightmove = true;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = -trancemaxvalue;
		}
	}


	float centerofinterestpointx = playerptr->getPos().x + cameratrancex*1.5f;
	centerofinterestpointx = std::min(centerofinterestpointx, -minvalue.x - WorldScale * 17.f);
	centerofinterestpointx = std::max(centerofinterestpointx, -maxvalue.x + WorldScale * 17.f);

	cameratrancex = EasingQuadOut(trancex_t, begincameratrancex, endcameratrancex);

	float seteyepointx = playerptr->getPos().x + cameratrancex;
	seteyepointx = std::min(seteyepointx, -minvalue.x - WorldScale * 19.f);
	seteyepointx = std::max(seteyepointx, -maxvalue.x + WorldScale * 19.f);

	//////////////////////////////////////////////////////////////

	seteyepoint = Vec3f(seteyepointx,
		cameralockeyepos_y,
		-10.5*WorldScale);
	setcenterofinterestpoint = Vec3f(centerofinterestpointx,
		lockcenterofinterestpoint_y,
		playerptr->getPos().z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateXYLockCameraType()
{
	seteyepoint = Vec3f(cameralockpos_x,
		cameralockeyepos_y,
		-10.5*WorldScale);
	setcenterofinterestpoint = Vec3f(cameralockpos_x,
		lockcenterofinterestpoint_y,
		playerptr->getPos().z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateCameraTrance()
{
	if (EasingManager::tCountEnd(deathdelay_t))return;

	if (EasingManager::tCountEnd(deathcamera_t)) {
		EasingManager::tCount(deathdelay_t, 1.0f);
		if (EasingManager::tCountEnd(deathdelay_t)){
			deathcameraend = true;
		}
	}
	else {
		EasingManager::tCount(deathcamera_t, 0.5f);
		if (EasingManager::tCountEnd(deathcamera_t)) {
			SoundM.FadeNowBGM(0.0f, 1.0f);
			SoundM.PlaySE("montavoice.wav");
		}
		float value = EasingLinear(deathcamera_t, 150.f, 0);
		float speed = 50.f;
		float length = value*sin(deathcamera_t*speed);
		setcenterofinterestpointtrance.x = -length*cos(M_PI / 4.f);
		setcenterofinterestpointtrance.y = length*sin(M_PI / 4.f);
		seteyepointtrance.x = -length*cos(M_PI / 4.f);
		seteyepointtrance.y = length*sin(M_PI / 4.f);
	}

}

void CameraManager::ResetT()
{
	deathcamera_t = 0.0f;
	deathdelay_t = 0.0f;
	deathcameraend = false;
}

CamaraUpdateType CameraManager::stringToCameraType(const std::string type)
{

	if (type == "player") {
		return PLAYER_CAMERA;
	}
	if (type == "xlock") {
		return X_LOCK_CAMERA;
	}
	if (type == "ylock") {
		return Y_LOCK_CAMERA;
	}
	if (type == "xylock") {
		return XY_LOCK_CAMERA;
	}
	console() << "失敗" << std::endl;
	return PLAYER_CAMERA;
}

CamaraUpdateType CameraManager::JsonReadCameraType(const int worldnum, const int stagenum, const int floornum)
{
	std::string path = "Json/Stage/World" + std::to_string(worldnum) +
		"/Stage" + std::to_string(stagenum);
	JsonTree camerajson(loadAsset(path + "/camera.json"));
	JsonTree child = camerajson.getChild(floornum - 1);
	std::string typestr = child.getValueForKey<std::string>("cameratype");
	CamaraUpdateType type = stringToCameraType(typestr);

	switch (type)
	{
	case X_LOCK_CAMERA:
		if (child.hasChild("pos")) {
			cameralockpos_x = child.getValueForKey<float>("pos")*WorldScale;
		}
		else {
			cameralockpos_x = -maxvalue.x / 2.f;
		}
		break;
	case Y_LOCK_CAMERA:
		if (child.hasChild("eyepos")) {
			cameralockeyepos_y = child.getValueForKey<float>("eyepos")*WorldScale;
		}
		else {
			cameralockeyepos_y = maxvalue.y / 2.f;
		}
		if (child.hasChild("center")) {
			lockcenterofinterestpoint_y = child.getValueForKey<float>("center")*WorldScale;
		}
		else {
			lockcenterofinterestpoint_y = maxvalue.y / 2.f;
		}
		break;
	case XY_LOCK_CAMERA:
		if (child.hasChild("posx")) {
			cameralockpos_x = child.getValueForKey<float>("posx")*WorldScale;
		}
		else {
			cameralockpos_x = -maxvalue.x / 2.f;
		}
		if (child.hasChild("posy")) {
			cameralockeyepos_y = child.getValueForKey<float>("posy")*WorldScale;
		}
		else {
			cameralockeyepos_y = maxvalue.y / 2.f;
		}
		if (child.hasChild("centery")) {
			lockcenterofinterestpoint_y = child.getValueForKey<float>("centery")*WorldScale;
		}
		else {
			lockcenterofinterestpoint_y = maxvalue.y / 2.f;
		}
		break;
	default:
		break;
	}

	return type;
}

ci::Vec3f CameraManager::getSetEyePointTrance()
{
	return seteyepointtrance;
}

ci::Vec3f CameraManager::getSetCenterofinterestPointTrance()
{
	return setcenterofinterestpointtrance;
}
ci::Vec3f CameraManager::getSetEyePoint()
{
	return seteyepoint;
}

ci::Vec3f CameraManager::getSetCenterofinterestPoint()
{
	return setcenterofinterestpoint;
}



void CameraManager::setCameraUpdateType(const CamaraUpdateType _cameratype)
{
	cameraupdatetype = _cameratype;
}

CamaraUpdateType CameraManager::getCameraUpdateType()
{
	return cameraupdatetype;
}

void CameraManager::setPlayerPtr(CharacterBase * _playerptr)
{
	playerptr = _playerptr;
}