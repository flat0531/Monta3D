#include "BigPumpkin.h"
#include"../WorldObject/Boss.h"
#include"../Top/Top.h"
#include"../Top/DrawManager.h"
#include"../WorldCreater/BulletManager.h"
#include"../WorldCreater/CharacterManager.h"
#include"../Top/TextureManager.h"
#include"../Top/EasingManager.h"
#include"../Top/DataManager.h"
#include"cinder\Rand.h"
#include"../WorldCreater/CameraMnager.h"
#include"../Top/SoundManager.h"
#include"../WorldCreater/EffectManager.h"
#include"../WorldCreater/MapChipManager.h"
#include"../WorldObject/Effect/EffectBlackBox.h"
#include"../WorldObject/Effect/EffectBossName.h"
#include"../WorldObject/Effect/EffectColored.h"
#include"../WorldObject/Bullet/WideShotBullet.h"
#include"../WorldObject/Bullet/ColorShotBullet.h"
#include"../WorldObject/Bullet/FireBullet.h"
#include"../WorldObject/Bullet/BarrierBullet.h"
#include"../WorldObject/Bullet/BlackScaleBullet.h"
#include"../WorldObject/Bullet/MyToras.h"
#include"../WorldObject/MapChip/MapChipBase.h"
#include"../WorldObject/MapChip/MapChipNone.h"
#include"../WorldObject/MapChip/MapChipColored.h"

using namespace ci;
using namespace ci::app;
BigPumpkin::BigPumpkin()
{
}

BigPumpkin::BigPumpkin(CharacterBase * _enemy)
{
	bossptr = dynamic_cast<Boss*>(_enemy);
	maxjumppower = 0.085f*WorldScale;
	jumppower = maxjumppower;
	int maxhp = 350;
	bossptr->setMaxHp(maxhp);
	basepos = bossptr->getPos();
	createAsset();
	bossptr->setScale(Vec3f(7, 4, 7)*WorldScale);
	bossptr->setRotate(Vec3f(0, 180, 0));
	bossptr->setQuat(Quatf(0, M_PI, 0));
	bossptr->setHp(maxhp);
	bossptr->setDefalutColor(ColorA(1, 1, 1, 1));
	bossptr->setColor(ColorA(1, 1, 1, 1));
	bossptr->setName("PumpkyDumpty");
	bossptr->setUniqueColor(DataM.getColor("orange"));

	isbegineffect = false;
	begineffectcount = 0;
	controlcount = 0;

	SoundM.StopNowBGM();
	SoundM.PlayBGM("lastboss.wav",0.55f);
	SoundM.SetLoopBGM("lastboss.wav", true);
	createRainbowColor();

	bossptr->getEffectManagerPointer()->CreateEffect2D(EffectBlackBox(0.5f, 11.f));
	nextcandidate.clear();
	nextcandidate.push_back(DROP);
}

void BigPumpkin::update()
{
	updateBeginEffect();
	rotateEasing();
	mainUpdate();
}

void BigPumpkin::draw()
{

	//DrawM.drawStrokeCube(bossptr->getPos(),bossptr->getScale(),Vec3f(0,0,0),ColorA(0,0,0,1));


	gl::pushModelView();
	float drawscalecorrection = 45.f;
	float drawposcorrection = -WorldScale*2.f;
	gl::translate(bossptr->getPos() + Vec3f(0, drawposcorrection, 0));
	gl::rotate(bossptr->getRotate());
	gl::scale(Vec3f(bossptr->getScale().x, bossptr->getScale().x, bossptr->getScale().z) / drawscalecorrection);
	gl::color(bossptr->getColor());
	TextureM.getTexture("Mesh/kingKabotya.png").enableAndBind();
	gl::draw(TextureM.getMesh("kingKabotya.obj"));
	TextureM.getTexture("Mesh/kingKabotya.png").disable();
	gl::popModelView();
}

void BigPumpkin::attack()
{

}

void BigPumpkin::updateBeginEffect()
{
	if (isbegineffect)return;
	if (begineffectcount == (60 * 8)) {
		rotateStart();
	}
	if (begineffectcount == ((60 * 5)+1)) {
		SoundM.PlaySE("wind.wav");
	}
	if (begineffectcount == ((60 * 7))) {
		bossptr->getEffectManagerPointer()->CreateEffect2D(EffectBossName("UI/world1bossname.png"));
	}
	if (begineffectcount == ((60 * 8)+30)) {
		SoundM.PlaySE("bossvoice.wav",1.0f);
		bossptr->getCameraManager()->Shake(50.f, 2.f);
	}
	if (begineffectcount == ((60 * 10) + 30)) {
		SoundM.PlaySE("gage.wav", 1.0f);
		bossptr->setIsBeginEffectEnd(true);
		isbegineffect = true;
	}
	begineffectcount++;
}

