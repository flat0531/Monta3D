#include "CharacterBase.h"
#include"../CharacterAction/SlimeAction.h"
#include"../CharacterAction/CatAction.h"
#include"../CharacterAction/Ratton.h"
#include"../CharacterAction/WitchAction.h"
#include"../CharacterAction/SparrowAction.h"
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
		return;
	case CAT:
		setCharacterAction(CatAction());
		return;
	case RATTON:
		setCharacterAction(RattonAction());
		return;
	case WITCH:
		setCharacterAction(WitchAction());
		break;
	case SPARROW:
		setCharacterAction(SparrowAction());
		break;
	default:
		return;
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

ci::ColorA CharacterBase::getColor()
{
	return color;
}

ci::ColorA CharacterBase::getUniqueColor()
{
	return uniquecolor;
}

void CharacterBase::setUniqueColor(ci::ColorA _color)
{
	uniquecolor = _color;
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
	/*hp = std::max(value, 0);
	hp = std::min(value, maxhp);*/
}

bool CharacterBase::getIsAlive()
{
	return hp > 0;
}



