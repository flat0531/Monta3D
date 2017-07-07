#include "CameraMnager.h"
#include"../Top/Top.h"
#include"../Top/EasingManager.h"
#include"../Top/MyJson.h"
#include"../Top/SoundManager.h"
#include"../WorldObject/CharacterBase.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldObject/Effect/EffectBossDeath.h"
#include"../WorldObject/Effect/EffectWorldClear.h"
#include"../Top/DataManager.h"
#include"cinder\Rand.h"
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
	SoundM.CreateSE("enemy_die.wav");
	SoundM.CreateSE("stageclear.wav");
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
	case BOSS_CAMERA:
		updateBossCameraType();
		break;
	case BOSS_EFFECT_END:
		updateBossDeathEffectCamera();
		break;
	case CAMERA_TYPE_MAX:
		break;
	default:
		break;
	}
	updateShake();
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

void CameraManager::updateShake()
{
	if (isshake) {
		EasingManager::tCount(shaketime_t,shaketime);
		shakeeyepoint = Vec3f(randFloat(-shakevalue,shakevalue), randFloat(-shakevalue, shakevalue),0);
		shakecenterpoint = Vec3f(randFloat(-shakevalue, shakevalue), randFloat(-shakevalue, shakevalue), 0);
		if (EasingManager::tCountEnd(shaketime_t)) {
			isshake = false;
		}
	}
	else {
		shakeeyepoint = Vec3f(0, 0, 0);
		shakecenterpoint = Vec3f(0, 0, 0);
	}
}