void BigPumpkin::rotateStart()
{
	isrotate = true;
	rotate_easing_t = 0.0f;
}

void BigPumpkin::rotateEasing()
{
	if (isrotate) {
		EasingManager::tCount(rotate_easing_t, 0.5f);
		bossptr->setRotateY(EasingCubicOut(rotate_easing_t, 540.f, 180.f));
		if (EasingManager::tCountEnd(rotate_easing_t)) {
			isrotate = false;
			rotate_easing_t = 0.0f;
		}
	}
}

bool BigPumpkin::getIsHpHalf()
{
	return bossptr->getHp()<=(bossptr->getMaxHp()/2);
}

void BigPumpkin::createAsset()
{
	TextureM.CreateMesh("kingKabotya.obj");
	TextureM.CreateTexture("Mesh/kingKabotya.png");
	TextureM.CreateTexture("UI/world1bossname.png");
	TextureM.CreateTexture("UI/blood.png");
	
	SoundM.CreateSE("bossvoice.wav");
	SoundM.CreateSE("wind.wav");
	SoundM.CreateSE("gage.wav");
	SoundM.CreateSE("quake.wav");
	SoundM.CreateSE("oscillation.wav");
	SoundM.CreateSE("wideshot.wav");
	SoundM.CreateSE("colorcharge.wav");
	SoundM.CreateSE("colorchargeshot.wav");
	SoundM.CreateSE("colorblood.wav");
	SoundM.CreateSE("rope.wav");
}

void BigPumpkin::mainUpdate()
{
	if (!isbegineffect)return;
	switch (updatetype)
	{
	case STANDBY:
		updateStandby();
		break;
	case DROP:
		updateDrop();
		break;
	case WIDESHOT:
		updateWideshot();
		break;
	case COLORSHOT:
		updateColorshot();
		break;
	case BARRIERSHOT:
		updateBarriershot();
		break;
	case JUMPROPE:
		updateJumpRope();
		break;
	default:
		break;
	}
}
void BigPumpkin::updateStandby()
{
	mainupdatecount++;
	standby_sinangle += 0.02f;
	bossptr->setPos(basepos + Vec3f(-9*sin(standby_sinangle)*WorldScale, 2*sin(standby_sinangle*2.f)*WorldScale, 0));
	if (standby_sinangle >= 2.f*M_PI) {
		standby_sinangle = 0.0f;
		setNextUpdate(true);
	}

}

void BigPumpkin::updateDrop()
{
	mainupdatecount++;
	int dropnum = 3;
	if (dropcount < dropnum) {
		dropLockon();
		dropDelay();
		dropBegin();
		dropShake();
		dropEnd();
	}
	if (dropcount == dropnum) {
		dropReturnBase();
	}
	setNextUpdate(dropcount == (dropnum+1));
	//console() << "Drop" << std::endl;
}

void BigPumpkin::updateWideshot()
{
	wideMove();
	setNextUpdate(EasingManager::tCountEnd(wide_end_t));
	//console() << "Wide" << std::endl;
}


void BigPumpkin::updateColorshot()
{


	colorBeginMove();
	colorCharge();
	colorDelay();
	colorEndMove();
	setNextUpdate(EasingManager::tCountEnd(color_t[3]));
	//console() << "Color" << std::endl;
}

void BigPumpkin::updateJumpRope()
{
	jumpRopeBeginMove();
	jumpRopeRotate();
	jumpRopeDelay();
	jumpRopeStop();
	jumpRopeEndMove();
	setNextUpdate(EasingManager::tCountEnd(jumprope_t[jumprope_t.size() - 1]));
}

void BigPumpkin::updateBarriershot()
{
	barrierShot();
	barrierBeginDelay();
	barrierCreateMapChip();
	barrierEndDelay();
	barrierReverseMapChip();
	setNextUpdate(EasingManager::tCountEnd(barrier_t[barrier_t.size() - 1]));
	//console() << "Barrier" << std::endl;
}


