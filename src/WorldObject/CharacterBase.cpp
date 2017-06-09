#include "CharacterBase.h"
#include"../CharacterAction/SlimeAction.h"
#include"../CharacterAction/CatAction.h"
#include"../CharacterAction/BirdAction.h"
#include"../CharacterAction/EnjelAction.h"
#include"../CharacterAction/MoguraAction.h"

#include"../CharacterAction/Ratton.h"
#include"../CharacterAction/WitchAction.h"
#include"../CharacterAction/SparrowAction.h"
#include"../CharacterAction/GhostAction.h"
#include"../CharacterAction/PumpmanAction.h"
#include"../Top/EasingManager.h"
using namespace ci;
using namespace ci::app;
CharacterBase::CharacterBase()
{
}

ci::Vec3f CharacterBase::getPos()
{
	return pos;
}

ci::Vec2f CharacterBase::getPos2f()
{
	return ci::Vec2f(pos.x,pos.y);
}

ci::Vec3f CharacterBase::getSpeed()
{
	return speed;
}

ci::Vec3f CharacterBase::getScale()
{
	return scale;
}

ci::Vec2f CharacterBase::getScale2f()
{
	return ci::Vec2f(scale.x, scale.y);
}

ci::Vec3f CharacterBase::getRotate()
{
	return rotate;
}

ci::Vec3f CharacterBase::getDrawPos()
{
	return drawpos;
}

ci::Vec3f CharacterBase::getPrevPos()
{
	return prevpos;
}

std::string CharacterBase::getName()
{
	return name;
}

void CharacterBase::setPos(const ci::Vec3f _pos)
{
	pos = _pos;
}

void CharacterBase::setPosX(const float posx)
{
	pos.x = posx;
}

void CharacterBase::setPosY(const float posy)
{
	pos.y = posy;
}

void CharacterBase::setPosZ(const float posz)
{
	pos.z = posz;
}

void CharacterBase::setDrawPos(const ci::Vec3f _pos)
{
	drawpos = _pos;
}

void CharacterBase::setDrawPosX(const float posx)
{
	drawpos.x = posx;
}

void CharacterBase::setDrawPosY(const float posy)
{
	drawpos.y = posy;
}

void CharacterBase::setPrevPos(const ci::Vec3f _pos)
{
	prevpos = _pos;
}

void CharacterBase::setRotate(const ci::Vec3f _rotate)
{
	rotate = _rotate;
}

void CharacterBase::setRotateX(const float rotatex)
{
	rotate.x = rotatex;
}

void CharacterBase::setRotateY(const float rotatey)
{
	rotate.y = rotatey;
}

void CharacterBase::setRotateZ(const float rotatez)
{
	rotate.z = rotatez;
}

void CharacterBase::rotation(const ci::Vec3f _rotate)
{
	rotate += _rotate;
}

void CharacterBase::setSpeed(const ci::Vec3f _speed)
{
	speed = _speed;
}

void CharacterBase::setSpeedX(const float speedx)
{
	speed.x = speedx;
}

void CharacterBase::setSpeedY(const float speedy)
{
	speed.y = speedy;
}

void CharacterBase::setSpeedZ(const float speedz)
{
	speed.z = speedz;
}

void CharacterBase::setScale(const ci::Vec3f _scale)
{
	scale = _scale;
}

void CharacterBase::setName(const std::string _name)
{
	name = _name;
}

void CharacterBase::AddForth(const ci::Vec3f _forth)
{
	speed += _forth;
}

void CharacterBase::setCanJumpCount(const int count)
{
	jumpcount = count;
}

BulletManager * CharacterBase::getBulletManagerPointer()
{
	return bulletmanager;
}

void CharacterBase::decideAction(ActionType folm)
{
	switch (folm)
	{
	case SLIME:
		setCharacterAction(SlimeAction());
		break;
	case CAT:
		setCharacterAction(CatAction());
		break;
	case BIRD:
		setCharacterAction(BirdAction());
		break;
	case ENJEL:
		setCharacterAction(EnjelAction());
		break;
	case MOGURA:
		setCharacterAction(MoguraAction());
		break;
	case RATTON:
		setCharacterAction(RattonAction());
		break;
	case WITCH:
		setCharacterAction(WitchAction());
		break;
	case SPARROW:
		setCharacterAction(SparrowAction());
		break;
	case GHOST:
		setCharacterAction(GhostAction());
		break;
	case PUMPMAN:
		setCharacterAction(PumpmanAction());
		break;
	case NONE:
		break;
	default:
		break;
	}
}