void CameraManager::updatePlayerCameraType()
{
	/////////y軸徐々にプレイヤーのポスに近づける///////////
	float cameraposy;
	cameraposy = 1.5f * WorldScale + playerptr->getPos().y;
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
	cameraposy = 1.5 * WorldScale + playerptr->getPos().y;
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

void CameraManager::updateBossCameraType()
{

	for (int i = 0;i < event_t.size();i++) {
		if (!EasingManager::tCountEnd(event_t[i])) {
			EasingManager::tCount(event_t[i],easingtime[i]);
			seteyepoint.x = EasingManager::getEas[easingtypeseye[i].x](event_t[i], eyebeginpos[i].x, eyeendpos[i].x);
			seteyepoint.y = EasingManager::getEas[easingtypeseye[i].y](event_t[i], eyebeginpos[i].y, eyeendpos[i].y);
			seteyepoint.z = EasingManager::getEas[easingtypeseye[i].z](event_t[i], eyebeginpos[i].z, eyeendpos[i].z);

			setcenterofinterestpoint.x = EasingManager::getEas[easingtypescenter[i].x](event_t[i], eyecenterbeginpos[i].x, eyecenterendpos[i].x);
			setcenterofinterestpoint.y = EasingManager::getEas[easingtypescenter[i].y](event_t[i], eyecenterbeginpos[i].y, eyecenterendpos[i].y);
			setcenterofinterestpoint.z = EasingManager::getEas[easingtypescenter[i].z](event_t[i], eyecenterbeginpos[i].z, eyecenterendpos[i].z);
			break;
		}
		
	}



	//seteyepoint = Vec3f(cameralockpos_x,
	//	cameralockeyepos_y,
	//	-10.5*WorldScale);
	//setcenterofinterestpoint = Vec3f(cameralockpos_x,
	//	lockcenterofinterestpoint_y,
	//	playerptr->getPos().z);
	//prevcenterrofinterstpoint = setcenterofinterestpoint;
}

void CameraManager::updateBossDeathEffectCamera()
{
	if (!EasingManager::tCountEnd(bossrotate_t)) {
		EasingManager::tCount(bossrotate_t, 5.0f);
		bosssinrotateangle += 0.11f;
		CreateBossEffect();
		seteyepoint = Vec3f(-11.25*WorldScale + 10.f*cos(bosssinrotateangle)*WorldScale,
			8 * WorldScale,
			35.f*WorldScale + 10.f*sin(bosssinrotateangle)*WorldScale);
		setcenterofinterestpoint = Vec3f(-11.25*WorldScale,
			3 * WorldScale,
			35.f * WorldScale);
		prevcenterrofinterstpoint = setcenterofinterestpoint;
		if (EasingManager::tCountEnd(bossrotate_t)) {
			rotateeyepoint = seteyepoint;
			rotateeyecenterpoint = setcenterofinterestpoint;
			SoundM.StopSE("rope.wav");
		}
	}
	else {
		if (!EasingManager::tCountEnd(bosstoplayer_t)) {
			EasingManager::tCount(bosstoplayer_t, 2.0f);
			seteyepoint.x = EasingCubicOut(bosstoplayer_t, rotateeyepoint.x, -15.25*WorldScale);
			seteyepoint.y = EasingCubicOut(bosstoplayer_t, rotateeyepoint.y, 4.f*WorldScale);
			seteyepoint.z = EasingCubicOut(bosstoplayer_t, rotateeyepoint.z, 4.5f*WorldScale);

			setcenterofinterestpoint.x = EasingCubicOut(bosstoplayer_t, rotateeyecenterpoint.x, -10.25*WorldScale);
			setcenterofinterestpoint.y = EasingCubicOut(bosstoplayer_t, rotateeyecenterpoint.y, 2.f*WorldScale);
			setcenterofinterestpoint.z = EasingCubicOut(bosstoplayer_t, rotateeyecenterpoint.z, 0.f*WorldScale);
			if (EasingManager::tCountEnd(bosstoplayer_t)) {
				SoundM.PlaySE("stageclear.wav");
				effectmanager->CreateEffect2D(EffectWorldClear(DataM.getWorldNum()));
			}
		}
		
	}
	if (EasingManager::tCountEnd(bosstoplayer_t)) {
		EasingManager::tCount(bossdelay_t, 7.5f);
	}
}

void CameraManager::updateBlackWall()
{
	
}

void CameraManager::CreateBossEffect()
{
	createbosseffectcount++;
	
	if (createbosseffectcount % 5 == 0) {
		float scale = randFloat(2.f*WorldScale, 4.f*WorldScale);
		SoundM.PlaySE("enemy_die.wav");
		effectmanager->CreateEffect(EffectBossDeath(Vec3f(-11.25*WorldScale, 5.f*WorldScale, 35.f*WorldScale)
			+ Vec3f(randFloat(-8.f*WorldScale, 8.f*WorldScale),
				randFloat(-3.f*WorldScale, 3.f*WorldScale),
				randFloat(-8.f*WorldScale, 8.f*WorldScale)),
			Vec3f(scale, scale, scale), randFloat(0.5f, 1.0f)));
	}
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
	shaketime_t = 0.0f;
	isshake = false;
	bosssinrotateangle = 0.0f;
	createbosseffectcount = 0;
	bossrotate_t = 0.0f;
	bosstoplayer_t = 0.0f;
	bossdelay_t = 0.0f;
}

CameraManager * CameraManager::getThisPtr()
{
	return this;
}

void CameraManager::Shake(const float value, const float time)
{
	isshake = true;
	shaketime_t = 0.0f;
	shakevalue = value;
	shaketime = time;
}

ci::Vec3f CameraManager::getShakeEyePoint()
{
	return shakeeyepoint;
}

ci::Vec3f CameraManager::getShakeCenterPoint()
{
	return shakecenterpoint;
}

bool CameraManager::getIsBossDelayEnd()
{
	return EasingManager::tCountEnd(bossdelay_t);
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
	if (type == "boss") {
		return BOSS_CAMERA;
	}
	console() << "失敗" << std::endl;
	return PLAYER_CAMERA;
}

void CameraManager::setupBossCamera(const ci::JsonTree tree)
{
	easingtime.clear();
	event_t.clear();
	eyebeginpos.clear();
	eyeendpos.clear();
	eyecenterbeginpos.clear();
	eyecenterendpos.clear();
	easingtypeseye.clear();
	easingtypescenter.clear();
	{
		JsonTree easingtimes = tree.getChild("easingtime");
		for (size_t i = 0; i < easingtimes.getNumChildren(); i++)
		{
			easingtime.push_back(easingtimes.getValueAtIndex<float>(i));
			event_t.push_back(0.0f);
		}
	}
	{
		JsonTree easingeyebehgin_s = tree.getChild("easingbegin");
		for (size_t i = 0; i < easingeyebehgin_s.getNumChildren(); i++)
		{
			JsonTree easingeyebegin = easingeyebehgin_s.getChild(i);
			eyebeginpos.push_back(JsonM.getVec3(easingeyebegin, "")*WorldScale);
		}
	}
	
	{
		JsonTree easingeyeend_s = tree.getChild("easingend");
		for (size_t i = 0; i < easingeyeend_s.getNumChildren(); i++)
		{
			JsonTree easingeyeend = easingeyeend_s.getChild(i);
			eyeendpos.push_back(JsonM.getVec3(easingeyeend, "")*WorldScale);
		}
	}
	
	{
		JsonTree easingeyecenterbegin_s = tree.getChild("easingcenterbegin");
		for (size_t i = 0; i <easingeyecenterbegin_s.getNumChildren(); i++)
		{
			JsonTree easingeycenterbegin = easingeyecenterbegin_s.getChild(i);
			eyecenterbeginpos.push_back(JsonM.getVec3(easingeycenterbegin, "")*WorldScale);
		}
	}

	{
		JsonTree easingcenterend_s = tree.getChild("easingcenterend");
		for (size_t i = 0; i < easingcenterend_s.getNumChildren(); i++)
		{
			JsonTree easingeyecenterend = easingcenterend_s.getChild(i);
			eyecenterendpos.push_back(JsonM.getVec3(easingeyecenterend, "")*WorldScale);
		}
	}

	{
		JsonTree easingtype = tree.getChild("easingtypeeye");
		for (size_t i = 0; i <easingtype.getNumChildren(); i++)
		{
			JsonTree easingeycenterbegin = easingtype.getChild(i);
			easingtypeseye.push_back(JsonM.getVec3i(easingeycenterbegin, ""));
		}
	}
	{
		JsonTree easingtype = tree.getChild("easingtypecenter");
		for (size_t i = 0; i <easingtype.getNumChildren(); i++)
		{
			JsonTree easingeycenterbegin = easingtype.getChild(i);
			easingtypescenter.push_back(JsonM.getVec3i(easingeycenterbegin, ""));
		}
	}
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
	case BOSS_CAMERA:
		setupBossCamera(child);
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

void CameraManager::setEffectManagerPtr(EffectManager * _effectmanager)
{
	effectmanager = _effectmanager;
}

CamaraUpdateType CameraManager::getCameraUpdateType()
{
	return cameraupdatetype;
}

void CameraManager::setPlayerPtr(CharacterBase * _playerptr)
{
	playerptr = _playerptr;
}