void BigPumpkin::setNextUpdate(const bool _isshift)
{
	if (_isshift) {
		updatetype = getNextUpdate();
		updateSetUp();
		mainupdatecount = 0;
		createNextUpdate();

	}
}

void BigPumpkin::createNextUpdate()
{
	nextcandidate.clear();
	switch (updatetype)
	{
	case STANDBY:
		if (!getIsHpHalf()) {
			createNextCandidate(STANDBY, 2);
		}
		createNextCandidate(DROP, 4);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 4);
		if (getIsHpHalf()) {
			createNextCandidate(COLORSHOT, 6);
		}
		createNextCandidate(BARRIERSHOT, 4);
		break;
	case DROP:
		createNextCandidate(STANDBY, getIsHpHalf()?0:8);
		createNextCandidate(DROP, 0);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 4);
		if (getIsHpHalf()) {
			createNextCandidate(COLORSHOT, 6);
		}
		createNextCandidate(BARRIERSHOT, 4);
		break;
	case WIDESHOT:
		createNextCandidate(STANDBY, 8);
		createNextCandidate(DROP, 4);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 4);
		if (getIsHpHalf()) {
			createNextCandidate(COLORSHOT, 6);
		}
		createNextCandidate(BARRIERSHOT, 4);
		break;
	case COLORSHOT:
		createNextCandidate(STANDBY, 0);
		createNextCandidate(DROP, 4);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 4);
		createNextCandidate(COLORSHOT, 0);
		createNextCandidate(BARRIERSHOT, 4);
		break;
	case BARRIERSHOT:
		createNextCandidate(STANDBY, getIsHpHalf() ? 0 : 8);
		createNextCandidate(DROP, 4);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 4);
		if (getIsHpHalf()) {
			createNextCandidate(COLORSHOT, 6);
		}
		createNextCandidate(BARRIERSHOT, 0);
		break;
	case JUMPROPE:
		createNextCandidate(STANDBY, getIsHpHalf() ? 0 : 8);
		createNextCandidate(DROP, 4);
		createNextCandidate(WIDESHOT, 4);
		createNextCandidate(JUMPROPE, 0);
		if (getIsHpHalf()) {
			createNextCandidate(COLORSHOT, 6);
		}
		createNextCandidate(BARRIERSHOT, 4);
		break;
	default:
		break;
	}
}

void BigPumpkin::createNextCandidate(const PumpkinUpdateType type, const int num)
{
	for (int i = 0;i < num;i++) {
		nextcandidate.push_back(type);
	}

}

void BigPumpkin::updateSetUp()
{
	switch (updatetype)
	{
	case STANDBY:
	
		break;
	case DROP:
		dropbeginpos = bossptr->getPos();
		returnbase_t = 0.0f;
		dropcount = 0;
		for (int i = 0;i < 5;i++) {
		    dropstep_t[i] = 0.0f;
		}
		break;
	case WIDESHOT:
		wideShotSetUp();
		break;
	case COLORSHOT:
		colorShotSetUp();
		break;
	case BARRIERSHOT:
		barrierSetUp();
		break;
	case JUMPROPE:
		jumpRopeSetUp();
		break;
	default:
		break;
	}
}

void BigPumpkin::createRainbowColor()
{
	rainbowcolor.push_back(ColorA(1, 0, 0, 1));
	rainbowcolor.push_back(ColorA(1, 165.f/255.f, 0, 1));
	rainbowcolor.push_back(ColorA(1, 1, 0, 1));
	rainbowcolor.push_back(ColorA(51.f/255.f, 153.f / 255.f, 67.f / 255.f, 1));
	rainbowcolor.push_back(ColorA(0, 1, 1, 1));
	rainbowcolor.push_back(ColorA(0, 0, 1, 1));
	rainbowcolor.push_back(ColorA(165.f / 255.f, 0, 1, 1));
}

PumpkinUpdateType BigPumpkin::getNextUpdate()
{
	randSeed(app::getElapsedFrames() % 10000);
	PumpkinUpdateType next = nextcandidate[randInt(nextcandidate.size())];

	return next;
}

void BigPumpkin::dropLockon()
{
	if (EasingManager::tCountEnd(dropstep_t[0]))return;
	Vec3f playerpos = bossptr->getCharacterManager()->getPlayer()->getPos();
	EasingManager::tCount(dropstep_t[0], 1.5f);
	bossptr->setPosX(bossptr->getPos().x - (bossptr->getPos().x-playerpos.x)/20.f);
	bossptr->setPosY(EasingCubicOut(dropstep_t[0], dropbeginpos.y, 8.5f * WorldScale));
	bossptr->setPosZ(EasingCubicIn(dropstep_t[0], dropbeginpos.z, 0));
	if (EasingManager::tCountEnd(dropstep_t[0])) {
		SoundM.PlaySE("oscillation.wav");
	}
		dropuppos = bossptr->getPos();
}