CharacterType CharacterBase::getCharacterType()
{
	return charactertype;
}

void CharacterBase::SetBulletManagerPointer(BulletManager * _bulletmanager)
{
	bulletmanager = _bulletmanager;
}

ci::AxisAlignedBox3f CharacterBase::getAABB()
{
	AxisAlignedBox3f buf(pos - (scale / 2.f), pos + (scale / 2.f));
	return buf;
}

CharacterBase * CharacterBase::getThisPointer()
{
	return this;
}

ActionType CharacterBase::getActiontype()
{
	return actiontype;
}

void CharacterBase::setActionType(ActionType _actiontype)
{
	actiontype = _actiontype;
}

void CharacterBase::setCharacterManagerPointer(CharacterManager * charactermanager)
{
	charactermanagerptr = charactermanager;
}

CharacterManager * CharacterBase::getCharacterManager()
{
	return charactermanagerptr;
}

void CharacterBase::setQuat(ci::Quatf _quat)
{
	quat = _quat;
}

void CharacterBase::setBulletQuat(ci::Quatf _quat)
{
	bulletquat = _quat;
}

void CharacterBase::setJumpPower()
{
	action->setJumpPower(action->getMaxJumpPower());
}

void CharacterBase::RsetDeathColorT()
{
	death_color_t = 0.0f;
	color = defaultcolor;
}

ci::Quatf CharacterBase::getQuat()
{
	return quat;
}

ci::Quatf CharacterBase::getBulletQuat()
{
	return bulletquat;
}

bool CharacterBase::getIsStan()
{
	return isstun;
}

bool CharacterBase::updateDeathEnd()
{
	return EasingManager::tCountEnd(death_color_t);
}

void CharacterBase::setIsStun(const bool is)
{
	isstun = is;
}

void CharacterBase::setIsinvincible(const bool is)
{
	issnvincible = is;
}

bool CharacterBase::getIsInvincible()
{
	return issnvincible;
}


void CharacterBase::setDefalutColor(const ci::ColorA _color)
{
	defaultcolor = _color;
}

void CharacterBase::setColor(const ci::ColorA _color)
{
	color = _color;
}

ci::ColorA CharacterBase::getColor()
{
	return color;
}

ci::ColorA CharacterBase::getUniqueColor()
{
	return uniquecolor;
}

ci::ColorA CharacterBase::getDefaultColor()
{
	return defaultcolor;
}
void CharacterBase::setUniqueColor(ci::ColorA _color)
{
	uniquecolor = _color;
}

bool CharacterBase::getCanJump()
{
	return canjump;
}

void CharacterBase::setCanJump(const bool is)
{
	canjump = is;
}

void CharacterBase::onRightWall()
{
	action->onRightWall();
}

void CharacterBase::onLeftWall()
{
	action->onLeftWall();
}

void CharacterBase::updateDeath(float time)
{
	if (!getIsAlive()) {
		EasingManager::tCount(death_color_t,time);
		color.r = EasingLinear(death_color_t, defaultcolor.r, 0.0f);
		color.g = EasingLinear(death_color_t, defaultcolor.g, 0.0f);
		color.b = EasingLinear(death_color_t, defaultcolor.b, 0.0f);
	}
}

void CharacterBase::updateStun()
{
	if (issnvincible) {
		stuncount++;
		float angle = stuncount / 2.f;
		float colorvalue = 0.5f + 0.5f*cos(angle);
		color = ci::ColorA(1, colorvalue, colorvalue, 1);
		int stuntime = 30;
		int snvincibletime = 60;
		if (stuncount > snvincibletime) {
			issnvincible = false;
			stuncount = 0;
			color = defaultcolor;
		}
		else if (stuncount > stuntime) {
			isstun = false;
		}
	}
	else {
		color = defaultcolor;
	}
}

int CharacterBase::getHp()
{
	return hp;
}

int CharacterBase::getMaxHp()
{
	return maxhp;
}

int CharacterBase::getId()
{
	return id;
}

void CharacterBase::setHp(int _hp)
{
	hp = _hp;
	hp = std::max(hp, 0);
}

void CharacterBase::setMaxHp(int _maxhp)
{
	maxhp = _maxhp;
}

void CharacterBase::addHpValue(int value)
{
	hp += value;
	if (hp >= 100)hp = 100;
	if (hp < 0)hp = 0;
}

bool CharacterBase::getIsAlive()
{
	return hp > 0;
}




