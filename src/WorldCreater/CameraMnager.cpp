#include "CameraMnager.h"
#include"../Top/Top.h"
#include"../Top/EasingManager.h"
#include"../Top/MyJson.h"
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
	cameratrancex = 0.0f;
	trancex_t = 0.0f;
	isplayerrightmove = true;
}

void CameraManager::update()
{
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

void CameraManager::setPlayerSpeed(const ci::Vec3f _speed)
{
	playerspeed = _speed;
}

void CameraManager::updatePlayerCameraType()
{
	/////////y�����X�Ƀv���C���[�̃|�X�ɋ߂Â���///////////
	float cameraposy;
	cameraposy = 2 * WorldScale + playerpos.y;
	cameraposy = std::min(cameraposy, maxvalue.y - 3 * WorldScale);//���
	cameraposy = std::max(cameraposy, 2 * WorldScale);//����
	float trancespeed = 40.f;//�v���C���[���J���������Ɍ������Ă���Ƃ��x��
	if (((cameraposy - 2 * WorldScale) - prevcenterrofinterstpoint.y)<=0.0f)trancespeed = 10.0f;//�v���C���[���J���������Ɍ������Ă���Ƃ��f����
	//�J������O�̃t���[�����班���ړI�l�܂ŋ߂Â���
	setcenterofinterestpoint.y = prevcenterrofinterstpoint.y+(((cameraposy-2*WorldScale)-prevcenterrofinterstpoint.y) / trancespeed);
	///////////////////////////////////////////////////


	///////////x�����v���C���[�̐i�s�����ʂɃC�[�W���O///////////
	
	float easingtime = 2.0f;
	EasingManager::tCount(trancex_t, easingtime);

	if (isplayerrightmove) {
		if (playerspeed.x > 0) {
			isplayerrightmove = false;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = trancemaxvalue;
		}
	}
	else {
		if (playerspeed.x < 0) {
			isplayerrightmove = true;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = -trancemaxvalue;
		}
	}

	float centerofinterestpointx = playerpos.x+cameratrancex*1.5f;
	centerofinterestpointx = std::min(centerofinterestpointx, -minvalue.x - WorldScale * 17.f);
	centerofinterestpointx = std::max(centerofinterestpointx, -maxvalue.x + WorldScale * 17.f);

	cameratrancex = EasingQuadOut(trancex_t, begincameratrancex, endcameratrancex);

	float seteyepointx = playerpos.x + cameratrancex;
	seteyepointx = std::min(seteyepointx, -minvalue.x - WorldScale * 19.f);
	seteyepointx = std::max(seteyepointx, -maxvalue.x + WorldScale * 19.f);

	//////////////////////////////////////////////////////////////

	seteyepoint = Vec3f(seteyepointx,
		setcenterofinterestpoint.y+2*WorldScale,
		-10.5*WorldScale);
	setcenterofinterestpoint = Vec3f(centerofinterestpointx,
		setcenterofinterestpoint.y,
		playerpos.z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateEventCameraType()
{
	
}

void CameraManager::updateXLockCameraType()
{
	float cameraposy;
	cameraposy = 2 * WorldScale + playerpos.y;
	cameraposy = std::min(cameraposy, maxvalue.y - 3 * WorldScale);//���
	cameraposy = std::max(cameraposy, 2 * WorldScale);//����
	float trancespeed = 40.f;//�v���C���[���J���������Ɍ������Ă���Ƃ��x��
	if (((cameraposy - 2 * WorldScale) - prevcenterrofinterstpoint.y) <= 0.0f)trancespeed = 10.0f;//�v���C���[���J���������Ɍ������Ă���Ƃ��f����
																								  //�J������O�̃t���[�����班���ړI�l�܂ŋ߂Â���
	setcenterofinterestpoint.y = prevcenterrofinterstpoint.y + (((cameraposy - 2 * WorldScale) - prevcenterrofinterstpoint.y) / trancespeed);


	seteyepoint = Vec3f(cameralockpos_x,
		setcenterofinterestpoint.y + 2 * WorldScale,
		-10.5*WorldScale);

	setcenterofinterestpoint = Vec3f(cameralockpos_x,
		setcenterofinterestpoint.y,
		playerpos.z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateYLockCameraType()
{

	///////////x�����v���C���[�̐i�s�����ʂɃC�[�W���O///////////

	float easingtime = 2.0f;
	EasingManager::tCount(trancex_t, easingtime);

	if (isplayerrightmove) {
		if (playerspeed.x > 0) {
			isplayerrightmove = false;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = trancemaxvalue;
		}
	}
	else {
		if (playerspeed.x < 0) {
			isplayerrightmove = true;
			trancex_t = 0.0f;
			begincameratrancex = cameratrancex;
			endcameratrancex = -trancemaxvalue;
		}
	}


	float centerofinterestpointx = playerpos.x + cameratrancex*1.5f;
	centerofinterestpointx = std::min(centerofinterestpointx, -minvalue.x - WorldScale * 17.f);
	centerofinterestpointx = std::max(centerofinterestpointx, -maxvalue.x + WorldScale * 17.f);

	cameratrancex = EasingQuadOut(trancex_t, begincameratrancex, endcameratrancex);

	float seteyepointx = playerpos.x + cameratrancex;
	seteyepointx = std::min(seteyepointx, -minvalue.x - WorldScale * 19.f);
	seteyepointx = std::max(seteyepointx, -maxvalue.x + WorldScale * 19.f);

	//////////////////////////////////////////////////////////////

	seteyepoint = Vec3f(seteyepointx,
		cameralockeyepos_y,
		-10.5*WorldScale);
	setcenterofinterestpoint = Vec3f(centerofinterestpointx,
		lockcenterofinterestpoint_y,
		playerpos.z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateXYLockCameraType()
{
	seteyepoint = Vec3f(cameralockpos_x,
		cameralockeyepos_y,
		-10.5*WorldScale);
	setcenterofinterestpoint = Vec3f(cameralockpos_x,
		lockcenterofinterestpoint_y,
		playerpos.z);
	prevcenterrofinterstpoint = setcenterofinterestpoint;
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
	console() << "���s" << std::endl;
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



ci::Vec3f CameraManager::getSetEyePoint()
{
	return seteyepoint;
}

ci::Vec3f CameraManager::getSetCenterofinterestPoint()
{
	return setcenterofinterestpoint;
}

void CameraManager::setPlayerPos(const ci::Vec3f _pos)
{
	playerpos = _pos;
}

void CameraManager::setCameraUpdateType(const CamaraUpdateType _cameratype)
{
	cameraupdatetype = _cameratype;
}

CamaraUpdateType CameraManager::getCameraUpdateType()
{
	return cameraupdatetype;
}