void BigPumpkin::dropDelay()
{
	if (EasingManager::tCountEnd(dropstep_t[1])||(!EasingManager::tCountEnd(dropstep_t[0])))return;
	EasingManager::tCount(dropstep_t[1], 1.0f);
	bossptr->setPos(dropuppos+Vec3f(randFloat(-10,10), randFloat(-10, 10), randFloat(-10, 10)));
	if (EasingManager::tCountEnd(dropstep_t[1])) {
		bossptr->setPos(dropuppos);
	
		dropdownpos = Vec3f(dropuppos.x, 3*WorldScale, dropuppos.z);
	}
}



void BigPumpkin::dropBegin()
{
	if (EasingManager::tCountEnd(dropstep_t[2]) || (!EasingManager::tCountEnd(dropstep_t[1])))return;
	EasingManager::tCount(dropstep_t[2], 0.8f);
	bossptr->setPosY(EasingBounceOut(dropstep_t[2], dropuppos.y, dropdownpos.y));
	bossptr->setRotateY(EasingCircOut(dropstep_t[2], -540, 180));
	if (dropstep_t[2] >= 0.3f&&!isshake) {
		isshake = true;
		SoundM.PlaySE("quake.wav");
		bossptr->getCameraManager()->Shake(100, 0.5f);
	}
	if (EasingManager::tCountEnd(dropstep_t[2])) {
		bossptr->setPos(dropdownpos);
		isshake = false;
	}
}
void BigPumpkin::dropShake()
{
	if (EasingManager::tCountEnd(dropstep_t[3]) || (!EasingManager::tCountEnd(dropstep_t[2])))return;

	EasingManager::tCount(dropstep_t[3], 0.5f);
}
void BigPumpkin::dropEnd()
{
	if (EasingManager::tCountEnd(dropstep_t[4]) || (!EasingManager::tCountEnd(dropstep_t[3])))return;
	EasingManager::tCount(dropstep_t[4], 1.0f);

	bossptr->setPosY(EasingCubicOut(dropstep_t[4], dropdownpos.y, dropuppos.y));
	if (EasingManager::tCountEnd(dropstep_t[4])) {
		dropbeginpos = bossptr->getPos();
		dropcount++;
		for (int i = 0;i < 5;i++) {
			dropstep_t[i] = 0.0f;
		}
	}
}

void BigPumpkin::dropReturnBase()
{
	EasingManager::tCount(returnbase_t, 1.0f);
	bossptr->setPosX(EasingCubicIn(returnbase_t, dropbeginpos.x, basepos.x));
	bossptr->setPosY(EasingCubicIn(returnbase_t, dropbeginpos.y, basepos.y));
	bossptr->setPosZ(EasingExpoOut(returnbase_t, dropbeginpos.z, basepos.z));
	if (EasingManager::tCountEnd(returnbase_t)) {
		returnbase_t = 0.0f;
		dropcount++;
	}
}

void BigPumpkin::wideShotSetUp()
{
	wide_t.clear();
	wideshotpos.clear();
	wide_end_t = 0.0f;
	int shotnum = 10;
	for (int i = 0;i < shotnum;i++) {
		wide_t.push_back(0.0f);
		wideshotpos.push_back(basepos+ Vec3f(randFloat(-8.f,8.f)*WorldScale, randFloat(-3.f, 3.f)*WorldScale, randFloat(-1.5f, 1.0f)*WorldScale));
	}
}

void BigPumpkin::wideMove()
{
	for (int i = 0;i < wide_t.size();i++) {
		if (EasingManager::tCountEnd(wide_t[i]))continue;
		EasingManager::tCount(wide_t[i],1.f);
		bossptr->setPosX(EasingExpoOut(wide_t[i], (i == 0 ? basepos.x : wideshotpos[i - 1].x),wideshotpos[i].x));
		bossptr->setPosY(EasingExpoOut(wide_t[i], (i == 0 ? basepos.y : wideshotpos[i - 1].y), wideshotpos[i].y));
		bossptr->setPosZ(EasingExpoOut(wide_t[i], (i == 0 ? basepos.z : wideshotpos[i - 1].z), wideshotpos[i].z));
		if (EasingManager::tCountEnd(wide_t[i])) {
			createWideShot();
		}
		break;
	}
	if (EasingManager::tCountEnd(wide_t[wide_t.size() - 1])) {
		EasingManager::tCount(wide_end_t,1.0f);
		bossptr->setPosX(EasingCubicOut(wide_end_t, wideshotpos[wide_t.size() - 1].x, basepos.x));
		bossptr->setPosY(EasingCubicOut(wide_end_t, wideshotpos[wide_t.size() - 1].y, basepos.y));
		bossptr->setPosZ(EasingCubicOut(wide_end_t, wideshotpos[wide_t.size() - 1].z, basepos.z));
	}
}

void BigPumpkin::createWideShot()
{
	float createnum = 7.f;
	float speedz = -0.15f;
	for (float i = 0;i < 7;i++) {
		ColorA color = rainbowcolor[(rainbowcolor.size()-1) - i];
		bossptr->getBulletManagerPointer()->CreateBossBullet(WideShotBullet(bossptr->getPos() + Vec3f(-(((float(createnum - 1)) / 2.f)*WorldScale) + WorldScale*i, -WorldScale, -bossptr->getScale().z/2.f), Vec3f(1, 1, 1)*WorldScale,
			Vec3f(0, 0, speedz)*WorldScale, Vec3f(0, 0, 0),color));
		bossptr->getBulletManagerPointer()->CreateBossBullet(WideShotBullet(bossptr->getPos() + Vec3f(-(((float(createnum - 1)) / 2.f)*WorldScale) + WorldScale*i,0, -bossptr->getScale().z / 2.f), Vec3f(1, 1, 1)*WorldScale,
			Vec3f(0, 0, speedz)*WorldScale, Vec3f(0, 0, 0), color));
		bossptr->getBulletManagerPointer()->CreateBossBullet(WideShotBullet(bossptr->getPos() + Vec3f(-(((float(createnum - 1)) / 2.f)*WorldScale) + WorldScale*i, WorldScale, -bossptr->getScale().z / 2.f), Vec3f(1, 1, 1)*WorldScale,
			Vec3f(0, 0, speedz)*WorldScale, Vec3f(0, 0, 0), color));
	}
	SoundM.PlaySE("wideshot.wav", 0.5f);
	/*playerptr->getBulletManagerPointer()->CreatePlayerBullet(SlimeBullet
		(playerptr->getPos() + speed*(WorldScale / 2.f),
			ci::Vec3f(0.95, 0.95, 0.95)*WorldScale,
			ci::Vec3f(speed)*WorldScale*0.1f,
			playerptr->getRotate() + Vec3f(0, 0, 0)));*/
}

void BigPumpkin::colorBeginMove()
{
	if (EasingManager::tCountEnd(color_t[0]))return;
	EasingManager::tCount(color_t[0], 1.f);
	bossptr->setPosX(EasingCubicOut(color_t[0],basepos.x,colorshotpos.x));
	bossptr->setPosY(EasingCubicOut(color_t[0], basepos.y, colorshotpos.y));
	bossptr->setPosZ(EasingCubicOut(color_t[0], basepos.z, colorshotpos.z));
	if (EasingManager::tCountEnd(color_t[0])) {
		colorShot();
		SoundM.PlaySE("colorcharge.wav");
	}
}

void BigPumpkin::colorCharge()
{
	if ((!EasingManager::tCountEnd(color_t[0])) || EasingManager::tCountEnd(color_t[1]))return;
	if (!ischargeshake) {
		bossptr->getCameraManager()->Shake(50.f, 3.f);
		ischargeshake = true;
	
	}
	EasingManager::tCount(color_t[1], 3.f);
}

void BigPumpkin::colorDelay()
{
	if ((!EasingManager::tCountEnd(color_t[1]))|| EasingManager::tCountEnd(color_t[2]))return;
	EasingManager::tCount(color_t[2], 7.f);
}

void BigPumpkin::colorEndMove()
{
	if ((!EasingManager::tCountEnd(color_t[2])) || EasingManager::tCountEnd(color_t[3]))return;
	bossptr->setPosX(EasingCubicOut(color_t[3], colorshotpos.x,basepos.x));
	bossptr->setPosY(EasingCubicOut(color_t[3], colorshotpos.y, basepos.y));
	bossptr->setPosZ(EasingCubicOut(color_t[3], colorshotpos.z, basepos.z));
	EasingManager::tCount(color_t[3], 1.0f);
}

void BigPumpkin::colorShot()
{
	bossptr->getBulletManagerPointer()->CreateBossBullet(ColorShotBullet(bossptr->getPos()+Vec3f(0,0,-WorldScale*3.f),Vec3f(1,1,1)*WorldScale*16.f,Vec3f(0,0,-0.075f)*WorldScale,Vec3f(0,0,0),ColorA(1,1,1,1),bossptr));
}

void BigPumpkin::colorShotSetUp()
{
	for (int i = 0;i < 4;i++) {
		color_t[i] = 0.0f;
	}
    ischargeshake = false;
	colorshotpos = basepos + Vec3f(0, 0, 20*WorldScale);
}

void BigPumpkin::jumpRopeSetUp()
{
	jumprope_t.clear();
	for (int i = 0;i < 5;i++) {
		jumprope_t.push_back(0.0f);
	}
	jumproperotatepos= basepos + Vec3f(0, -1, 10)*WorldScale;
	jumpropeendpos = basepos + Vec3f(0, -1, -4)*WorldScale;
}

void BigPumpkin::jumpRopeBeginMove()
{
	if (EasingManager::tCountEnd(jumprope_t[0]))return;
	EasingManager::tCount(jumprope_t[0], 1.0f);
	bossptr->setPosX(EasingCubicOut(jumprope_t[0], basepos.x, jumproperotatepos.x));
	bossptr->setPosY(EasingCubicOut(jumprope_t[0], basepos.y, jumproperotatepos.y));
	bossptr->setPosZ(EasingCubicOut(jumprope_t[0], basepos.z, jumproperotatepos.z));
	if (EasingManager::tCountEnd(jumprope_t[0])) {
		bossptr->getCameraManager()->Shake(10, 18.f);
	}
}

void BigPumpkin::jumpRopeRotate()
{
	if ((!EasingManager::tCountEnd(jumprope_t[0])) || EasingManager::tCountEnd(jumprope_t[1]))return;
	EasingManager::tCount(jumprope_t[1], 3.0f);
	jumproperotatespeed = EasingCubicIn(jumprope_t[1], 0.f, -20.f);
	bossptr->rotation(Vec3f(0, jumproperotatespeed, 0));


	if (EasingManager::tCountEnd(jumprope_t[1])) {
		createJumpRope();
		SoundM.PlaySE("rope.wav");
	}

}

void BigPumpkin::jumpRopeDelay()
{
	if ((!EasingManager::tCountEnd(jumprope_t[1])) || EasingManager::tCountEnd(jumprope_t[2]))return;
	EasingManager::tCount(jumprope_t[2], 15.0f);
	bossptr->setPosX(EasingExpoOut(jumprope_t[2], jumproperotatepos.x, jumpropeendpos.x));
	bossptr->setPosY(EasingExpoOut(jumprope_t[2], jumproperotatepos.y, jumpropeendpos.y));
	bossptr->setPosZ(EasingExpoOut(jumprope_t[2], jumproperotatepos.z, jumpropeendpos.z));
	bossptr->rotation(Vec3f(0, jumproperotatespeed, 0));
}

void BigPumpkin::jumpRopeStop()
{
	if ((!EasingManager::tCountEnd(jumprope_t[2])) || EasingManager::tCountEnd(jumprope_t[3]))return;
	EasingManager::tCount(jumprope_t[3], 1.0f);
	jumproperotatespeed = EasingCubicIn(jumprope_t[3], -20.f, 0.f);
	bossptr->rotation(Vec3f(0, jumproperotatespeed, 0));
	if (EasingManager::tCountEnd(jumprope_t[3])) {
		bossptr->setRotateY((int(bossptr->getRotate().y))%360);
		jumpropeendrotate = bossptr->getRotate();
	}
}

void BigPumpkin::jumpRopeEndMove()
{
	if ((!EasingManager::tCountEnd(jumprope_t[3])) || EasingManager::tCountEnd(jumprope_t[4]))return;
	EasingManager::tCount(jumprope_t[4], 1.0f);
	bossptr->setRotateY(EasingCubicOut(jumprope_t[4],jumpropeendrotate.y,180.f));
	bossptr->setPosX(EasingCubicOut(jumprope_t[4], jumpropeendpos.x, basepos.x));
	bossptr->setPosY(EasingCubicOut(jumprope_t[4], jumpropeendpos.y, basepos.y));
	bossptr->setPosZ(EasingCubicOut(jumprope_t[4], jumpropeendpos.z, basepos.z));
}

void BigPumpkin::createJumpRope()
{
	int createnum = 11;
	for (int i = 1;i <= createnum;i++) {
		ColorA color = ColorA(1, 1.0f - (float(i)/float(createnum)), 0, 1);
		Vec3f trancepos = Vec3f(0, -1.5f*WorldScale, 0);
		float tranceangle = M_PI / 4.f;
		bossptr->getBulletManagerPointer()->CreateBossBullet(
			FireBullet(jumproperotatepos + trancepos, jumpropeendpos, Vec3f(1, 1, 1)*WorldScale, i*WorldScale, tranceangle, color));
	
		bossptr->getBulletManagerPointer()->CreateBossBullet(
			FireBullet(jumproperotatepos +trancepos, jumpropeendpos, Vec3f(1, 1, 1)*WorldScale, i*WorldScale, M_PI/2.f+ tranceangle, color));
		
		bossptr->getBulletManagerPointer()->CreateBossBullet(
			FireBullet(jumproperotatepos + trancepos, jumpropeendpos, Vec3f(1, 1, 1)*WorldScale, i*WorldScale, M_PI+ tranceangle, color));

		bossptr->getBulletManagerPointer()->CreateBossBullet(
			FireBullet(jumproperotatepos + trancepos, jumpropeendpos, Vec3f(1, 1, 1)*WorldScale, i*WorldScale, 3.f*M_PI / 2.f+ tranceangle, color));
		
	}
}

void BigPumpkin::barrierSetUp()
{
	barrier_t.clear();
	barrierisshake = false;
	barriersinangle = 0.0f;
	barriercreatecount = 0;
	iscreatetype = bossptr->getHp() > bossptr->getMaxHp() / 2;
	for (int i = 0;i < 5;i++) {
		barrier_t.push_back(0.0f);
	}
}

void BigPumpkin::barrierShot()
{
	if (EasingManager::tCountEnd(barrier_t[0]))return;
	float time = 3.0f;
	if (!barrierisshake) {
		barrierisshake = true;
		SoundM.PlaySE("colorcharge.wav");
		bossptr->getBulletManagerPointer()->CreateBossBullet(BlackScaleBullet(basepos + Vec3f(0, 0, -bossptr->getScale().z / 2.f),Vec3f(0,0,0),Vec3f(6,6,6)*WorldScale,time));
		bossptr->getCameraManager()->Shake(20, time);
	}
	EasingManager::tCount(barrier_t[0], time);
	if (EasingManager::tCountEnd(barrier_t[0])) {
		barrierCreateBullet();
		SoundM.PlaySE("colorchargeshot.wav");
		barriercreatecount = 0;
	}

}

void BigPumpkin::barrierBeginDelay()
{
	if ((!EasingManager::tCountEnd(barrier_t[0])) || EasingManager::tCountEnd(barrier_t[1]))return;

	EasingManager::tCount(barrier_t[1], 3.0f);
}

void BigPumpkin::barrierCreateMapChip()
{
	if ((!EasingManager::tCountEnd(barrier_t[1])) || EasingManager::tCountEnd(barrier_t[2]))return;
	barrierUpdateBossPos();

	EasingManager::tCount(barrier_t[2], 2.5f);
	barriercreatecount++;
	int frame = 8;
	
	if (barriercreatecount % frame == 0) {
		if ((barriercreatecount / frame) >= 2 && (barriercreatecount / frame) <= 9) {
			if (iscreatetype) {
				createColorChip((barriercreatecount / frame), 8);
				createColorChip((barriercreatecount / frame), 9);
				createColorChip((barriercreatecount / frame), 13);
				createColorChip((barriercreatecount / frame), 14);
			}
			else {
				createColorChip((barriercreatecount / frame), 9);
				createColorChip((barriercreatecount / frame), 10);
				createColorChip((barriercreatecount / frame), 11);
				createColorChip((barriercreatecount / frame), 12);
				createColorChip((barriercreatecount / frame), 13);
			}

		}
	}
	if (EasingManager::tCountEnd(barrier_t[2])) {
		barriercreatecount = 0;
	}
}

void BigPumpkin::barrierEndDelay()
{
	if ((!EasingManager::tCountEnd(barrier_t[2])) || EasingManager::tCountEnd(barrier_t[3]))return;
	barrierUpdateBossPos();
	EasingManager::tCount(barrier_t[3], 7.0f);
	if (EasingManager::tCountEnd(barrier_t[3])) {
		barrierendpos = bossptr->getPos();
	}
}

void BigPumpkin::barrierReverseMapChip()
{
	if ((!EasingManager::tCountEnd(barrier_t[3])) || EasingManager::tCountEnd(barrier_t[4]))return;
	EasingManager::tCount(barrier_t[4], 2.0f);
	bossptr->setPosX(EasingCubicOut(barrier_t[4], barrierendpos.x, basepos.x));
	bossptr->setPosY(EasingCubicOut(barrier_t[4], barrierendpos.y, basepos.y));
	bossptr->setPosZ(EasingCubicOut(barrier_t[4], barrierendpos.z, basepos.z));



	barriercreatecount++;
	int frame = 8;
	if (barriercreatecount % frame == 0) {
		if ((barriercreatecount / frame) >= 2 && (barriercreatecount / frame) <= 9) {
			if (iscreatetype) {
				createNoneChip((barriercreatecount / frame), 8);
				createNoneChip((barriercreatecount / frame), 9);
				createNoneChip((barriercreatecount / frame), 13);
				createNoneChip((barriercreatecount / frame), 14);
			}
			else {
				createNoneChip((barriercreatecount / frame), 9);
				createNoneChip((barriercreatecount / frame), 10);
				createNoneChip((barriercreatecount / frame), 11);
				createNoneChip((barriercreatecount / frame), 12);
				createNoneChip((barriercreatecount / frame), 13);
			}

		}
	}


}

void BigPumpkin::createColorChip(const int y, const int x)
{
	Vec3f pos = bossptr->getMapChipManagerPointer()->getMapChips()[y][x]->getPos3f();
	Vec3f scale = bossptr->getMapChipManagerPointer()->getMapChips()[y][x]->getScale3f();
	bossptr->getEffectManagerPointer()->CreateEffect2D(EffectColored(pos, scale, ColorA(1, 1, 0, 1)));
	bossptr->getMapChipManagerPointer()->getMapChipsP()[y][x] = std::make_shared<MapChipColored>(pos, scale, bossptr->getEffectManagerPointer());
}

void BigPumpkin::createNoneChip(const int y, const int x)
{
	Vec3f pos = bossptr->getMapChipManagerPointer()->getMapChips()[y][x]->getPos3f();
	Vec3f scale = bossptr->getMapChipManagerPointer()->getMapChips()[y][x]->getScale3f();
	bossptr->getEffectManagerPointer()->CreateEffect2D(EffectColored(pos, scale, ColorA(1, 1, 0, 1)));
	bossptr->getMapChipManagerPointer()->getMapChipsP()[y][x] = std::make_shared<MapChipNone>(pos, scale);
}

void BigPumpkin::barrierCreateBullet()
{
	for (int i = 2;i <= 9;i++) {
		bossptr->getBulletManagerPointer()->CreateBossBullet(BarrierBullet(basepos+Vec3f(0,0,-bossptr->getScale().z/2.f), Vec3f(-1, i, 0)*WorldScale, Vec3f(-23, i, 0)*WorldScale, ColorA(0, 0, 0, 1)));
	}
	for (int i = 2;i <= 9;i++) {
		bossptr->getBulletManagerPointer()->CreateBossBullet(BarrierBullet(basepos + Vec3f(0, 0, -bossptr->getScale().z / 2.f), Vec3f(-21, i, 0)*WorldScale, Vec3f(0, i, 0)*WorldScale, ColorA(0, 0, 0, 1)));
	}
	if (!iscreatetype) {
		for (int i = 2;i <= 20;i++) {
			bossptr->getBulletManagerPointer()->CreateBossBullet(BarrierBullet(basepos + Vec3f(0, 0, -bossptr->getScale().z / 2.f), Vec3f(-i, 9, 0)*WorldScale, Vec3f(-i, 1, 0)*WorldScale, ColorA(0, 0, 0, 1)));
		}
	}

}

void BigPumpkin::barrierUpdateBossPos()
{
	barriersinangle += 0.02f;
	bossptr->setPos(basepos + Vec3f(-9 * sin(barriersinangle)*WorldScale, 2 * sin(barriersinangle*2.f)*WorldScale, 0));
	if (barriersinangle >= 2.f*M_PI) {
		barriersinangle = 0.0f;
	}
}

